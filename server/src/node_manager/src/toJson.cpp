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
        {"opt", headerToString(MSG)},
        {"target", targetToString(Robot_Position_Pixel)},
        {"data", data},
        {"size_data", size_data},
        {"total_size_img", total_size_img},
        {"num_frame", num_frame},
        {"total_frame", total_frame}};
}

void getPositionJoystick(json const &j, float &linear_output, float &angular_output)
{
    pri1("hey");
    if (j.contains("linear") && j["linear"].is_number())
    {
        linear_output = j["linear"];
    }
    else
    {
        std::cerr << "Error: La clave 'linear' no existe o no es un número válido." << std::endl;
    }

    if (j.contains("angular") && j["angular"].is_number())
    {
        angular_output = j["angular"];
    }
    else
    {
        std::cerr << "Error: La clave 'angular' no existe o no es un número válido." << std::endl;
    }
}

