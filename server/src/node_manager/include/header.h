#ifndef HEADER_H
#define HEADER_H

enum Header {
    MSG,
    REQUEST_MSG,
    IMG,
    REQUEST_IMG
};

enum Target {
    Joystick_Position,
    Map_SLAM,
    Robot_Position_Pixel,
    Img_Map_SLAM,
    Save_Map,
    State_Remote_Controlled,
    Map_Name,
    Change_Map_Name,
    Delete_Map,
    Img_Map_Select
};

struct FinalPosition
{
    int x_pixel;
    int y_pixel;
    float yaw;
};

// #define PATH2MAP "/home/robogait/Desktop/gui_andri/gui/server/maps" // uni
#define PATH2MAP "/home/andri/Desktop/gui_nuevo/gui_/server/maps" //casa

// #define MAP_SAVER_CLI "ros2 run nav2_map_server map_saver_cli -t /map -f " + PATH2MAP + " "
#define MAP_SAVER_CLI "ros2 run nav2_map_server map_saver_cli -t /map -f /home/robogait/Desktop/gui_andri/gui_/server/maps"

// launch
#define RVIZ_LAUNCH_MAPING "ros2 launch turtlebot3_cartographer cartographer.launch.py &" // &ejecutar en segundo plano

// kill
#define RVIZ_LAUNCH_MAPING_KILL "pgrep -f 'ros2 launch turtlebot3_cartographer cartographer.launch.py'"

//    if (number == 10) // como matar procesos
//     {
//         if (!turtlesim_started_)
//         {
//             std::system("ros2 run turtlesim turtlesim_node &"); // Ejecuta turtlesim en segundo plano
//             turtlesim_started_ = true;
//         }
//     }
//     else if (number == 11)
//     {
//         if (turtlesim_started_)
//         {
//             std::system("pkill turtlesim_node"); // Detiene el nodo de turtlesim
//             turtlesim_started_ = false;
//         }
//     }

// topic
#define TF_TOPIC "/tf"
#define CMD_TOPIC "/cmd_vel"

// turtlesim
#define CMD_TOPIC_TURTLESIM "/turtle1/cmd_vel"

#endif // HEADER_H
