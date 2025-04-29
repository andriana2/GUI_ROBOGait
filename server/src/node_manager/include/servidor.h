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
#include "HandleMsg.h"

using json = nlohmann::json;
using boost::asio::ip::udp;
using boost::asio::ip::tcp;

class NodeManager;

class Servidor
{
public:
    using CommandCallback = std::function<void(const std::string &)>;

    Servidor(int port_tcp, int port_udp, rclcpp::Node::SharedPtr node,
             boost::asio::io_context &io_context);
    void run();
    void closeServer();

private:
    void runUdp();
    void udp_discovery();
    void handle_udp_acks();
    void startAccept();
    void startRead();
    void resetConnection();
    // void signalHandler(int signal);

    void handleType(std::vector<std::string> const &jsons);

    void handleRequestMsg(const json &json_msg);
    void handleRequestImg(const json &json_msg);

    void sendMsg(const json &json_msg);
    void sendImageMap(const std::string &name_map, bool img_map_SLAM);

    // boost::asio::io_context io_context_;
    // // boost::asio::ip::tcp::acceptor acceptor_;
    // // std::optional<boost::asio::ip::tcp::acceptor> acceptor_;
    // std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
    // boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf buffer_;
    std::array<char, 1024> buffer_array;
    std::string buf_;
    CommandCallback callback_;

    boost::asio::io_context& io_context_;
    udp::socket udp_socket_;
    tcp::socket tcp_socket_;
    tcp::acceptor tcp_acceptor_;
    udp::endpoint client_endpoint_;
    std::atomic<bool> connection_active_;

    int ip_port_tcp_;
    int ip_port_udp_;

    NodeManager nodeManager;
};

#endif // SERVIDOR_H
