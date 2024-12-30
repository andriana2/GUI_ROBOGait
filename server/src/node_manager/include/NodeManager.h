#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <string>
#include "utils.h"
#include "interface_srv/srv/get_robot_position.hpp"

#include <yaml-cpp/yaml.h> // leer el archivo yaml

class NodeManager
{
public:
    NodeManager(rclcpp::Node::SharedPtr node_ptr);
    void create_publisher(Target const &target);

    void execute_position(float const &linear, float const &angular);
    void refresh_map();
    struct FinalPosition getPositionRobotPixel(std::string const &path_yaml);

private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;
    rclcpp::Client<interface_srv::srv::GetRobotPosition>::SharedPtr tf_service_client_;

    rclcpp::Node::SharedPtr node_manager;
    void kill_launch_file(std::string const &command);

    bool rviz_active;
    struct GetPosition position_robot;
    struct FinalPosition final_position_pixel;
};

#endif // NODEMANAGER_H