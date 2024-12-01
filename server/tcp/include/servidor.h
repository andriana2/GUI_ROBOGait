#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <functional>
#include <boost/asio.hpp>
#include <memory>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <string>

#include "utils.h"
#include "header.h"
#include "NodeManager.h"

class Servidor
{
public:
    using CommandCallback = std::function<void(const std::string &)>;

    Servidor(int port, rclcpp::Node::SharedPtr node);
    void run();

private:
    void startAccept();
    void readHeader();
    void handleType(std::string const &type, int const &size, std::string const &target);
    void readBodyMsg(size_t const &size, std::string const &target);
    void processMsg(std::string const &data, std::string const &target);
    void readBodyImage(size_t const &size);
    void handleDisconnect(const boost::system::error_code &ec);
    void saveImage(const std::vector<uint8_t> &buffer);
    void resetConnection();

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf buffer_;
    std::string buf_;
    CommandCallback callback_;
    NodeManager nodeManager;
};

#endif // SERVIDOR_H
