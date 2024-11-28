#include "../include/servidor.h"
#include <iostream>

Servidor::Servidor(int port, CommandCallback callback)
    : acceptor_(io_context_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)), callback_(callback) {}

void Servidor::run() {
    std::cout << "Servidor escuchando en el puerto " << acceptor_.local_endpoint().port() << std::endl;
    startAccept();
    io_context_.run();
}

void Servidor::startAccept() {
    auto socket = std::make_shared<asio::ip::tcp::socket>(io_context_);
    acceptor_.async_accept(*socket, [this, socket](const std::error_code &error) {
        if (!error) {
            std::cout << "Se ha establecido conexion con un cliente " << std::endl;
            handleRead(*socket);
        }
        startAccept();
    });
}

void Servidor::handleRead(asio::ip::tcp::socket &socket) {
    auto buffer = std::make_shared<asio::streambuf>();
    asio::async_read_until(socket, *buffer, "\n", [this, buffer](const std::error_code &error, std::size_t) {
        if (!error) {
            std::istream stream(buffer.get());
            std::string command;
            std::getline(stream, command);
            if (!command.empty()) {
                callback_(command);
            }
        }
    });
}
