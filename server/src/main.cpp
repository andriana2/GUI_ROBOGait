#include "include/servidor.h"
#include <rclcpp/rclcpp.hpp>
#include <thread>

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("node_manager");

    Servidor servidor(8080, node);

    std::thread servidor_thread([&servidor]() { servidor.run(); });

    rclcpp::spin(node);
    servidor_thread.join();

    rclcpp::shutdown();
    return 0;
}
