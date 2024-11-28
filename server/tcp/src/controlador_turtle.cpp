#include "../include/controlador_turtle.h"
#include <iostream>

ControladorTurtle::ControladorTurtle(rclcpp::Node::SharedPtr node) {
    cmd_vel_publisher_ = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
}

void ControladorTurtle::ejecutarComando(const std::string &command) {
    geometry_msgs::msg::Twist twist_msg;

    if (command == "Recto") {
        twist_msg.linear.x = 1.0;
        twist_msg.angular.z = 0.0;
    } else if (command == "Atras") {
        twist_msg.linear.x = -1.0;
        twist_msg.angular.z = 0.0;
    } else if (command == "Giro_Izquierda") {
        twist_msg.linear.x = 0.0;
        twist_msg.angular.z = 1.0;
    } else if (command == "Giro_Derecha") {
        twist_msg.linear.x = 0.0;
        twist_msg.angular.z = -1.0;
    } else if (command == "Mas_Rapido") {
        twist_msg.linear.x = 2.0;
        twist_msg.angular.z = 0.0;
    } else if (command == "Mas_Lento") {
        twist_msg.linear.x = 0.5;
        twist_msg.angular.z = 0.0;
    } else if (command == "Stop") {
        twist_msg.linear.x = 0.0;
        twist_msg.angular.z = 0.0;
    } else {
        std::cerr << "Comando desconocido: " << command << std::endl;
        return;
    }

    cmd_vel_publisher_->publish(twist_msg);
    std::cout << "Comando ejecutado: " << command << std::endl;
}
