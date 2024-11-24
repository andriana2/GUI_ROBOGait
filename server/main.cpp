#include "include/servidor.h"
#include "include/controlador_turtle.h"
#include <rclcpp/rclcpp.hpp>
#include <thread>

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("turtlesim_controller");

    ControladorTurtle controlador(node);

    Servidor servidor(8080, [&controlador](const std::string &command) {
        controlador.ejecutarComando(command);
    });

    std::thread servidor_thread([&servidor]() { servidor.run(); });

    rclcpp::spin(node);
    servidor_thread.join();

    rclcpp::shutdown();
    return 0;
}
