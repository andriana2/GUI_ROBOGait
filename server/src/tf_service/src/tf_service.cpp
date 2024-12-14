#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include "interface_srv/srv/get_robot_position.hpp" // Cambia según tu archivo .srv
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

class RobotPoseService : public rclcpp::Node
{
public:
    RobotPoseService()
        : Node("robot_pose_service"), tf_buffer_(std::make_shared<tf2_ros::Buffer>(this->get_clock())), tf_listener_(*tf_buffer_)
    {
        service_ = this->create_service<interface_srv::srv::GetRobotPosition>(
            "get_robot_pose",
            std::bind(&RobotPoseService::handle_pose_request, this, std::placeholders::_1, std::placeholders::_2)
        );
        RCLCPP_INFO(this->get_logger(), "Robot Pose Service ready.");
    }

private:
    void handle_pose_request([[maybe_unused]] const std::shared_ptr<interface_srv::srv::GetRobotPosition::Request> request,
                             std::shared_ptr<interface_srv::srv::GetRobotPosition::Response> response)
    {
        try
        {
            // Obtener la transformación de "map" a "odom"
            auto map_to_odom = tf_buffer_->lookupTransform("map", "odom", tf2::TimePointZero);

            // Obtener la transformación de "odom" a "base_link"
            auto odom_to_base = tf_buffer_->lookupTransform("odom", "base_link", tf2::TimePointZero);

            // Combinar ambas transformaciones
            geometry_msgs::msg::TransformStamped map_to_base;
            tf2::doTransform(odom_to_base, map_to_base, map_to_odom);

            // Extraer posición
            response->x = map_to_base.transform.translation.x;
            response->y = map_to_base.transform.translation.y;

            // Convertir cuaternión a yaw
            tf2::Quaternion q(
                map_to_base.transform.rotation.x,
                map_to_base.transform.rotation.y,
                map_to_base.transform.rotation.z,
                map_to_base.transform.rotation.w);
            double roll, pitch, yaw;
            tf2::Matrix3x3(q).getRPY(roll, pitch, yaw);
            response->yaw = yaw;

            // RCLCPP_INFO(this->get_logger(), "Robot pose: x=%.2f, y=%.2f, yaw=%.2f", response->x, response->y, response->yaw);
        }
        catch (const tf2::TransformException &ex)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to get transform: %s", ex.what());
            response->x = response->y = response->yaw = 0.0;
        }
    }

    rclcpp::Service<interface_srv::srv::GetRobotPosition>::SharedPtr service_;
    std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
    tf2_ros::TransformListener tf_listener_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotPoseService>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
