#ifndef CONTROLADOR_TURTLE_H
#define CONTROLADOR_TURTLE_H

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <string>

class ControladorTurtle {
public:
    explicit ControladorTurtle(rclcpp::Node::SharedPtr node);
    void ejecutarComando(const std::string &command);

private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;
};

#endif // CONTROLADOR_TURTLE_H
