#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <string>

#include "utils.h"
#include "ProcessController.h"

#include <rclcpp/rclcpp.hpp>
#include "interface_srv/srv/get_robot_position.hpp"
#include <geometry_msgs/msg/twist.hpp>
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"
#include "nav2_msgs/action/follow_waypoints.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

#include <yaml-cpp/yaml.h> // leer el archivo yaml

class NodeManager
{
public:
    NodeManager(rclcpp::Node::SharedPtr node_ptr);
    void create_publisher(Target const &target);
    void close_publisher(Target const &target);

    // void create_publisher(Target const &target, std::string const &path = "");

    void execute_position(float const &linear, float const &angular);
    void refresh_map(std::string const &map_name = "temporal_map");

    struct FinalPosition getPositionRobotPixel(std::string const &path_yaml);

    void publish_initial_pose(double x, double y, double theta);
    void publish_goal_pose(double x, double y, double theta);
    void publish_waypoint_follower(const std::vector<geometry_msgs::msg::PoseStamped> &waypoints);

    void start_robot();
    void stop_robot();

    void start_bringup(std::string const &map_name);


    void reset();
    geometry_msgs::msg::Quaternion create_quaternion_from_yaw(double yaw, bool radianes = false);

private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;
    rclcpp::Client<interface_srv::srv::GetRobotPosition>::SharedPtr tf_service_client_;
    rclcpp::Publisher<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr initial_pose_publisher_;
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr goal_pose_publisher_;
    rclcpp_action::Client<nav2_msgs::action::FollowWaypoints>::SharedPtr waypoint_follower_client_;


    rclcpp::Node::SharedPtr node_manager;
    ProcessController processController;

    bool slam_launch_file = false;
    bool bringup_launch_file = false;
    bool start_robot_launch_file = false;
};

#endif // NODEMANAGER_H