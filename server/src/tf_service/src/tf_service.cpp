#include <rclcpp/rclcpp.hpp>
#include <tf2_msgs/msg/tf_message.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include "interface_srv/srv/get_robot_position.hpp" // Interfaz personalizada
#include <unordered_map>
#include <string>
#include <vector>
#include <cmath>
#define I_AM_ROBOT 1

class TFServiceNode : public rclcpp::Node
{
public:
    struct GetPosition
    {
        float x;
        float y;
        float yaw;
    };
    TFServiceNode() : Node("tf_service_node")
    {
        // Suscripción al topic /tf
        subscription_ = this->create_subscription<tf2_msgs::msg::TFMessage>(
            "/tf", 10, std::bind(&TFServiceNode::tfCallback, this, std::placeholders::_1));

        // Servicio para obtener transformaciones
        service_ = this->create_service<interface_srv::srv::GetRobotPosition>(
            "get_transform", std::bind(&TFServiceNode::handleServiceRequest, this, std::placeholders::_1, std::placeholders::_2));

        RCLCPP_INFO(this->get_logger(), "TF Service Node has been started.");
    }

private:
    // Callback para procesar datos del topic /tf
    void tfCallback(const tf2_msgs::msg::TFMessage::SharedPtr msg)
    {
        // std::cout << "tfCallback" << std::endl;

        for (const auto &transform : msg->transforms)
        {
            std::string key = transform.header.frame_id + "->" + transform.child_frame_id;
            transform_cache_[key] = transform;
        }
    }

    // Encontrar la transformación acumulada entre dos frames
    bool findTransform(const std::string &parent_frame, const std::string &child_frame, geometry_msgs::msg::Transform &result)
    {
        // std::cout << "encontrando transformacion" << std::endl;

        std::string key = parent_frame + "->" + child_frame;

        // Caso base: transformación directa
        if (transform_cache_.find(key) != transform_cache_.end())
        {
            const auto &transform = transform_cache_[key];
            result = transform.transform;
            return true;
        }

        // Buscar frame intermedio
        for (const auto &[cached_key, transform] : transform_cache_)
        {
            if (cached_key.find(parent_frame + "->") == 0)
            {
                std::string intermediate_frame = cached_key.substr(parent_frame.size() + 2); // Extraer el frame hijo

                geometry_msgs::msg::Transform intermediate_transform;
                if (findTransform(intermediate_frame, child_frame, intermediate_transform))
                {
                    // Multiplicar transformaciones (parent_frame -> intermediate_frame -> child_frame)
                    combineTransforms(transform.transform, intermediate_transform, result);
                    return true;
                }
            }
        }

        return false;
    }

    // Combinar dos transformaciones
    void combineTransforms(const geometry_msgs::msg::Transform &t1, const geometry_msgs::msg::Transform &t2, geometry_msgs::msg::Transform &result)
    {
        // Combinar traslaciones
        // std::cout << "transformando" << std::endl;

        result.translation.x = t1.translation.x + t2.translation.x;
        result.translation.y = t1.translation.y + t2.translation.y;
        result.translation.z = t1.translation.z + t2.translation.z;

        // Combinar rotaciones (multiplicación de cuaterniones)
        result.rotation.x = t1.rotation.w * t2.rotation.x + t1.rotation.x * t2.rotation.w + t1.rotation.y * t2.rotation.z - t1.rotation.z * t2.rotation.y;
        result.rotation.y = t1.rotation.w * t2.rotation.y - t1.rotation.x * t2.rotation.z + t1.rotation.y * t2.rotation.w + t1.rotation.z * t2.rotation.x;
        result.rotation.z = t1.rotation.w * t2.rotation.z + t1.rotation.x * t2.rotation.y - t1.rotation.y * t2.rotation.x + t1.rotation.z * t2.rotation.w;
        result.rotation.w = t1.rotation.w * t2.rotation.w - t1.rotation.x * t2.rotation.x - t1.rotation.y * t2.rotation.y - t1.rotation.z * t2.rotation.z;
    }

    void transform2GetPosition(const geometry_msgs::msg::Transform &result, struct GetPosition &result_struct)
    {
        // std::cout << "En las transformaciones" << std::endl;

        result_struct.x = result.translation.x;
        result_struct.y = result.translation.y;

        float siny_cosp = 2.0 * (result.rotation.w * result.rotation.z + result.rotation.x * result.rotation.y);
        float cosy_cosp = 1.0 - 2.0 * (result.rotation.y * result.rotation.y + result.rotation.z * result.rotation.z);
        result_struct.yaw = std::atan2(siny_cosp, cosy_cosp);
    }

#if I_AM_ROBOT
    // Manejar solicitudes del servicio
    void handleServiceRequest(
        [[maybe_unused]] const std::shared_ptr<interface_srv::srv::GetRobotPosition::Request> request,
        std::shared_ptr<interface_srv::srv::GetRobotPosition::Response> response)
    {
        // std::cout << "Manejando solicitudes" << std::endl;
        geometry_msgs::msg::Transform result;

        if (findTransform("map", "base_link", result))
        {
            struct GetPosition gp;
            transform2GetPosition(result, gp);
            response->x = gp.x;
            response->y = gp.y;
            response->yaw = gp.yaw;
            response->success = true;
            RCLCPP_INFO(this->get_logger(), "Transform found: map -> base_link");
        }
        else
        {
            response->success = false;
            RCLCPP_WARN(this->get_logger(), "Transform not found: map -> base_link");
        }
    }
#else

    void handleServiceRequest(
        [[maybe_unused]] const std::shared_ptr<interface_srv::srv::GetRobotPosition::Request> request,
        std::shared_ptr<interface_srv::srv::GetRobotPosition::Response> response)
    {
        // std::cout << "Manejando solicitudes" << std::endl;
        geometry_msgs::msg::Transform result;

        if (findTransform("map", "base_footprint", result))
        {
            struct GetPosition gp;
            transform2GetPosition(result, gp);
            response->x = gp.x;
            response->y = gp.y;
            response->yaw = gp.yaw;
            response->success = true;
            RCLCPP_INFO(this->get_logger(), "Transform found: map -> base_footprint");
            RCLCPP_INFO(this->get_logger(), "map -> base_footprint: x=%.2f, y=%.2f, yaw=%.2f", gp.x, gp.y, gp.yaw);
        }
        else
        {
            response->success = false;
            RCLCPP_WARN(this->get_logger(), "Transform not found: map -> base_footprint");
        }
    }
#endif

    rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_;
    rclcpp::Service<interface_srv::srv::GetRobotPosition>::SharedPtr service_;

    // Almacén para guardar las transformaciones más recientes
    std::unordered_map<std::string, geometry_msgs::msg::TransformStamped> transform_cache_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TFServiceNode>());
    rclcpp::shutdown();
    return 0;
}
