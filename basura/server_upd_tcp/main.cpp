#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <atomic>
#include <chrono>

using boost::asio::ip::udp;
using boost::asio::ip::tcp;

boost::asio::io_context io_context;

std::atomic<bool> connection_active{false};
udp::endpoint current_client_endpoint;

void handle_udp_acks(udp::socket& socket) {
    std::thread([&socket]() {
        char buffer[1024];
        int failed_acks = 0;
        const int max_failed_acks = 3;

        while (connection_active) {
            // Enviar ACK
            try {
                socket.send_to(boost::asio::buffer("ACK"), current_client_endpoint);
            } catch (...) {
                std::cerr << "Error enviando ACK\n";
                connection_active = false;
                break;
            }

            // Recibir ACK con timeout
            bool ack_received = false;
            for (int i = 0; i < 5; ++i) {
                boost::system::error_code ec;
                udp::endpoint sender;
                socket.non_blocking(true);
                size_t len = socket.receive_from(boost::asio::buffer(buffer), sender, 0, ec);

                if (!ec && len > 0 && sender == current_client_endpoint && 
                    std::string(buffer, len) == "ACK") {
                    ack_received = true;
                    failed_acks = 0;
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }

            if (!ack_received && ++failed_acks >= max_failed_acks) {
                std::cerr << "Conexión UDP perdida\n";
                connection_active = false;
                break;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }).detach();
}

void handle_tcp_connection(tcp::socket socket) {
    try {
        std::cout << "Conexión TCP establecida\n";
        
        while (connection_active) {
            char data[1024];
            boost::system::error_code ec;
            size_t len = socket.read_some(boost::asio::buffer(data), ec);
            
            if (ec || len == 0) {
                std::cerr << "Conexión TCP cerrada: " << ec.message() << "\n";
                break;
            }
            
            std::cout << "TCP recibido: " << std::string(data, len) << "\n";
            boost::asio::write(socket, boost::asio::buffer("ACK\n"));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error en conexión TCP: " << e.what() << "\n";
    }
    
    connection_active = false;
}

void udp_discovery(udp::socket& socket) {
    try {
        // Poner el socket en modo bloqueante para discovery
        socket.non_blocking(false);
        
        char buffer[1024] = {0};
        udp::endpoint client_ep;
        
        std::cout << "Esperando cliente UDP...\n";
        size_t len = socket.receive_from(boost::asio::buffer(buffer), client_ep);
        
        std::cout << "Cliente UDP encontrado: " << client_ep << "\n";
        std::cout << "Mensaje recibido: " << std::string(buffer, len) << "\n";

        if (std::string(buffer, len) == "DISCOVER") {
            socket.send_to(boost::asio::buffer("SERVER_ACK"), client_ep);
            current_client_endpoint = client_ep;
            connection_active = true;
            std::cout << "Cliente confirmado: " << client_ep << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error en descubrimiento UDP: " << e.what() << "\n";
        connection_active = false;
    }
}

int main() {
    try {
        // Configuración UDP
        udp::socket udp_socket(io_context, udp::endpoint(udp::v4(), 45454));
        std::cout << "Servidor UDP iniciado en 45454\n";

        while (true) {
            // 1. Fase de descubrimiento UDP (bloqueante)
            udp_discovery(udp_socket);

            if (!connection_active) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }

            // 2. Iniciar ACKs en segundo plano
            handle_udp_acks(udp_socket);

            // 3. Configurar TCP (una sola conexión)
            tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 5555));
            acceptor.set_option(tcp::acceptor::reuse_address(true));
            std::cout << "Esperando conexión TCP...\n";

            try {
                tcp::socket tcp_socket(io_context);
                acceptor.accept(tcp_socket);
                
                // 4. Manejar conexión TCP (bloqueante)
                handle_tcp_connection(std::move(tcp_socket));
            } catch (const std::exception& e) {
                std::cerr << "Error en conexión TCP: " << e.what() << "\n";
                connection_active = false;
            }

            // 5. Limpieza
            acceptor.close();
            std::cout << "Reiniciando servidor...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error fatal: " << e.what() << "\n";
        return 1;
    }

    return 0;
}