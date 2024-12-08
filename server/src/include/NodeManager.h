#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <string>
#include "utils.h"

class NodeManager
{
public:
    NodeManager(rclcpp::Node::SharedPtr node_ptr);
    void create_publisher(std::string const &where_publish);
    void execute_position(float const &linear, float const &angular);
    void refresh_map();

private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;
    
    rclcpp::Node::SharedPtr node_manager;
    void kill_launch_file(std::string const &command);

    bool rviz_active;
};

#endif // NODEMANAGER_H