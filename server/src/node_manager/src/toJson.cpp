#include "../include/toJson.h"

json sendRobotPositionPixel(int x, int y, float yaw)
{
    return {
        {"opt", headerToString(MSG)},
        {"target", targetToString(Robot_Position_Pixel)},
        {"x", x},
        {"y", y},
        {"yaw", yaw}};
}

json sendImgMapSlam(const std::string data, int size_data, int total_size_img, int num_frame, int total_frame)
{
    return {
        {"opt", headerToString(IMG)},
        {"target", targetToString(Img_Map_SLAM)},
        {"data", data},
        {"size_data", size_data},
        {"total_size_img", total_size_img},
        {"num_frame", num_frame},
        {"total_frame", total_frame}};
}

void getPositionJoystick(const json &j, float &linear_output, float &angular_output) {
    if (j.contains("linear") && j["linear"].is_string()) {
        try {
            linear_output = std::stof(j["linear"].get<std::string>());
        } catch (const std::exception &e) {
            std::cerr << "Error: No se pudo convertir 'linear' a float: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Error: La clave 'linear' no existe o no es una cadena válida." << std::endl;
    }

    if (j.contains("angular") && j["angular"].is_string()) {
        try {
            angular_output = std::stof(j["angular"].get<std::string>());
        } catch (const std::exception &e) {
            std::cerr << "Error: No se pudo convertir 'angular' a float: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Error: La clave 'angular' no existe o no es una cadena válida." << std::endl;
    }
}

