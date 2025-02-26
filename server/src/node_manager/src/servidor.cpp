#include "../include/servidor.h"
#include <iostream>
#include <boost/beast/core/detail/base64.hpp>

Servidor::Servidor(int port, rclcpp::Node::SharedPtr node)
    : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), socket_(io_context_), nodeManager(node) {}

void Servidor::run()
{
    std::cout << "Servidor escuchando en el puerto " << acceptor_.local_endpoint().port() << std::endl;
    startAccept();
    io_context_.run();
}

void Servidor::startAccept()
{
    // Acepta una nueva conexión
    std::cout << "Waiting for a client to connect...\n";
    acceptor_.async_accept(socket_, [this](boost::system::error_code ec)
                           {
            if (!ec) {
                std::cout << "Client connected.\n";
                startRead();
            } else {
                std::cerr << "Error accepting connection: " << ec.message() << "\n";
                startAccept(); // Retry accepting a connection
            } });
}

void Servidor::resetConnection()
{
    try
    {
        std::cout << "Cerrando la conexión con el cliente...\n";
        socket_.close();
        buf_.clear(); // Limpia el buffer
        nodeManager.reset();
        startAccept(); // Espera por un nuevo cliente
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error cerrando el socket: " << e.what() << "\n";
    }
}

void Servidor::closeServer()
{
    std::cout << "Apagando el servidor...\n";

    try
    {
        // Detener el contexto de IO
        io_context_.stop();

        // Cerrar el socket
        if (socket_.is_open())
        {
            pri1("Estoy intentando cerrarme");
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            socket_.close();
        }

        std::cout << "Servidor cerrado correctamente.\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error cerrando el servidor: " << e.what() << "\n";
    }
}

void Servidor::startRead()
{
    pri1("estoy en StartRead");
    socket_.async_read_some(
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

            std::string path = PATH2MAP;
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
        std::string path = PATH2MAP;
        sendMsg(toJson::sendMapName(getMapName(path)));
    }
    else if (json_msg.contains("target") && json_msg["target"] == targetToString(Request_Robot_Position))
    {
        // pri1("Estoy en handleRequestMsg EEEEEELLLLSSSEEEEE");

        std::string path = PATH2MAP;
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
        std::string path = PATH2MAP;
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
        std::string path = PATH2MAP;
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
    boost::asio::write(socket_, boost::asio::buffer(jsonStr));
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
            throw std::runtime_error("Error al leer la imagen.");
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
                std::string str = "El JSON generado excede el tamaño máximo permitido " + std::to_string(jsonStr.size());
                throw std::runtime_error(str);
            }

            // Enviar el JSON por el socket
            pri1("IMAGEN ENVIADA size: " + std::to_string(jsonStr.size()));
            // pri1(std::to_string(jsonStr.size()));
            boost::asio::write(socket_, boost::asio::buffer(jsonStr));
            bytesSent += bytesRead;
            numFrame++;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error en sendImageMap: " << e.what() << std::endl;
    }
}
