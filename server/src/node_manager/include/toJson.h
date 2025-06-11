#ifndef TOJSON_H
#define TOJSON_H

#include <iostream>
#include <nlohmann/json.hpp> // Asegúrate de incluir la biblioteca
#include "utils.h"

namespace toJson
{
    using json = nlohmann::json;

    json sendRobotPositionPixel(int x, int y, float yaw);

    json sendRobotPositionInitialpose(int x, int y, float yaw);

    json sendImgMap(const std::string data, int size_data, int total_size_img, int num_frame, int total_frame, bool img_map_slam);

    json sendImgMap();

    void getPositionJoystick(json const &j, float &linear_output, float &angular_output);

    json sendMapName(std::vector<std::string> const &vec_map_name);

    json sendInfoMap(std::string const &map_name, int const &width, int const &height, float const &resolution);

    json sendGoalPosePath(std::vector<struct FinalPosition> const &path);
    
    json sendStopProcess();

    json sendBatteryLevel(float battery_level);
}
#endif // TOJSON_H