#include "../include/NodeManager.h"
#include <iostream>

NodeManager::NodeManager(rclcpp::Node::SharedPtr node_ptr) : processController()
{
    node_manager = node_ptr;
}

void NodeManager::create_publisher(Target const &target)
{
#if !EN_CASA
    pri1("Estoy en create_publisher");
    if (target == Joystick_Position)
    {
        if (!cmd_vel_publisher_)
        {
            cmd_vel_publisher_ = node_manager->create_publisher<geometry_msgs::msg::Twist>(CMD_VEL_TOPIC, 10);
            RCLCPP_INFO(node_manager->get_logger(), "Publisher /cmd_vel creado.");
        }
    }
    else if (target == Request_Map_SLAM)
    {
        if (slam_launch_file == false)
        {
            processController.startProcess(NAME_CARTOGRAPHER_LAUNCH, CARTOGRAPHER_LAUNCH);
            slam_launch_file = true;
        }
        if (!tf_service_client_)
        {
            // Crear el publisher si no existe
            tf_service_client_ = node_manager->create_client<interface_srv::srv::GetRobotPosition>("get_transform");
            RCLCPP_INFO(node_manager->get_logger(), "Robot Pose Client initialized.");
        }
    }
    else if (target == Goal_Pose)
    {
        if (!initial_pose_publisher_)
        {
            initial_pose_publisher_ = node_manager->create_publisher<geometry_msgs::msg::PoseWithCovarianceStamped>(INITIAL_POSE_TOPIC, 10);
            RCLCPP_INFO(node_manager->get_logger(), "Publisher /initialpose.");
        }
        if (!goal_pose_publisher_)
        {
            goal_pose_publisher_ = node_manager->create_publisher<geometry_msgs::msg::PoseStamped>(GOAL_POSE_TOPIC, 10);
            RCLCPP_INFO(node_manager->get_logger(), "Publisher /goal_pose.");
        }
    }
    else if (target == Waypoint_Follower)
    {
        // if (!goal_pose_launch_file)
        // {
        //     processController.startProcess(NAME_NAV2_BRINGUP_LAUNCH, NAV2_BRINGUP_LAUNCH);
        //     goal_pose_launch_file = true;
        // }
        if (!initial_pose_publisher_)
        {
            initial_pose_publisher_ = node_manager->create_publisher<geometry_msgs::msg::PoseWithCovarianceStamped>(INITIAL_POSE_TOPIC, 10);
            RCLCPP_INFO(node_manager->get_logger(), "Publisher /initialpose.");
        }
        if (!waypoint_follower_client_)
        {
            waypoint_follower_client_ = rclcpp_action::create_client<nav2_msgs::action::FollowWaypoints>(node_manager, WAYPOINT_FOLLOWER_ACTION);
            RCLCPP_INFO(node_manager->get_logger(), "Create Cliente /waypoint_follower.");
            while (!waypoint_follower_client_->wait_for_action_server())
            {
                RCLCPP_INFO(node_manager->get_logger(), "Esperando al servidor de acción...");
                rclcpp::sleep_for(std::chrono::seconds(1));
            }
        }
    }
#endif
}

void NodeManager::close_publisher(Target const &target)
{
#if !EN_CASA
    if (target == Joystick_Position)
    {
        if (!cmd_vel_publisher_)
        {
            cmd_vel_publisher_.reset();
            RCLCPP_INFO(node_manager->get_logger(), "Close Publisher /cmd_vel destroy.");
        }
    }
    else if (target == Request_Map_SLAM)
    {
        if (slam_launch_file)
        {
            processController.stopProcess(NAME_CARTOGRAPHER_LAUNCH);
            slam_launch_file = false;
        }
        if (!tf_service_client_)
        {
            tf_service_client_.reset();
            RCLCPP_INFO(node_manager->get_logger(), "Close Robot Pose Client destroy.");
        }
    }
    else if (target == Goal_Pose)
    {
        if (goal_pose_launch_file)
        {
            processController.stopProcess(NAME_NAV2_BRINGUP_LAUNCH);
            goal_pose_launch_file = false;
        }
        if (!initial_pose_publisher_)
        {
            initial_pose_publisher_.reset();
            RCLCPP_INFO(node_manager->get_logger(), "Close Publisher /initialpose.");
        }
        if (!goal_pose_publisher_)
        {
            goal_pose_publisher_.reset();
            RCLCPP_INFO(node_manager->get_logger(), "Close Publisher /goal_pose.");
        }
    }
    else if (target == Waypoint_Follower)
    {
        if (goal_pose_launch_file)
        {
            processController.stopProcess(NAME_NAV2_BRINGUP_LAUNCH);
            goal_pose_launch_file = false;
        }
        if (!initial_pose_publisher_)
        {
            initial_pose_publisher_.reset();
            RCLCPP_INFO(node_manager->get_logger(), "Close Publisher /initialpose.");
        }
        if (!waypoint_follower_client_)
        {
            waypoint_follower_client_.reset();
            RCLCPP_INFO(node_manager->get_logger(), "Close Cliente /waypoint_follower.");
        }
    }
#endif
}

// VERSION DE CUANDO ESTOY EN CASA
#if EN_CASA
struct FinalPosition NodeManager::getPositionRobotPixel(std::string const &path_yaml)
{
    float x_robot = 0, y_robot = 0, yaw_robot = 0.0;
    struct FinalPosition final_position;

    pri1(path_yaml);
    YAML::Node config = YAML::LoadFile(path_yaml);
    float resolution = config["resolution"].as<float>();
    auto origin = config["origin"];
    float origin_x = origin[0].as<float>();
    float origin_y = origin[1].as<float>();

    final_position.x_pixel = static_cast<int>((x_robot - origin_x) / resolution);
    final_position.y_pixel = static_cast<int>((y_robot - origin_y) / resolution);
    final_position.yaw = -1 * yaw_robot;

    return final_position;
}

#else
// VERSION DE CUANDO ESTOY EN LA UNIVERSIDAD
struct FinalPosition NodeManager::getPositionRobotPixel(std::string const &path_yaml)
{
    float x_robot, y_robot, yaw_robot;
    struct FinalPosition final_position;

    if (!tf_service_client_->wait_for_service(std::chrono::seconds(1)))
    {
        RCLCPP_WARN(node_manager->get_logger(), "Service not available, waiting...");
        // return;
    }
    auto request = std::make_shared<interface_srv::srv::GetRobotPosition::Request>();

    // Enviar solicitud y procesar la respuesta
    auto future = tf_service_client_->async_send_request(request);

    try
    {
        // Esperar la respuesta con un timeout
        auto response = future.get();
        if (response->success == true)
        {
            RCLCPP_INFO(node_manager->get_logger(), "La informacion ha llegado correctamente");
            x_robot = response->x;
            y_robot = response->y;
            yaw_robot = response->yaw;
        }

        // Lo relacionado con el path

        // Cargar el archivo .yaml
        pri1(path_yaml);
        YAML::Node config = YAML::LoadFile(path_yaml);

        // Obtener la resolución
        float resolution = config["resolution"].as<float>();
        std::cout << "Resolución: " << resolution << std::endl;

        // Obtener los valores de origen
        auto origin = config["origin"];
        float origin_x = origin[0].as<float>();
        float origin_y = origin[1].as<float>();
        std::cout << "Origen X: " << origin_x << ", Origen Y: " << origin_y << std::endl;
        std::cout << "Robot X: " << x_robot << ", Robot Y: " << y_robot << std::endl;

        final_position.x_pixel = static_cast<int>((x_robot - origin_x) / resolution);
        final_position.y_pixel = static_cast<int>((y_robot - origin_y) / resolution);
        final_position.yaw = -1 * yaw_robot;
        std::cout << "Pixel X: " << final_position.x_pixel << ", Pixel Y: " << final_position.y_pixel << ", YAW: " << final_position.yaw << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error al leer el archivo YAML: " << e.what() << std::endl;
    }
    return final_position;
}
#endif

void NodeManager::refresh_map(std::string const &map_name)
{
    std::string command = MAP_SAVER_CLI;
    command += "/" + replaceSpaces(map_name);
    int result = system(command.c_str());

    if (result == 0)
        std::cout << "El comando se ejecutó correctamente. " << command << std::endl;
    else
        std::cerr << "Hubo un error al ejecutar el comando. " << command << std::endl;
}

void NodeManager::execute_position(float const &linear, float const &angular)
{
    if (cmd_vel_publisher_)
    {
        geometry_msgs::msg::Twist twist_msg;
        twist_msg.linear.x = linear;
        twist_msg.angular.z = angular;
        cmd_vel_publisher_->publish(twist_msg);
        std::cout << "valores publicados linear: " << linear << " angular: " << angular << std::endl;
    }
}

void NodeManager::start_robot()
{
    if (!start_robot_launch_file)
    {
        pri1("Comienzo robot");
        // processController.startProcess(START_ROBOT, NAME_START_ROBOT);
        // start_robot_launch_file = true;
    }
}

void NodeManager::stop_robot()
{
    if (start_robot_launch_file)
    {
        processController.stopProcess(NAME_START_ROBOT);
        start_robot_launch_file = false;
    }
}

void NodeManager::publish_initial_pose(double x, double y, double theta)
{
    // Crear el mensaje de tipo PoseWithCovarianceStamped
    auto msg = geometry_msgs::msg::PoseWithCovarianceStamped();
    msg.header.frame_id = "map"; // Referencia al marco del mapa

    // Asignar la posición (x, y) y orientación (theta)
    msg.pose.pose.position.x = x;
    msg.pose.pose.position.y = y;
    msg.pose.pose.position.z = 0.0; // Generalmente, el robot opera en un plano 2D

    // Convertir theta (en radianes) a cuaternión
    msg.pose.pose.orientation = create_quaternion_from_yaw(theta);

    // Configurar la matriz de covarianza
    for (int i = 0; i < 36; i++)
    {
        msg.pose.covariance[i] = 0.0;
    }
    msg.pose.covariance[0] = 0.05;  // Varianza en x (50 cm)
    msg.pose.covariance[7] = 0.05;  // Varianza en y (50 cm)
    msg.pose.covariance[35] = 0.15; // Varianza en yaw (15 grados)

    // Publicar el mensaje
    initial_pose_publisher_->publish(msg);
    RCLCPP_INFO(node_manager->get_logger(), "Pose inicial publicada: x=%.2f, y=%.2f, theta=%.2f", x, y, theta);
}

geometry_msgs::msg::Quaternion NodeManager::create_quaternion_from_yaw(double yaw, bool radianes)
{
    if (!radianes)
    {
        yaw = yaw * M_PI / 180.0;
    }
    // double yaw_radians = yaw * M_PI / 180.0;
    geometry_msgs::msg::Quaternion quaternion;
    quaternion.x = 0.0;
    quaternion.y = 0.0;
    quaternion.z = sin(yaw / 2.0);
    quaternion.w = cos(yaw / 2.0);
    std::cout << " z=" << quaternion.z << ", w=" << quaternion.w << std::endl;
    return quaternion;
}

void NodeManager::publish_goal_pose(double x, double y, double theta)
{
    geometry_msgs::msg::Quaternion orientation = create_quaternion_from_yaw(theta);
    geometry_msgs::msg::PoseStamped goal_pose;
    goal_pose.header.frame_id = "map";        // Usualmente 'map' o 'odom'
    goal_pose.pose.position.x = x;            // Establecer la posición x
    goal_pose.pose.position.y = y;            // Establecer la posición y
    goal_pose.pose.position.z = 0.0;          // Z usualmente es 0.0 para el plano 2D
    goal_pose.pose.orientation = orientation; // Establecer la orientación

    // Publicar el mensaje
    goal_pose_publisher_->publish(goal_pose);
    RCLCPP_INFO(node_manager->get_logger(), "Publicando goal_pose: (x: %.2f, y: %.2f, theta: %.2f)", x, y, theta);
}

void NodeManager::start_goal_pose(std::string const &map_name)
{
    if (!goal_pose_launch_file)
    {
        std::string bringup = NAV2_BRINGUP_LAUNCH;
        bringup += PATH2MAP;
        bringup += "/" + map_name + ".yaml";
        pri1("Start bring up GOAL POSE:" + bringup);
        processController.startProcess(NAME_NAV2_BRINGUP_LAUNCH, bringup);
        goal_pose_launch_file = true;
    }
}

void NodeManager::start_waypoint_follower(std::string const &map_name)
{
    if (!waypoint_follower_launch_file)
    {
        std::string bringup = NAV2_BRINGUP_LAUNCH;
        bringup += PATH2MAP;
        bringup += "/" + map_name + ".yaml";
        pri1("Start bring up:" + bringup);
        processController.startProcess(NAME_NAV2_BRINGUP_LAUNCH, bringup);
        waypoint_follower_launch_file = true;
    }
}

void NodeManager::publish_waypoint_follower(const std::vector<geometry_msgs::msg::PoseStamped> &waypoints)
{
    if (waypoint_follower_client_)
    {
        auto goal_msg = nav2_msgs::action::FollowWaypoints::Goal();
        goal_msg.poses = waypoints;

        auto send_goal_options = rclcpp_action::Client<nav2_msgs::action::FollowWaypoints>::SendGoalOptions();
        send_goal_options.result_callback = [](const auto &future)
        {
            auto result = future.result; // Acceder al resultado correctamente
            if (result == nullptr)
            {
                RCLCPP_ERROR(rclcpp::get_logger("NodeManager"), "Waypoint following failed");
            }
            else
            {
                RCLCPP_INFO(rclcpp::get_logger("NodeManager"), "Waypoint following succeeded");
            }
        };

        waypoint_follower_client_->async_send_goal(goal_msg, send_goal_options);
    }
}

void NodeManager::reset()
{
    processController.stopAllProcesses();
}