#include <boost/asio.hpp>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <functional>
#include <iostream>
#include <array>
#include "include/servidor.h"
#include "include/controlador_turtle.h"
#include <thread>


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("servidor_udp");

    ControladorTurtle controlador(node);
    // Callback que recibe el comando y lo pasa al controlador
    auto callback = [&controlador](const std::string &command) {
        controlador.ejecutarComando(command);
    };

    // Iniciar el servidor UDP en el puerto 12345
    Servidor servidor(8080, callback);
    std::thread servidor_thread([&servidor]() {servidor.run();});
    rclcpp::spin(node);
    servidor_thread.join();

    rclcpp::shutdown();
    return 0;
}