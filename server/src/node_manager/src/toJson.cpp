#include "../include/toJson.h"

namespace toJson
{

    json sendRobotPositionPixel(int x, int y, float yaw)
    {
        // pri1("Send x" + std::to_string(x) + "Send y = " + std::to_string(y) + "Send yaw = " + std::to_string(yaw));
        return {
            {"opt", headerToString(MSG)},
            {"target", targetToString(Robot_Position_Pixel)},
            {"x", x},
            {"y", y},
            {"yaw", yaw}};
    }

    json sendRobotPositionInitialpose(int x, int y, float yaw)
    {
        yaw = yaw * 180.0 / M_PI;
        // pri1("Send x" + std::to_string(x) + "Send y = " + std::to_string(y) + "Send yaw = " + std::to_string(yaw));
        return {
            {"opt", headerToString(MSG)},
            {"target", targetToString(Robot_Position_Pixel_Initialpose)},
            {"x", x},
            {"y", y},
            {"yaw", yaw}};
    }

    json sendImgMap(const std::string data, int size_data, int total_size_img, int num_frame, int total_frame, bool img_map_slam)
    {
        std::string target_name;
        if (img_map_slam)
            target_name = targetToString(Img_Map_SLAM);
        else
            target_name = targetToString(Img_Map_Path);
        return {
            {"opt", headerToString(IMG)},
            {"target", target_name},
            {"data", data},
            {"size_data", size_data},
            {"total_size_img", total_size_img},
            {"num_frame", num_frame},
            {"total_frame", total_frame}};
    }

    json sendImgMap()
    {
        return {
            {"opt", headerToString(IMG)},
            {"target", targetToString(Img_Map_SLAM)},
            {"data", ""}};
    }

    void getPositionJoystick(const json &j, float &linear_output, float &angular_output)
    {
        if (j.contains("linear") && j["linear"].is_string())
        {
            try
            {
                linear_output = std::stof(j["linear"].get<std::string>());
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error: No se pudo convertir 'linear' a float: " << e.what() << std::endl;
            }
        }
        else
            std::cerr << "Error: La clave 'linear' no existe o no es una cadena válida." << std::endl;

        if (j.contains("angular") && j["angular"].is_string())
        {
            try
            {
                angular_output = std::stof(j["angular"].get<std::string>());
            }
            catch (const std::exception &e)
            {
                std::cerr
                    << "Error: No se pudo convertir 'angular' a float: " << e.what() << std::endl;
            }
        }
        else
            std::cerr << "Error: La clave 'angular' no existe o no es una cadena válida." << std::endl;
    }

    json sendMapName(std::vector<std::string> const &vec_map_name)
    {
        return {
            {"opt", headerToString(MSG)},
            {"target", targetToString(Map_Name)},
            {"vec_map_name", vec_map_name}};
    }

    json sendInfoMap(std::string const &map_name, int const &width, int const &height, float const &resolution)
    {
        return {
            {"opt", headerToString(MSG)},
            {"target", targetToString(Map_Info_Image_Size)},
            {"map_name", map_name},
            {"width", width},
            {"height", height},
            {"resolution", resolution}};
    }

    json sendGoalPosePath(std::vector<struct FinalPosition> const &path)
    {
        json j;
        j["opt"] = headerToString(MSG);
        j["target"] = targetToString(Goal_Pose_Path);
        for (const auto &p : path)
        {
            j["points"].push_back({{"x", p.x_pixel}, {"y", p.y_pixel}});
        }
        return j;
    }

    json sendStopProcess()
    {
        return {
            {"opt", headerToString(MSG)},
            {"target", targetToString(Stop_Process)}};
    }

    json sendBatteryLevel(float battery_level)
    {
        return {
            {"opt", headerToString(MSG)},
            {"target", targetToString(Battery_Level)},
            {"battery_level", battery_level}};
    }
}
