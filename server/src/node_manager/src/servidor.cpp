#include "../include/servidor.h"
#include <iostream>

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

void Servidor::handleDisconnect(const boost::system::error_code &ec)
{
    if (ec == boost::asio::error::eof)
    {
        std::cout << "Client disconnected.\n";
    }
    else
    {
        std::cerr << "Error: " << ec.message() << "\n";
    }
    resetConnection();
}

void Servidor::resetConnection()
{
    // rviz_active = false;
    socket_.close(); // Ensure the socket is closed
    buf_.clear();    // Clear the buffer
    startAccept();   // Wait for the next client
}

void Servidor::startRead()
{
    socket_.async_read_some(
        boost::asio::buffer(buffer_array),
        [this](const boost::system::error_code &ec, long unsigned int bytes_transferred)
        {
            if (!ec)
            {
                // Crear un std::string a partir del buffer leído
                std::string buffer_string(buffer_array.data(), bytes_transferred);
                pri1(buffer_string);
                std::vector<std::string> buffer_vector = splitJson(buffer_string);
                handleType(buffer_vector);
            }
            else if (ec != boost::asio::error::eof)
            {
                std::cerr << "Error en la lectura: " << ec.message() << std::endl;
            }
        });
}

// void Servidor::readHeader()
// {
//     std::cout << "estoy en readHeader" << std::endl;
//     boost::asio::async_read_until(socket_, buffer_, '}',
//                                   [this](boost::system::error_code ec, std::size_t bytes_transferred)
//                                   {
//                                       if (!ec)
//                                       {
//                                           std::istream stream(&buffer_);
//                                           std::string tipo;
//                                           std::getline(stream, tipo, ':'); // Lee hasta ':'

//                                           std::string longitudStr;
//                                           std::getline(stream, longitudStr, ':'); // Remove processed data

//                                           int longitud = std::stoi(longitudStr);
//                                           std::cout << "Tipo: " << tipo << ", Longitud: " << longitud << std::endl;

//                                           std::string contenido;
//                                           std::getline(stream, contenido, '\n'); // Remove processed data
//                                                                                  //   handleType(tipo, longitud, contenido);
//                                           std::cout << "Contenido " << contenido << std::endl;

//                                           std::string resto;
//                                           std::getline(stream, resto, '\0'); // Remove processed data
//                                           handleType(tipo, longitud, contenido, resto);
//                                           std::cout << "resto " << resto << std::endl;
//                                       }
//                                       else
//                                       {
//                                           handleDisconnect(ec);
//                                       }
//                                   });
// }

void Servidor::handleType(std::vector<std::string> const &jsons)
{
    for (auto json_ : jsons)
    {
        json parsed_json = nlohmann::json::parse(json_);

        if (parsed_json.contains("opt") && parsed_json["opt"] == headerToString(MSG))
        {
            if (parsed_json.contains("target") && parsed_json["target"] == targetToString(Joystick_Position))
            {
                float linear, angular;
                getPositionJoystick(json_, linear, angular);
                pri1("hola2");
                pri1(std::to_string(linear) + "<-linear angular ->" + std::to_string(angular));
                nodeManager.execute_position(linear, angular);
                pri1("hola");
            }
        }
        else if (parsed_json.contains("opt") && parsed_json["opt"] == headerToString(REQUEST_IMG))
        {
            if (parsed_json.contains("target") && parsed_json["target"] == targetToString(Img_Map_SLAM))
            {
                nodeManager.create_publisher(stringToTarget(parsed_json["target"]));
                // nodeManager.refresh_map();
                std::string path = PATH2MAP;
                std::string path_yaml = path + "/temporal_map.yaml";
                path += "/temporal_map.pgm";
                // struct FinalPosition final_position = nodeManager.getPositionRobotPixel(path_yaml);
                // std::string msg = "X_pixel:" + std::to_string(final_position.x_pixel) + ",Y_pixel:" + std::to_string(final_position.y_pixel) + ",yawl:" + std::to_string(final_position.yaw);
                // sendMsg(msg, "final_position");
                sendImageMap(path);
            }
        }
        else
        {
            std::cout << "El campo 'opt' no contiene 'MSG' o 'IMG_REQUEST' o no existe.\n";
        }
        pri1("hola3");
    }
    startRead();
    // if (type == "MSG")
    // {
    //     pri1("estoy en handleType con mi target " + target);
    //     nodeManager.create_publisher(target);
    //     // readBodyMsg(size, target);
    //     processMsg(else_info, target);
    // }
    // else if (type == "IMG")
    // {
    //     // saveImage(else_info);
    // }
    // else if (type == "REQUEST_MSG")
    // {
    //     manageTarget(target);
    // }
    // else if (type == "REQUEST_IMG")
    // {
    //     if (target == "map_scan")
    //     {
    //         nodeManager.create_publisher(target);
    //         nodeManager.refresh_map();
    //         std::string path = PATH2MAP;
    //         std::string path_yaml = path + "/temporal_map.yaml";
    //         path += "/temporal_map.pgm";
    //         struct FinalPosition final_position = nodeManager.getPositionRobotPixel(path_yaml);
    //         std::string msg = "X_pixel:" + std::to_string(final_position.x_pixel) + ",Y_pixel:" + std::to_string(final_position.y_pixel) + ",yawl:" + std::to_string(final_position.yaw);
    //         sendMsg(msg, "final_position");
    //         sendImageMap(path);
    //     }
    // }
}

// void Servidor::manageTarget(std::string const &target)
// {
//     if (target == "send_map_names")
//     {
//         std::string msg;
//         std::string path = PATH2MAP;
//         std::string command = "find " + path + " -type f -name '*.pgm' 2>&1";

//         std::vector<std::string> maps = executeCommand(command);
//         if (maps.empty())
//         {
//             std::cout << "No se encontraron archivos .png en el directorio actual." << std::endl;
//         }
//         else
//         {
//             std::cout << "Archivos encontrados:" << std::endl;
//             for (size_t i = 0; i < maps.size(); ++i)
//             {
//                 std::filesystem::path filePath(maps[i]);
//                 msg += filePath.filename().string();
//                 if (i != maps.size() - 1)
//                 {
//                     msg += "\n";
//                 }
//             }
//         }
//         pri1(msg);
//         sendMsg(msg, "maps");
//     }
// }

// void Servidor::readBodyMsg(size_t const &size, std::string const &target)
// {
//     pri1("estoy en readBodyMsg");
//     boost::asio::streambuf buf;
//     std::string data;
//     boost::asio::async_read(socket_, buf, boost::asio::transfer_exactly(size),
//                             [this, &buf, &target](boost::system::error_code ec, std::size_t bytes_transferred)
//                             {
//                                 pri1("estoy en la funcion de dentro de read body");
//                                 if (!ec)
//                                 {
//                                     std::istream stream_(&buf);
//                                     std::string data;
//                                     std::getline(stream_, data);
//                                     pri1("quiero saber data");
//                                     pri1(data);
//                                     processMsg(data, target);
//                                     readHeader();
//                                 }
//                                 else
//                                 {
//                                     handleDisconnect(ec);
//                                 }
//                             });
// }

// void Servidor::processMsg(std::string const &data, std::string const &target)
// {
//     pri1("procesar mensaje");
//     pri1(data);
//     if (target == get_info_message(Position_joystick))
//     {
//         float linear, angular;
//         getValuePositionJoystick(data, linear, angular);
//         std::string str = std::to_string(linear) + "<-linear angular ->" + std::to_string(angular);
//         pri1(str);
//         nodeManager.execute_position(linear, angular);
//     }
// }

// void Servidor::sendImageMap(const std::string &name_map)
// {
//     // boost::asio::socket_base::send_buffer_size sendOption(8192); // Tamaño en bytes
//     // socket_.set_option(sendOption);

//     // boost::asio::socket_base::receive_buffer_size recvOption(8192); // Tamaño en bytes
//     // socket_.set_option(recvOption);
//     // Abrir el archivo .pgm en modo binario
//     std::string path = name_map;
//     std::ifstream file(path, std::ios::binary);
//     if (!file)
//     {
//         throw std::runtime_error("No se pudo abrir el archivo " + path);
//     }

//     // Leer el contenido del archivo
//     file.seekg(0, std::ios::end);
//     std::size_t file_size = file.tellg();
//     file.seekg(0, std::ios::beg);
//     std::vector<char> buffer(file_size);
//     const size_t packetSize = 1024;
//     size_t bytesSent = 0;

//     std::string header = "IMG:" + std::to_string(file_size) + ":map_drawing\n";
//     boost::asio::write(socket_, boost::asio::buffer(header));

//     while (bytesSent < file_size)
//     {
//         file.read(buffer.data(), packetSize);
//         size_t bytesRead = file.gcount();
//         boost::asio::write(socket_, boost::asio::buffer(buffer.data(), bytesRead));
//         bytesSent += bytesRead;

//         // Esperar confirmación del cliente
//         // char ack[3];
//         // boost::asio::read(socket_, boost::asio::buffer(ack, 3));
//         // if (std::string(ack) != "ACK")
//         // {
//         //     pri1("OK");
//         //     throw std::runtime_error("ACK no recibido");
//         // }
//     }
//     // file.read(buffer.data(), file_size);

//     // pri1(buffer.data());
//     // // Enviar el tamaño del archivo primero
//     // // boost::asio::write(socket, boost::asio::buffer(&file_size, sizeof(file_size)));

//     // // Enviar el contenido del archivo
//     // boost::asio::write(socket_, boost::asio::buffer(buffer));

//     // std::cout << "Archivo enviado: " << path << " (" << file_size << " bytes)" << std::endl;
// }

void Servidor::sendMsg(const json &json_msg)
{
    std::string jsonStr = json_msg.dump();
    boost::asio::write(socket_, boost::asio::buffer(jsonStr));
}

void Servidor::sendImageMap(const std::string &name_map)
{
    const std::size_t maxJsonSize = 1024; // Tamaño máximo por paquete

    std::ifstream file(name_map, std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("No se pudo abrir el archivo " + name_map);
    }

    // Leer el contenido del archivo
    file.seekg(0, std::ios::end);
    std::size_t totalSize = file.tellg();
    file.seekg(0, std::ios::beg);

    const std::size_t maxDataSize = 512; // Espacio reservado para los datos de la imagen
    std::vector<char> buffer(maxDataSize);
    std::size_t bytesSent = 0;
    std::size_t numFrame = 0;
    std::size_t totalFrames = (totalSize + maxDataSize - 1) / maxDataSize; // Calcular total de frames

    while (bytesSent < totalSize)
    {
        file.read(buffer.data(), maxDataSize);
        std::size_t bytesRead = file.gcount();

        // Convertir datos a hexadecimal
        std::string hexData = toHex(buffer.data(), bytesRead);

        // Crear el JSON
        json jsonMessage = sendImgMapSlam(hexData, bytesRead, totalSize, numFrame, totalFrames);

        // Serializar el JSON
        std::string jsonStr = jsonMessage.dump();

        // Verificar que el tamaño total no exceda el límite
        if (jsonStr.size() > maxJsonSize)
        {
            throw std::runtime_error("El JSON generado excede el tamaño máximo permitido");
        }

        // Enviar el JSON por el socket
        boost::asio::write(socket_, boost::asio::buffer(jsonStr));

        bytesSent += bytesRead;
        numFrame++;
    }
}
