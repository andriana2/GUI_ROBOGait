#include <rclcpp/rclcpp.hpp>
#include <filesystem>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("tf_service");

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
