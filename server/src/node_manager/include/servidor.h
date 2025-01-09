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
#include <filesystem>

#include <nlohmann/json.hpp>

#include <threads.h>

#include <opencv2/opencv.hpp>

#include "utils.h"
#include "header.h"
#include "toJson.h"

#include "NodeManager.h"

using json = nlohmann::json;

class NodeManager;

class Servidor
{
public:
    using CommandCallback = std::function<void(const std::string &)>;

    Servidor(int port, rclcpp::Node::SharedPtr node);
    void run();
    void closeServer();

private:
    void startAccept();
    void startRead();
    void resetConnection();
    // void signalHandler(int signal);

    void handleType(std::vector<std::string> const &jsons);
    void sendMsg(const json &json_msg);

    void sendImageMap(const std::string &name_map);

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf buffer_;
    std::array<char, 1024> buffer_array;
    std::string buf_;
    CommandCallback callback_;
    NodeManager nodeManager;
};

#endif // SERVIDOR_H
