#include "../include/servidor.h"
#include <iostream>
#include <boost/beast/core/detail/base64.hpp>

Servidor::Servidor(int port_tcp, int port_udp, rclcpp::Node::SharedPtr node, boost::asio::io_context &io_context)
    : io_context_(io_context), udp_socket_(io_context, udp::endpoint(udp::v4(), port_udp)),
      tcp_acceptor_(io_context, tcp::endpoint(tcp::v4(), port_tcp)),
      nodeManager(node), ip_port_tcp_(port_tcp), ip_port_udp_(port_udp),
      connection_active_(false), tcp_socket_(io_context)
{
    tcp_acceptor_.set_option(tcp::acceptor::reuse_address(true));
}

void Servidor::run()
{
    std::cout << "Servidor listening port " << tcp_acceptor_.local_endpoint().port() << std::endl;
    runUdp();
    io_context_.run();
}

void Servidor::runUdp()
{
    // std::cout << "Servidor escuchando por udp en el puerto " << tcp_acceptor_.local_endpoint().port() << std::endl;
    try
    {
        // Poner el socket en modo bloqueante para discovery
        if (!connection_active_)
        {
            udp_discovery();
            if (!connection_active_)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                runUdp();
            }
            handle_udp_acks();

            std::cout << "Waiting conexion TCP...\n";
        }
        try
        {
            if (!connection_active_)
            {
                std::cout << "exit the code \n";
                // tcp::socket tcp_socket(io_context_);
                tcp_acceptor_.accept(tcp_socket_);
            }
            startAccept();
        }
        catch (const std::exception &e)
        {
            std::cerr << "TCP connection error: " << e.what() << "\n";
            connection_active_ = false;
        }
        // tcp_acceptor_.close();
        // std::cout << "Reiniciando servidor...\n";
        // std::this_thread::sleep_for(std::chrono::seconds(1));

        // // Reabrir el acceptor para la próxima ronda
        // tcp_acceptor_ = tcp::acceptor(io_context_, tcp::endpoint(tcp::v4(), ip_port_tcp_));
        // tcp_acceptor_.set_option(tcp::acceptor::reuse_address(true));
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error en descubrimiento UDP: " << e.what() << "\n";
        connection_active_ = false;
    }
}

void Servidor::udp_discovery()
{
    try
    {
        udp_socket_.non_blocking(false);

        char buffer[1024] = {0};
        udp::endpoint client_ep;

        std::cout << "Waiting for UPD client...\n";
        size_t len = udp_socket_.receive_from(boost::asio::buffer(buffer), client_ep);

        std::cout << "UDP client found: " << client_ep << "\n";
        std::cout << "Message received: " << std::string(buffer, len) << "\n";

        if (std::string(buffer, len) == "DISCOVER")
        {
            YAML::Node config;
            try
            {
                std::string path_ = PATH;
                config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error loading YAML file: " << e.what() << std::endl;
            }
            std::string str2client = "SERVER_ACK: " + config["ROBOT_NAME"].as<std::string>() + " TYPE: " + config["TYPE"].as<std::string>();
            udp_socket_.send_to(boost::asio::buffer(str2client), client_ep);
            client_endpoint_ = client_ep;
            connection_active_ = true;
            std::cout << "Confirmed Client " << client_ep << "\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "UDP discovery error: " << e.what() << "\n";
        connection_active_ = false;
    }
}

void Servidor::handle_udp_acks()
{
    std::thread([this]()
                {
        char buffer[1024];
        int failed_acks = 0;
        const int max_failed_acks = 3;

        while (connection_active_) {
            try {
                udp_socket_.send_to(boost::asio::buffer("ACK"), client_endpoint_);
            } catch (...) {
                std::cerr << "Error sending ACK\n";
                connection_active_ = false;
                break;
            }

            bool ack_received = false;
            for (int i = 0; i < 5; ++i) {
                boost::system::error_code ec;
                udp::endpoint sender;
                udp_socket_.non_blocking(true);
                size_t len = udp_socket_.receive_from(boost::asio::buffer(buffer), sender, 0, ec);

                if (!ec && len > 0 && sender == client_endpoint_ &&
                    std::string(buffer, len) == "ACK") {
                    ack_received = true;
                    failed_acks = 0;
                    break;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }

            if (!ack_received && ++failed_acks >= max_failed_acks) {
                // nodeManager.reset(); // This cause a bug because doing at the same time as other .reset()
                std::cerr << "UDP connection lost\n";
                connection_active_ = false;
                break;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        } })
        .detach();
}

void Servidor::startAccept()
{
    // Acepta una nueva conexión
    std::cout << "Waiting for a client to connect... estoy en startAccept\n";
    tcp_acceptor_.async_accept(tcp_socket_, [this](boost::system::error_code ec)
                               {
            if (!ec) {
                std::cout << "Client connected.\n";
                startRead();
            } else {
                std::cerr << "Error accepting connection: " << ec.message() << "\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                startAccept(); // Retry accepting a connection
            } });
    // run();
}

void Servidor::resetConnection()
{
    try
    {
        std::cout << "Closing the connection with the client...\n";
        tcp_socket_.close();
        buf_.clear(); // Limpia el buffer
        nodeManager.reset();
        connection_active_ = false;

        // tcp_acceptor_.close();
        // std::cout << "Reiniciando servidor...\n";
        // std::this_thread::sleep_for(std::chrono::seconds(1));

        // // Reabrir el acceptor para la próxima ronda
        // // tcp_acceptor_.close();
        // tcp_acceptor_ = tcp::acceptor(io_context_, tcp::endpoint(tcp::v4(), ip_port_tcp_));
        // tcp_acceptor_.set_option(tcp::acceptor::reuse_address(true));
        runUdp(); // Espera por un nuevo cliente
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error closing socket: " << e.what() << "\n";
    }
}

void Servidor::closeServer()
{
    std::cout << "Shutting down the server...\n";

    try
    {
        // Detener el contexto de IO
        io_context_.stop();

        // Cerrar el socket
        if (tcp_socket_.is_open())
        {
            pri1("I'm trying to shut down");
            tcp_socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            tcp_socket_.close();
        }

        std::cout << "Server successfully shut down.\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error closing server: " << e.what() << "\n";
    }
}

void Servidor::startRead()
{
    if (connection_active_ == false)
    {
        std::cout << "There is no active connection. Cannot read.\n";
        run();
    }
    pri1("In StartRead");
    tcp_socket_.async_read_some(
        boost::asio::buffer(buffer_array),
        [this](const boost::system::error_code &ec, long unsigned int bytes_transferred)
        {
            if (!ec)
            {
                // pri1("Hola1");
                std::string buffer_string(buffer_array.data(), bytes_transferred);
                // pri1("Hola2");
                std::vector<std::string> buffer_vector = splitJson(buffer_string);
                // pri1("Hola3");
                handleType(buffer_vector);
            }
            else if (ec == boost::asio::error::eof || ec == boost::asio::error::connection_reset)
            {
                std::cout << "Cliente desconectado.\n";
                resetConnection();
            }
            else
            {
                std::cerr << "Error en la lectura: " << ec.message() << "\n";
                resetConnection();
            }
        });
}

void Servidor::handleType(std::vector<std::string> const &jsons)
{
    for (auto json_ : jsons)
    {
        json json_msg = json::parse(json_);
        if (json_msg.contains("opt") && json_msg["opt"] == headerToString(MSG))
        {
            HandleMsg handleMsg(nodeManager);
            handleMsg.handleMsgJson(json_msg);
        }
        else if (json_msg.contains("opt") && json_msg["opt"] == headerToString(REQUEST_IMG))
            handleRequestImg(json_msg);
        else if (json_msg.contains("opt") && json_msg["opt"] == headerToString(REQUEST_MSG))
            handleRequestMsg(json_msg);
        else
            std::cout << "El campo 'opt' no contiene 'MSG' o 'IMG_REQUEST' o no existe.\n";
        // pri1("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
        if (json_msg.contains("opt") && json_msg["opt"] == headerToString(MSG) && json_msg.contains("target") && json_msg["target"] == targetToString(Goal_Pose))
        {
#if EN_CASA
            // std::vector<RealPositionMeters> path_number = {
            //     {0.060000020116567576, 0.21000003948807722},
            //     {0.05966976269587487, 0.32496261902097734},
            //     {0.05899427516749878, 0.3999589961761081},
            //     {0.05571277716327838, 0.47487640909666373},
            //     {0.06928928493394348, 0.5670454091883506},
            //     {0.07326448564625476, 0.5917274545390518}};
            std::vector<RealPositionMeters> path_number = nodeManager.getRealPositionPath();

#else
            std::vector<RealPositionMeters> path_number = nodeManager.getRealPositionPath();
#endif

            std::vector<FinalPosition> path_pixel;

            YAML::Node config;
            try
            {
                std::string path_ = PATH;
                config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error loading YAML file: " << e.what() << std::endl;
            }
            std::string path = config["PATH2MAP"].as<std::string>();

            path += "/" + replaceSpaces(json_msg["map_name"]) + ".yaml";
            try
            {
                YAML::Node config = YAML::LoadFile(path);
                float resolution = config["resolution"].as<float>();
                auto origin = config["origin"];
                float origin_x = origin[0].as<float>();
                float origin_y = origin[1].as<float>();

                for (const auto &point : path_number)
                {
                    FinalPosition final_p;
                    final_p.x_pixel = static_cast<int>((point.x - origin_x) / resolution);
                    final_p.y_pixel = static_cast<int>((point.y - origin_y) / resolution);
                    path_pixel.push_back(final_p);
                }

                // Imprimir resultados
                for (const auto &pos : path_pixel)
                {
                    std::cout << "Pixel Position: (" << pos.x_pixel << ", " << pos.y_pixel << ")\n";
                }
            }
            catch (const YAML::Exception &e)
            {
                std::cerr << "Error al cargar el archivo YAML: " << e.what() << std::endl;
            }

            sendMsg(toJson::sendGoalPosePath(path_pixel));
        }
    }
    startRead();
}

void Servidor::handleRequestMsg(const json &json_msg)
{
    pri1("Estoy en handleRequestMsg");
    if (json_msg.contains("target") && json_msg["target"] == targetToString(Map_Name))
    {
        YAML::Node config;
        try
        {
            std::string path_ = PATH;
            config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading YAML file: " << e.what() << std::endl;
        }
        std::string path = config["PATH2MAP"].as<std::string>();

        sendMsg(toJson::sendMapName(getMapName(path)));
    }
    else if (json_msg.contains("target") && json_msg["target"] == targetToString(Request_Robot_Position))
    {
        YAML::Node config;
        try
        {
            std::string path_ = PATH;
            config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading YAML file: " << e.what() << std::endl;
        }
        std::string path = config["PATH2MAP"].as<std::string>();

        if (json_msg.contains("map_name") && json_msg["map_name"] != "")
        {
            // pri1("hola");
            std::string map_name_without_spaces = replaceSpaces(json_msg["map_name"].get<std::string>());
            path += "/" + map_name_without_spaces + ".yaml";
            // pri1("hola2");
            FinalPosition fp = nodeManager.getPositionRobotPixel(path);
            // pri1("hola3");
            sendMsg(toJson::sendRobotPositionInitialpose(fp.x_pixel, fp.y_pixel, fp.yaw));
        }
    }
}

void Servidor::handleRequestImg(const json &json_msg)
{
    // pri1("Estoy en handleRequestImg");
    if (json_msg.contains("target") && json_msg["target"] == targetToString(Request_Map_SLAM))
    {
        YAML::Node config;
        try
        {
            std::string path_ = PATH;
            config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading YAML file: " << e.what() << std::endl;
        }
        std::string path = config["PATH2MAP"].as<std::string>();

        if (json_msg.contains("map_name") && json_msg["map_name"] != "")
        {
            std::string map_name_without_spaces = replaceSpaces(json_msg["map_name"].get<std::string>());

            std::cout << "+++++++++++++++Mapa seleccionado: " << map_name_without_spaces << std::endl;
            float resolution = 0.0;
            getResolution(path + "/" + map_name_without_spaces + ".yaml", resolution);
            path += "/" + map_name_without_spaces + ".pgm";
            int width = 0, height = 0;
            getImageSize(path, width, height);

            sendMsg(toJson::sendInfoMap(json_msg["map_name"], width, height, resolution));
            std::thread sendMapThread(&Servidor::sendImageMap, this, path, false);
            sendMapThread.detach();
        }
        else
        {
            // pri1("Estoy en else de handleRequestImg");
            FinalPosition fp = nodeManager.getPositionRobotPixel(path + "/temporal_map.yaml");
            path += "/temporal_map.pgm";

            // send robot position pixels
            // pri1("Hola4");
            sendMsg(toJson::sendRobotPositionPixel(fp.x_pixel, fp.y_pixel, fp.yaw));
            // pri1("Hola5");
            nodeManager.refresh_map();
            // pri1("Hola6");
            std::thread sendMapThread(&Servidor::sendImageMap, this, path, true);
            sendMapThread.detach();
        }
    }
    else if (json_msg.contains("target") && json_msg["target"] == targetToString(Img_Map_Select))
    {
        YAML::Node config;
        try
        {
            std::string path_ = PATH;
            config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading YAML file: " << e.what() << std::endl;
        }
        std::string path = config["PATH2MAP"].as<std::string>();

        path += "/" + replaceSpaces(json_msg["map_name"]);

        // nodeManager.refresh_map(json_msg["map_name"]);
        std::thread sendMapThread(&Servidor::sendImageMap, this, path, false);
        sendMapThread.detach();
    }
}

void Servidor::sendMsg(const json &json_msg)
{
    std::string jsonStr = json_msg.dump();
    pri1(jsonStr);
    boost::asio::write(tcp_socket_, boost::asio::buffer(jsonStr));
}

void Servidor::sendImageMap(const std::string &name_map, bool img_map_SLAM)
{
    try
    {
        // bool img_map_SLAM;
        // if (name_map.find("temporal") != std::string::npos)
        //     img_map_SLAM = true;
        // else
        //     img_map_SLAM = false;
        const std::size_t maxJsonSize = 2048; // Tamaño máximo por paquete

        // Leer imagen PGM usando OpenCV
        cv::Mat image = cv::imread(name_map, cv::IMREAD_GRAYSCALE);
        if (image.empty())
        {
            throw std::runtime_error("Error reading image in sendImageMap.");
        }

        // Comprimir imagen y convertirla a formato PNG
        std::vector<int> compression_params = {cv::IMWRITE_PNG_COMPRESSION, 9}; // Nivel de compresión (0-9)
        std::vector<uchar> compressed_image;
        cv::imencode(".png", image, compressed_image, compression_params);

        // Leer los datos comprimidos directamente desde la memoria
        std::size_t totalSize = compressed_image.size();
        const std::size_t maxDataSize = 1300; // Espacio reservado para los datos de la imagen
        std::size_t bytesSent = 0;
        std::size_t numFrame = 0;
        std::size_t totalFrames = (totalSize + maxDataSize - 1) / maxDataSize; // Calcular total de frames

        while (bytesSent < totalSize)
        {
            std::size_t bytesRead = std::min(maxDataSize, totalSize - bytesSent);
            std::vector<char> buffer(compressed_image.begin() + bytesSent, compressed_image.begin() + bytesSent + bytesRead);

            // Convertir datos a base64
            std::string hexData = toBase64(buffer.data(), bytesRead);

            // Crear el JSON
            nlohmann::json jsonMessage = toJson::sendImgMap(hexData, bytesRead, totalSize, numFrame, totalFrames, img_map_SLAM);

            // Serializar el JSON
            std::string jsonStr = jsonMessage.dump();

            // Verificar que el tamaño total no exceda el límite
            if (jsonStr.size() > maxJsonSize)
            {
                std::string str = "The generated JSON exceeds the maximum allowed size " + std::to_string(jsonStr.size());
                throw std::runtime_error(str);
            }

            // Enviar el JSON por el socket
            pri1("IMAGEN SENDING size: " + std::to_string(jsonStr.size()));
            // pri1(std::to_string(jsonStr.size()));
            boost::asio::write(tcp_socket_, boost::asio::buffer(jsonStr));
            bytesSent += bytesRead;
            numFrame++;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error In sendImageMap: " << e.what() << std::endl;
    }
}
