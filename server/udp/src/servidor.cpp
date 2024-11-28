#include "../include/servidor.h"
#include <iostream>

Servidor::Servidor(unsigned short port, CommandCallback callback)
    : socket_(io_service_, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)),
      callback_(callback)
{
    startReceive();
    this->port = port;
}

void Servidor::run()
{
    std::cout << "servidor escuchando puerto " << port;
    io_service_.run();
}

void Servidor::startReceive()
{
    socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
                               [this](boost::system::error_code ec, std::size_t bytes_recvd)
                               {
                                   if (!ec && bytes_recvd > 0)
                                   {
                                       std::string command(recv_buffer_.data(), bytes_recvd);
                                       callback_(command); // Llamar al callback con el comando recibido
                                   }
                                   startReceive(); // Continuar escuchando por nuevos mensajes
                               });
}
