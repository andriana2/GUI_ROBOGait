#include "../include/HandleMsg.h"

HandleMsg::HandleMsg(NodeManager &nodeManager) : nodeManager(nodeManager) {}

void HandleMsg::handleMsgJson(const json &json_msg)
{
    if (json_msg.contains("target") && json_msg["target"] == targetToString(Joystick_Position))
        JoystickPosition(json_msg);
    else if (json_msg.contains("target") && json_msg["target"] == targetToString(State_Remote_Controlled))
        StateRemoteControlled(json_msg);
    else if (json_msg.contains("target") && json_msg["target"] == targetToString(Delete_Map))
        DeleteMap(json_msg);
    else if (json_msg.contains("target") && json_msg["target"] == targetToString(Change_Map_Name))
        ChangeMapName(json_msg);
    else if (json_msg.contains("target") && json_msg["target"] == targetToString(Save_Map))
        SaveMap(json_msg);
    else if (json_msg.contains("target") && json_msg["target"] == targetToString(Goal_Pose))
        GoalPose(json_msg);
}

void HandleMsg::JoystickPosition(const json &json_msg)
{
    float linear, angular;
    nodeManager.create_publisher(stringToTarget(json_msg["target"]));
    toJson::getPositionJoystick(json_msg, linear, angular); // json
    pri1(std::to_string(linear) + "<-linear angular ->" + std::to_string(angular));
    nodeManager.execute_position(linear, angular);
}

void HandleMsg::StateRemoteControlled(const json &json_msg)
{
    if (!json_msg["in"])
    {
        // bkill the process (all)
        nodeManager.close_publisher(Request_Map_SLAM);
        nodeManager.close_publisher(Joystick_Position);
        // SI HE INICIALIZADO ALGO CON UN ROS2 RUN O LAUNCH HAY QUE HACER UN KILL
        // RVIZ
        return;
    }
    else if (json_msg.contains("mapping") && json_msg["mapping"] == true)
    {
        nodeManager.create_publisher(Request_Map_SLAM);
    }
    nodeManager.create_publisher(Joystick_Position);
}

void HandleMsg::DeleteMap(const json &json_msg)
{
    std::string path = PATH2MAP;
    path += "/" + replaceSpaces(json_msg["map_name"]);
    std::string path1 = path + ".pgm";
    if (std::remove(path1.c_str()) == 0)
        std::cout << "Archivo eliminado exitosamente: " << path << std::endl;
    else
        std::cerr << "Error al eliminar el archivo: " << path << std::endl;
    std::string path2 = path + ".yaml";
    if (std::remove(path2.c_str()) == 0)
        std::cout << "Archivo eliminado exitosamente: " << path << std::endl;
    else
        std::cerr << "Error al eliminar el archivo: " << path << std::endl;
}

void HandleMsg::ChangeMapName(const json &json_msg)
{
    // if (fs::exists(nuevoNombre))
    // {
    //     std::cerr << "Error: El archivo \"" << nuevoNombre << "\" ya existe." << std::endl;
    //     return 1; // Salir con código de error
    // }

    // // Intentar renombrar el archivo
    // if (std::rename(nombreOriginal.c_str(), nuevoNombre.c_str()) == 0)
    // {
    //     std::cout << "El archivo se renombró exitosamente a: " << nuevoNombre << std::endl;
    // }
    // else
    // {
    //     std::cerr << "Error al renombrar el archivo: " << nombreOriginal << std::endl;
    // }
}

void HandleMsg::SaveMap(const json &json_msg)
{
    std::string path = PATH2MAP;
    path += "/" + replaceSpaces(json_msg["map_name"]);
    nodeManager.refresh_map(json_msg["map_name"]);
}

void HandleMsg::GoalPose(const json &json_msg)
{
}