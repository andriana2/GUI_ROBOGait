#include "rosnode.h"

RosNode::RosNode(QObject *parent) : QObject{parent}, Node{"joy_qt"}
{
    spin_thread = std::thread{std::bind(&RosNode::rosSpin, this)};
    pub.button = this->create_publisher<stringMsg>("button_state", 10);
    pub.ball = this->create_publisher<twistMsg>("ball_state", 10);
    turtlesim_started_ = false;
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
}

RosNode::~RosNode()
{
    rclcpp::shutdown();
}

void RosNode::rosSpin()
{
    rclcpp::spin(this->get_node_base_interface());
    rclcpp::shutdown();
}

void RosNode::buttonCallback(int number)
{
    if (number > 11)
    {
        return;
    }
    if (number == 10)
    {
        if (!turtlesim_started_)
        {
            std::system("ros2 run turtlesim turtlesim_node &"); // Ejecuta turtlesim en segundo plano
            turtlesim_started_ = true;
        }
    }
    else if (number == 11)
    {
        if (turtlesim_started_)
        {
            std::system("pkill turtlesim_node"); // Detiene el nodo de turtlesim
            turtlesim_started_ = false;
        }
    }
    else if (number == 0)
    {
        if (turtlesim_started_)
            moveUp();
    }
    else if (number == 1)
    {
        if (turtlesim_started_)
            moveDown();
    }
    else if (number == 2)
    {
        if (turtlesim_started_)
            moveLeft();
    }
    else if (number == 3)
    {
        if (turtlesim_started_)
            moveRight();
    }

    auto msg = example_interfaces::msg::String();
    msg.data = ros_message[number];
    pub.button->publish(msg);
}

void RosNode::ballStateCallback(int x, int y)
{
    geometry_msgs::msg::Twist msg;
    msg.linear.x = x;
    msg.linear.y = y;
    pub.ball->publish(msg);
}

void RosNode::moveUp() { sendVelocity(2.0, 0.0); }
void RosNode::moveDown() { sendVelocity(-2.0, 0.0); }
void RosNode::moveLeft() { sendVelocity(0.0, 2.0); }
void RosNode::moveRight() { sendVelocity(0.0, -2.0); }

void RosNode::sendVelocity(float linear, float angular)
{
    auto msg = geometry_msgs::msg::Twist();
    msg.linear.x = linear;
    msg.angular.z = angular;
    publisher_->publish(msg);
}