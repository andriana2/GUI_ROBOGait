#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <boost/asio.hpp>
#include <iostream>
#include <array>
#include <functional>

class Servidor
{
public:
    using CommandCallback = std::function<void(const std::string &)>;

    Servidor(unsigned short port, CommandCallback callback);

    void run();

private:
    void startReceive();

    boost::asio::io_service io_service_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    std::array<char, 1024> recv_buffer_;
    CommandCallback callback_;
    unsigned int port;
};

#endif // SERVIDOR_H
