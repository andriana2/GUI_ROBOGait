#ifndef ROSNODE_H
#define ROSNODE_H

#include <QObject>
#include <QDebug>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"

#include <memory>
#include <cstdlib>  // Para std::system()
#include <thread> 
  // Para std::this_thread::sleep_for
#include <chrono> 

using stringMsg = example_interfaces::msg::String;
using twistMsg  = geometry_msgs::msg::Twist;

typedef struct{
    rclcpp::Publisher<stringMsg>::SharedPtr button;
    rclcpp::Publisher<twistMsg>::SharedPtr ball;
}Pub_t;

class RosNode : public QObject, public rclcpp::Node
{
    Q_OBJECT
public:
    explicit RosNode(QObject *parent = nullptr);
    ~RosNode();
    Q_INVOKABLE void buttonCallback(int number);
    Q_INVOKABLE void ballStateCallback(int x, int y);
    Q_INVOKABLE void moveUp(); 
    Q_INVOKABLE void moveDown();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();

private:
    Pub_t pub;
    void rosSpin();
    std::thread spin_thread;
    std::string ros_message[12] = {"up", "down", "left", "right",
                                   "circle", "rectangle", "x", "triangle",
                                   "right hand mode", "left hand mode","up2", "down2"};
    bool turtlesim_started_;
    void sendVelocity(float linear, float angular);
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;



};

#endif // ROSNODE_H
