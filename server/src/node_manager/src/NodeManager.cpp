#include "../include/NodeManager.h"
#include <iostream>

NodeManager::NodeManager(rclcpp::Node::SharedPtr node_ptr)
{
    node_manager = node_ptr;
    rviz_active = false;
}

void NodeManager::create_publisher(Target const &target)
{
    // if (target == Joystick_Position)
    // {
    //     if (!cmd_vel_publisher_)
    //     {
    //         cmd_vel_publisher_ = node_manager->create_publisher<geometry_msgs::msg::Twist>(CMD_TOPIC, 10);
    //         RCLCPP_INFO(node_manager->get_logger(), "Publisher /cmd_vel creado.");
    //     }
    // }
    // else if (target == Map_SLAM)
    // {
    //     if (!tf_service_client_)
    //     {
    //         // Crear el publisher si no existe
    //         tf_service_client_ = node_manager->create_client<interface_srv::srv::GetRobotPosition>("get_transform");
    //         RCLCPP_INFO(node_manager->get_logger(), "Robot Pose Client initialized.");
    //     }
    // }
}

void NodeManager::close_publisher(Target const &target)
{
    // if (target == Joystick_Position)
    // {
    //     if (!cmd_vel_publisher_)
    //     {
    //         cmd_vel_publisher_.reset();
    //         RCLCPP_INFO(node_manager->get_logger(), "Publisher /cmd_vel destroy.");
    //     }
    // }
    // else if (target == Map_SLAM)
    // {
    //     if (!tf_service_client_)
    //     {
    //         tf_service_client_.reset();
    //         RCLCPP_INFO(node_manager->get_logger(), "Robot Pose Client destroy.");
    //     }
    // }
}

// VERSION DE CUANDO ESTOY EN CASA
struct FinalPosition NodeManager::getPositionRobotPixel(std::string const &path_yaml)
{
    float x_robot = 0, y_robot = 0, yaw_robot = 0.0;
    struct FinalPosition final_position;

    // if (!tf_service_client_->wait_for_service(std::chrono::seconds(1)))
    // {
    //     RCLCPP_WARN(node_manager->get_logger(), "Service not available, waiting...");
    //     // return;
    // }
    // auto request = std::make_shared<interface_srv::srv::GetRobotPosition::Request>();

    // // Enviar solicitud y procesar la respuesta
    // auto future = tf_service_client_->async_send_request(request);

    try
    {
        // Esperar la respuesta con un timeout
        // auto response = future.get();
        // if (response->success == true)
        // {
        //     RCLCPP_INFO(node_manager->get_logger(), "La informacion ha llegado correctamente");
        //     x_robot = response->x;
        //     y_robot = response->y;
        //     yaw_robot = response->yaw;
        // }

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

// struct FinalPosition NodeManager::getPositionRobotPixel(std::string const &path_yaml)
// {
//     float x_robot, y_robot, yaw_robot;
//     struct FinalPosition final_position;

//     if (!tf_service_client_->wait_for_service(std::chrono::seconds(1)))
//     {
//         RCLCPP_WARN(node_manager->get_logger(), "Service not available, waiting...");
//         // return;
//     }
//     auto request = std::make_shared<interface_srv::srv::GetRobotPosition::Request>();

//     // Enviar solicitud y procesar la respuesta
//     auto future = tf_service_client_->async_send_request(request);

//     try
//     {
//         // Esperar la respuesta con un timeout
//         auto response = future.get();
//         if (response->success == true)
//         {
//             RCLCPP_INFO(node_manager->get_logger(), "La informacion ha llegado correctamente");
//             x_robot = response->x;
//             y_robot = response->y;
//             yaw_robot = response->yaw;
//         }

//         // Lo relacionado con el path

//         // Cargar el archivo .yaml
//         pri1(path_yaml);
//         YAML::Node config = YAML::LoadFile(path_yaml);

//         // Obtener la resolución
//         float resolution = config["resolution"].as<float>();
//         std::cout << "Resolución: " << resolution << std::endl;

//         // Obtener los valores de origen
//         auto origin = config["origin"];
//         float origin_x = origin[0].as<float>();
//         float origin_y = origin[1].as<float>();
//         std::cout << "Origen X: " << origin_x << ", Origen Y: " << origin_y << std::endl;
//         std::cout << "Robot X: " << x_robot << ", Robot Y: " << y_robot << std::endl;

//         final_position.x_pixel = static_cast<int>((x_robot - origin_x) / resolution);
//         final_position.y_pixel = static_cast<int>((y_robot - origin_y) / resolution);
//         final_position.yaw = -1 * yaw_robot;
//         std::cout << "Pixel X: " << final_position.x_pixel << ", Pixel Y: " << final_position.y_pixel << ", YAW: " << final_position.yaw << std::endl;
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "Error al leer el archivo YAML: " << e.what() << std::endl;
//     }
//     return final_position;
// }

void NodeManager::refresh_map(std::string const &map_name)
{
    std::string command = MAP_SAVER_CLI;
    command += "/" + replaceSpaces(map_name);
    // command += "/temporal_map";
    int result = system(command.c_str());

    if (result == 0)
    {
        std::cout << "El comando se ejecutó correctamente. " << command << std::endl;
    }
    else
    {
        std::cerr << "Hubo un error al ejecutar el comando. " << command << std::endl;
    }
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

void NodeManager::kill_launch_file(std::string const &command)
{
    FILE *fp = popen(command.c_str(), "r");
    if (!fp)
    {
        std::cerr << "Error al obtener el PID." << std::endl;
        return;
    }

    int pid;
    fscanf(fp, "%d", &pid); // Obtén el PID
    fclose(fp);

    // Si el PID fue encontrado, matamos el proceso.
    if (pid > 0)
    {
        std::cout << "Matando el proceso con PID: " << pid << std::endl;
        kill(pid, SIGTERM); // Enviar la señal SIGTERM para terminar el proceso
    }
    else
    {
        std::cerr << "Proceso no encontrado." << std::endl;
    }
}