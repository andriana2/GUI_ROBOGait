#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <functional>
#include <boost/asio.hpp>

class Servidor {
public:
    using CommandCallback = std::function<void(const std::string &)>;

    Servidor(int port, CommandCallback callback);
    void run();

private:
    void startAccept();
    void handleRead(boost::asio::ip::tcp::socket &socket);

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    CommandCallback callback_;
};

#endif // SERVIDOR_H

