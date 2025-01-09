#include "include/servidor.h"
#include <rclcpp/rclcpp.hpp>
#include <thread>
#include "include/header.h"
#include <filesystem>
#include <boost/asio/signal_set.hpp>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("node_manager");

    Servidor servidor(8080, node);

    // Al hacer control c que no de error y se cierre de forma segura
    // When doing control c it does not give an error and closes safely
    boost::asio::io_context io_context;
    boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);

    signals.async_wait([&servidor](const boost::system::error_code &, int signal)
                       {
            std::cout << "\nSeñal de finalización capturada. Cerrando el servidor de forma segura...\n";
            servidor.closeServer();
            exit(0); });

    // Ejecuta Boost.Asio en un hilo separado
    std::thread boost_thread([&io_context]()
                             { io_context.run(); });

    // Ejecuta el servidor en otro hilo
    std::thread servidor_thread([&servidor]()
                                { servidor.run(); });

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
