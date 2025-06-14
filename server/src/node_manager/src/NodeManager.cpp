#include "../include/NodeManager.h"

#include <iostream>

NodeManager::NodeManager(rclcpp::Node::SharedPtr node_ptr) : processController()
{
    node_manager = node_ptr;
}
void NodeManager::create_subscription(Target const &target)
{
    if (target == All_Information_Pose)
    {
        if (!plan_path_subscriber_)
        {
            plan_path_subscriber_ = node_manager->create_subscription<nav_msgs::msg::Path>(
                "/global_plan", 10, std::bind(&NodeManager::topic_plan_callback, this, std::placeholders::_1));
            RCLCPP_INFO(node_manager->get_logger(), "Suscriptor global plan created, waiting messages...");
        }
    }

    if (target == Battery_Level)
    {
        if (!battert_subscription_)
        {
            battert_subscription_ = node_manager->create_subscription<sensor_msgs::msg::BatteryState>(
                "/rover_mini/battery_status", 10, std::bind(&NodeManager::battery_callback, this, std::placeholders::_1));
            RCLCPP_INFO(node_manager->get_logger(), "Suscriptor /rover_mini/battery_status created, waiting messages...");
        }
    }
}

void NodeManager::close_subscription(Target const &target)
{
    if (target == Battery_Level)
    {
        if (!battert_subscription_)
        {
            battert_subscription_.reset();
            RCLCPP_INFO(node_manager->get_logger(), "Close Publisher /rover_mini/battery_status destroy.");
        }
    }
}
void NodeManager::open_server_database()
{
    YAML::Node config;
    try
    {
        std::string path_ = PATH;
        config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading YAML file: " << e.what() << std::endl;
    }

    if (processController.listProcessesString().find(config["NAME_DATABASE"].as<std::string>()) == std::string::npos)
    {
        std::string name_server_database = config["NAME_DATABASE"].as<std::string>();
        std::string path_server_database = PATH + config["DATABASE"].as<std::string>();
        pri1("Path to database: " + path_server_database);
        std::string path2comand = PATH + config["PATH2DATABASE"].as<std::string>();
        std::string command = "python3 " + path2comand + " " + path_server_database;
        processController.startProcess(name_server_database, command);
        server_database_active = true;
    }
}

void NodeManager::close_server_database()
{
    if (server_database_active)
    {
        YAML::Node config;
        try
        {
            std::string path_ = PATH;
            config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading YAML file: " << e.what() << std::endl;
        }
        std::string name_server_database = config["NAME_DATABASE"].as<std::string>();
        processController.stopProcess(name_server_database);
        server_database_active = false;
    }
}

void NodeManager::create_publisher(Target const &target)
{
#if !EN_CASA
    // pri1("Estoy en create_publisher");
    if (target == Joystick_Position)
    {
        if (!cmd_vel_publisher_)
        {
            YAML::Node config;
            try
            {
                std::string path_ = PATH;
                config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error loading YAML file: " << e.what() << std::endl;
            }
            std::string cmd_vel = config["CMD_VEL_TOPIC"].as<std::string>();

            cmd_vel_publisher_ = node_manager->create_publisher<geometry_msgs::msg::Twist>(cmd_vel, 10);
            RCLCPP_INFO(node_manager->get_logger(), "Publisher /cmd_vel created.");
        }
    }
    else if (target == Request_Map_SLAM)
    {
        if (slam_launch_file == false)
        {
            YAML::Node config;
            try
            {
                std::string path_ = PATH;
                config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error loading YAML file: " << e.what() << std::endl;
            }
            std::string name_cartographer = config["NAME_CARTOGRAPHER_LAUNCH"].as<std::string>();
            std::string launch_cartographer = config["CARTOGRAPHER_LAUNCH"].as<std::string>();

            processController.startProcess(name_cartographer, launch_cartographer);
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
        // if (!initial_pose_publisher_)
        // {
        //     initial_pose_publisher_ = node_manager->create_publisher<geometry_msgs::msg::PoseWithCovarianceStamped>(INITIAL_POSE_TOPIC, 10);
        //     RCLCPP_INFO(node_manager->get_logger(), "Publisher /initialpose.");
        // }
        if (!goal_pose_publisher_)
        {
            YAML::Node config;
            try
            {
                std::string path_ = PATH;
                config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error loading YAML file: " << e.what() << std::endl;
            }
            std::string goal_pose_topic = config["GOAL_POSE_TOPIC"].as<std::string>();

            goal_pose_publisher_ = node_manager->create_publisher<geometry_msgs::msg::PoseStamped>(goal_pose_topic, 10);
            RCLCPP_INFO(node_manager->get_logger(), "Publisher /goal_pose.");
        }
        // if (!plan_path_subscriber_)
        // {
        //     plan_path_subscriber_ = node_manager->create_subscription<nav_msgs::msg::Path>(
        //         "/plan", 10, std::bind(&NodeManager::topic_plan_callback, this, std::placeholders::_1));
        // }
    }
    else if (target == Waypoint_Follower)
    {
        // if (!initial_pose_publisher_)
        // {
        //     initial_pose_publisher_ = node_manager->create_publisher<geometry_msgs::msg::PoseWithCovarianceStamped>(INITIAL_POSE_TOPIC, 10);
        //     RCLCPP_INFO(node_manager->get_logger(), "Publisher /initialpose.");
        // }
        if (!waypoint_follower_client_)
        {
            YAML::Node config;
            try
            {
                std::string path_ = PATH;
                config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error loading YAML file: " << e.what() << std::endl;
            }
            std::string waypoint_follower_action = config["WAYPOINT_FOLLOWER_ACTION"].as<std::string>();

            waypoint_follower_client_ = rclcpp_action::create_client<nav2_msgs::action::FollowWaypoints>(node_manager, waypoint_follower_action);
            RCLCPP_INFO(node_manager->get_logger(), "Create Cliente /waypoint_follower.");
            while (!waypoint_follower_client_->wait_for_action_server())
            {
                RCLCPP_INFO(node_manager->get_logger(), "Esperando al servidor de acción...");
                rclcpp::sleep_for(std::chrono::seconds(1));
            }
        }
    }
    else if (target == Initial_Pose)
    {
        if (!initial_pose_publisher_)
        {
            YAML::Node config;
            try
            {
                std::string path_ = PATH;
                config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error loading YAML file: " << e.what() << std::endl;
            }
            std::string initial_pose_topic = config["INITIAL_POSE_TOPIC"].as<std::string>();

            initial_pose_publisher_ = node_manager->create_publisher<geometry_msgs::msg::PoseWithCovarianceStamped>(initial_pose_topic, 10);
            RCLCPP_INFO(node_manager->get_logger(), "Publisher /initialpose.");
        }
        if (!tf_service_client_)
        {
            // Crear el publisher si no existe
            tf_service_client_ = node_manager->create_client<interface_srv::srv::GetRobotPosition>("get_transform");
            RCLCPP_INFO(node_manager->get_logger(), "Robot Pose Client initialized.");
        }
    }
#else
    if (target == Goal_Pose)
    {
        if (!plan_path_subscriber_)
        {
            plan_path_subscriber_ = node_manager->create_subscription<nav_msgs::msg::Path>(
                "/plan", 10, std::bind(&NodeManager::topic_plan_callback, this, std::placeholders::_1));
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
            YAML::Node config;
            try
            {
                std::string path_ = PATH;
                config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error loading YAML file: " << e.what() << std::endl;
            }
            std::string name_cartographer = config["NAME_CARTOGRAPHER_LAUNCH"].as<std::string>();

            processController.stopProcess(name_cartographer);

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
        if (bringup_launch_file)
        {
            YAML::Node config;
            try
            {
                std::string path_ = PATH;
                config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error loading YAML file: " << e.what() << std::endl;
            }
            if (navegando)
            {
                std::string name_nav2_bringup = config["NAME_NAV2_BRINGUP_LAUNCH"].as<std::string>();
                processController.stopProcess(name_nav2_bringup);
            }
            else
            {
                // std::string name_nav2_bringup = config["NAME_PERSON_FOLLOWER"].as<std::string>();
                // processController.stopProcess(name_nav2_bringup);

                processController.stopProcess(config["NAME_NAVIGATION_ROBOT"].as<std::string>());
                processController.stopProcess(config["NAME_DISTANCE_TRACKER"].as<std::string>());
                processController.stopProcess(config["NAME_CAMERA_CONTROLLER"].as<std::string>());
                processController.stopProcess(config["NAME_DYNAMIXEL"].as<std::string>());
                processController.stopProcess(config["NAME_PRUEBA"].as<std::string>());
                processController.startProcess(config["NAME_START_ROBOT"].as<std::string>(), config["START_ROBOT"].as<std::string>());
            }
            bringup_launch_file = false;
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
        if (!plan_path_subscriber_)
        {
            plan_path_subscriber_.reset();
            RCLCPP_INFO(node_manager->get_logger(), "Close Subscriber /plan.");
        }
        if (!tf_service_client_)
        {
            tf_service_client_.reset();
            RCLCPP_INFO(node_manager->get_logger(), "Close Robot Pose Client destroy.");
        }
    }
    else if (target == Waypoint_Follower)
    {
        if (bringup_launch_file)
        {
            YAML::Node config;
            try
            {
                std::string path_ = PATH;
                config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error loading YAML file: " << e.what() << std::endl;
            }
            std::string nav2_bringup;
            if (navegando)
            {
                nav2_bringup = config["NAME_NAV2_BRINGUP_LAUNCH"].as<std::string>();
                processController.stopProcess(nav2_bringup);
            }
            else
            {
                processController.stopProcess(config["NAME_NAVIGATION_ROBOT"].as<std::string>());
                processController.stopProcess(config["NAME_DISTANCE_TRACKER"].as<std::string>());
                processController.stopProcess(config["NAME_CAMERA_CONTROLLER"].as<std::string>());
                processController.stopProcess(config["NAME_DYNAMIXEL"].as<std::string>());
                processController.stopProcess(config["NAME_PRUEBA"].as<std::string>());

                processController.startProcess(config["NAME_START_ROBOT"].as<std::string>(), config["START_ROBOT"].as<std::string>());
            }
            bringup_launch_file = false;
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
        if (!tf_service_client_)
        {
            tf_service_client_.reset();
            RCLCPP_INFO(node_manager->get_logger(), "Close Robot Pose Client destroy.");
        }
    }
#else
    if (target == Goal_Pose)
    {
        if (!tf_service_client_)
        {
            tf_service_client_.reset();
            RCLCPP_INFO(node_manager->get_logger(), "Close Robot Pose Client destroy.");
        }
        if (!plan_path_subscriber_)
        {
            plan_path_subscriber_.reset();
            RCLCPP_INFO(node_manager->get_logger(), "Close Subscriber /plan.");
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
    final_position.yaw = yaw_robot;

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
        final_position.yaw = yaw_robot;
        std::cout << "Pixel X: " << final_position.x_pixel << ", Pixel Y: " << final_position.y_pixel << ", YAW: " << final_position.yaw << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error al leer el archivo YAML: " << e.what() << std::endl;
    }
    return final_position;
}
#endif

void NodeManager::execute_command(std::string const &command)
{
    int result = system(command.c_str());
    if (result == 0)
        std::cout << "El comando se ejecutó correctamente. " << command << std::endl;
    else
        std::cerr << "Hubo un error al ejecutar el comando. " << command << std::endl;
}

void NodeManager::refresh_map(std::string const &map_name)
{
#if !EN_CASA

    YAML::Node config;
    try
    {
        std::string path_ = PATH;
        config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading YAML file: " << e.what() << std::endl;
    }
    std::string map_saver_cli = config["MAP_SAVER_CLI"].as<std::string>();

    std::string command = map_saver_cli + PATH + config["PATH2MAP"].as<std::string>();
    command += "/" + replaceSpaces(map_name);
    // int result = system(command.c_str());
    std::thread t(&NodeManager::execute_command, this, command);
    t.detach();

    // processController.startProcess(map_saver_cli, command);

    // if (result == 0)
    //     std::cout << "El comando se ejecutó correctamente. " << command << std::endl;
    // else
    //     std::cerr << "Hubo un error al ejecutar el comando. " << command << std::endl;
#endif
}
// OPCOIn b
// void NodeManager::refresh_map(const std::string &map_name)
// {
//   // 1) Cliente al servicio; se crea una sola vez y se reutiliza.
//   static auto save_map_client =
//       node_->create_client<nav2_msgs::srv::SaveMap>("/map_saver/save_map");

//   if (!save_map_client->wait_for_service(std::chrono::seconds(2))) {
//     RCLCPP_ERROR(node_->get_logger(), "Servicio /map_saver/save_map no disponible");
//     return;
//   }

//   // 2) Construye la petición:
//   auto req = std::make_shared<nav2_msgs::srv::SaveMap::Request>();
//   req->map_topic        = "/map";
//   req->map_url          = "/home/robogait/GUI_ROBOGait/server/maps/" +
//                           replaceSpaces(map_name) + ".yaml";
//   req->image_format     = "png";       // pgm | png | bmp
//   req->map_mode         = "trinary";   // trinary | scale | raw
//   req->free_thresh      = 0.25;
//   req->occupied_thresh  = 0.65;

//   // 3) Llamada asíncrona → no bloquea tu hilo de control
//   save_map_client->async_send_request(
//       req,
//       [this, map_name](auto future) {
//         if (future.get()->result)
//           RCLCPP_INFO(node_->get_logger(), "Mapa «%s» guardado", map_name.c_str());
//         else
//           RCLCPP_ERROR(node_->get_logger(), "Falló al guardar «%s»", map_name.c_str());
//       });
// }

void NodeManager::create_global_plan(RealPositionMeters const &initialpose, RealPositionMeters const &goalpose, std::string const &pathMap)
{
#if !EN_CASA

#endif
}

void NodeManager::execute_position(float const &linear, float const &angular)
{
#if !EN_CASA

    if (cmd_vel_publisher_)
    {
        geometry_msgs::msg::Twist twist_msg;
        twist_msg.linear.x = linear;
        twist_msg.angular.z = angular;
        cmd_vel_publisher_->publish(twist_msg);
        std::cout << "valores publicados linear: " << linear << " angular: " << angular << std::endl;
    }
#endif
}

void NodeManager::start_robot()
{
#if !EN_CASA

    if (!start_robot_launch_file)
    {
        YAML::Node config;
        try
        {
            std::string path_ = PATH;
            config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading YAML file: " << e.what() << std::endl;
        }
        std::string start_robot = config["START_ROBOT"].as<std::string>();
        std::string start_robot_name = config["NAME_START_ROBOT"].as<std::string>();
        std::string name_tf_service = config["NAME_TF_SERVICE"].as<std::string>();
        std::string tf_service = config["TF_SERVICE"].as<std::string>();

        pri1("Comienzo robot");
        processController.startProcess(start_robot_name, start_robot);
        processController.startProcess(name_tf_service, tf_service);
        start_robot_launch_file = true;

#if ROBOT
        create_subscription(Battery_Level);
#endif
    }
#endif
}

void NodeManager::stop_robot()
{
    if (!tf_service_client_)
    {
        tf_service_client_.reset();
        RCLCPP_INFO(node_manager->get_logger(), "Close Robot Pose Client destroy.");
    }

    if (start_robot_launch_file)
    {
#if ROBOT
        close_subscription(Battery_Level);
#endif
        YAML::Node config;
        try
        {
            std::string path_ = PATH;
            config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading YAML file: " << e.what() << std::endl;
        }
        std::string name_robot = config["NAME_START_ROBOT"].as<std::string>();
        processController.stopProcess(name_robot);
        start_robot_launch_file = false;
    }
}

void NodeManager::publish_initial_pose(double x, double y, double theta)
{
#if !EN_CASA

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

#endif
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
#if !EN_CASA

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
#endif
}

void NodeManager::start_bringup(std::string const &map_name)
{
#if !EN_CASA

    if (!bringup_launch_file)
    {
        YAML::Node config;
        std::string path_;
        try
        {
            path_ = PATH;
            config = YAML::LoadFile(path_ + "server/src/node_manager/param/config.yaml");
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading YAML file: " << e.what() << std::endl;
        }
        std::string path_yaml = config["PATH2MAP"].as<std::string>();
        if (navegando)
        {
            std::string nav2_bringup_launch = config["NAV2_BRINGUP_LAUNCH"].as<std::string>();
            std::string name_nav2_bringup_launch = config["NAME_NAV2_BRINGUP_LAUNCH"].as<std::string>();

            std::string bringup = nav2_bringup_launch;
            bringup += path_yaml;
            bringup += "/" + map_name + ".yaml";
            pri1("++++++++++++++++++++++++++Start bring up GOAL POSE:" + bringup);
            processController.startProcess(name_nav2_bringup_launch, bringup);
        }
        else
        {
            processController.stopProcess(config["NAME_START_ROBOT"].as<std::string>());
            std::string nav_robot = config["NAVIGATION_ROBOT"].as<std::string>();
            std::string name_nav_robot = config["NAME_NAVIGATION_ROBOT"].as<std::string>();

            std::string bringup = nav_robot;
            bringup += path_ + path_yaml;
            bringup += "/" + map_name + ".yaml";
            pri1("+++++++++++++++++++Start person follow up GOAL POSE:" + bringup);
            processController.startProcess(name_nav_robot, bringup);

            std::string distance_tracker = config["DISTANCE_TRACKER"].as<std::string>();
            std::string name_distance_tracker = config["NAME_DISTANCE_TRACKER"].as<std::string>();
            processController.startProcess(name_distance_tracker, distance_tracker);

            std::string camara = config["CAMERA_CONTROLLER"].as<std::string>();
            std::string name_camara = config["NAME_CAMERA_CONTROLLER"].as<std::string>();
            processController.startProcess(name_camara, camara);

            std::string dinamixel = config["DYNAMIXEL"].as<std::string>();
            std::string name_dinamixel = config["NAME_DYNAMIXEL"].as<std::string>();
            processController.startProcess(name_dinamixel, dinamixel);


            std::string prueba = config["PRUEBA"].as<std::string>();
            std::string name_prueba = config["NAME_PRUEBA"].as<std::string>();
            processController.startProcess(name_prueba, prueba);
        }
        bringup_launch_file = true;
    }
#endif
}

void NodeManager::publish_waypoint_follower(const std::vector<geometry_msgs::msg::PoseStamped> &waypoints)
{
#if !EN_CASA

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
#endif
}

void NodeManager::reset()
{
    pri1("Reset NodeManager");
#if !EN_CASA
    if (!tf_service_client_)
    {
        tf_service_client_.reset();
        RCLCPP_INFO(node_manager->get_logger(), "Close Robot Pose Client destroy.");
    }
    slam_launch_file = false;
    bringup_launch_file = false;
    start_robot_launch_file = false;
    processController.listProcesses();
    processController.stopAllProcesses();
#endif
}

void NodeManager::topic_plan_callback(const nav_msgs::msg::Path::SharedPtr msg)
{
    path_.clear(); // Limpiar el vector antes de llenarlo

    for (const auto &pose : msg->poses)
    {
        path_.push_back({static_cast<float>(pose.pose.position.x), static_cast<float>(pose.pose.position.y)});
    }

    RCLCPP_INFO(node_manager->get_logger(), "Received plan with %zu poses", path_.size());
}

void NodeManager::battery_callback(const sensor_msgs::msg::BatteryState::SharedPtr msg)
{
    // RCLCPP_INFO(node_manager->get_logger(),
    //             "Voltaje: %.2f V, Carga: %.2f%%, Presente: %s",
    //             msg->voltage,
    //             msg->percentage,
    //             msg->present ? "Sí" : "No");

    battery_level = msg->percentage;
}

std::vector<RealPositionMeters> NodeManager::getRealPositionPath()
{
    return path_;
}