#include "../include/NodeManager.h"
#include <iostream>

NodeManager::NodeManager(rclcpp::Node::SharedPtr node_ptr)
{
    node_manager = node_ptr;
}

void NodeManager::create_publisher(std::string const &where_publish)
{
    if (where_publish == get_info_message(Position_joystick))
    {
        cmd_vel_publisher_ = node_manager->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    }
}

void NodeManager::execute_position(int const &linear, int const &angular)
{
    geometry_msgs::msg::Twist twist_msg;
    twist_msg.linear.x = linear;
    twist_msg.angular.z = angular;
    cmd_vel_publisher_->publish(twist_msg);
    std::cout << "valores publicados liear: " << linear << " angular: " << angular << std::endl;
}