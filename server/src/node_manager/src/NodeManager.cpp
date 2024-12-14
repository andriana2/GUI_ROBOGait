#include "../include/NodeManager.h"
#include <iostream>

NodeManager::NodeManager(rclcpp::Node::SharedPtr node_ptr)
{
    node_manager = node_ptr;
    rviz_active = false;
}

void NodeManager::create_publisher(std::string const &where_publish)
{
    static pid_t pid;
    if (where_publish == get_info_message(Position_joystick))
    {
        if (!cmd_vel_publisher_)
        {
            // Crear el publisher si no existe
            cmd_vel_publisher_ = node_manager->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
            RCLCPP_INFO(node_manager->get_logger(), "Publisher /cmd_vel creado.");
        }
    }
    else if (where_publish == "map_scan")
    {
        if (!tf_service_client_)
        {
            // Crear el publisher si no existe
            tf_service_client_ = node_manager->create_client<interface_srv::srv::GetRobotPosition>("get_robot_pose");
            RCLCPP_INFO(node_manager->get_logger(), "Robot Pose Client initialized.");
        }
        if (!rviz_active)
        {
            if (!tf_service_client_->wait_for_service(std::chrono::seconds(1)))
            {
                RCLCPP_WARN(node_manager->get_logger(), "Service not available, waiting...");
                return;
            }

            // Crear solicitud
            auto request = std::make_shared<interface_srv::srv::GetRobotPosition::Request>();

            // Enviar solicitud y procesar la respuesta
            auto future = tf_service_client_->async_send_request(request);

            try
            {
                // Esperar la respuesta con un timeout
                auto response = future.get();
                RCLCPP_INFO(node_manager->get_logger(),
                            "Received Robot Pose - x: %.2f, y: %.2f, yaw: %.2f",
                            response->x, response->y, response->yaw);
            }
            catch (const std::exception &e)
            {
                RCLCPP_ERROR(node_manager->get_logger(), "Failed to call service: %s", e.what());
            }

            // DESCOMENTAR CUANDO FUNCIONE LA TRASMISION DE IMAGENES
            //  pid = fork();
            //  if (pid == 0)
            //  {
            //      // Proceso hijo
            //      const char *command = "ros2";
            //      const char *args[] = {"ros2", "launch", "turtlebot3_cartographer", "cartographer.launch.py", nullptr};
            //      freopen("/dev/null", "w", stdout); // Redirigir stdout a /dev/null
            //      freopen("/dev/null", "w", stderr); // Redirigir stderr a /dev/null
            //      execvp(command, const_cast<char *const *>(args));
            //      std::exit(EXIT_FAILURE); // Solo si exec falla
            //  }
            //  else if (pid > 0)
            //  {
            //      // Proceso padre
            //      rviz_active = true;
            //      std::cout << "Cartographer lanzado en segundo plano." << std::endl;
            //  }
            //  else
            //  {
            //      // Error al crear proceso
            //      std::cerr << "Error al lanzar Cartographer." << std::endl;
            //  }
        }
    }
    else
    {
        if (rviz_active)
        {
            if (pid > 0)
            {
                if (kill(pid, SIGTERM) == 0)
                {
                    rviz_active = false;
                    std::cout << "Proceso Cartographer (PID " << pid << ") terminado." << std::endl;
                }
                else
                {

                    perror("Error al terminar el proceso");
                }
            }
            else
            {
                std::cerr << "Cartographer no está en ejecución." << std::endl;
            }
        }
        // kill_launch_file(RVIZ_LAUNCH_MAPING_KILL);
    }
}

void NodeManager::refresh_map()
{
    std::string command = MAP_SAVER_CLI;
    command += "/temporal_map";
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
    geometry_msgs::msg::Twist twist_msg;
    twist_msg.linear.x = linear;
    twist_msg.angular.z = angular;
    cmd_vel_publisher_->publish(twist_msg);
    std::cout << "valores publicados linear: " << linear << " angular: " << angular << std::endl;
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