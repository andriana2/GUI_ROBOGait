#ifndef HEADER_H
#define HEADER_H


#define EN_CASA 1
#define ROBOT 0
enum Header {
    MSG,
    REQUEST_MSG,
    IMG,
    REQUEST_IMG
};

enum Target {
    Joystick_Position, // Velocidad linea y angular del robot
    Request_Map_SLAM,   // Peticion para la imagen del mapa
    Robot_Position_Pixel, // Posicion del robot en pixeles
    Robot_Position_Pixel_Initialpose, // Posicion del robot en pixeles en la posicion inicial
    Request_Robot_Position, // Peticion de la posicion del robot
    Img_Map_SLAM, // Imagen al hacer SLAM
    Img_Map_Path, // Imagen al hacer la ruta
    Save_Map, // Guardar el mapa
    State_Remote_Controlled, // Estado del robot
    State_Menu, // Estado del menu para saber si hay que iniciar un programa
    Map_Name, // Nombres de los mapas
    Map_Info_Image_Size,
    Change_Map_Name, // Cambiar el nombre del mapa
    Delete_Map, // Borrar el mapa
    Img_Map_Select, // Informacion de la imagen del mapa
    Init_Bringup, // Iniciar el bringup
    Initial_Pose, // Posicion inicial del robot
    Goal_Pose, // Posicion objetivo del robot
    Waypoint_Follower, // Seguir la trayectoria de unos puntos
    Stop_Process,   // Detener el proceso
    Goal_Pose_Path, // Posicion objetivo del robot en la trayectoria
    All_Information_Pose,
    Battery_Level
};

struct FinalPosition
{
    int x_pixel;
    int y_pixel;
    float yaw;
};

struct RealPositionMeters
{
    float x;
    float y;
};

#if EN_CASA && !ROBOT
#define PATH "/home/andri/Desktop/gui_nuevo/gui_/" //casa

#elif !ROBOT
#define PATH "/home/robogait/Desktop/gui_andri/GUI_ROBOGait/" // uni
#else
#define PATH "/home/robogait/GUI_ROBOGait/" // robot
#endif


// // #define SOURCE_GAZEBO ""bash -i -c 'source /usr/share/gazebo/setup.sh && echo \"Gazebo configurado\"'""
// #define START_ROBOT "ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py"
// #define NAME_START_ROBOT "turtlebot3_gazebo"
// // #else
// // #define START_ROBOT ""

// // #define MAP_SAVER_CLI "ros2 run nav2_map_server map_saver_cli -t /map -f " + PATH2MAP + " "
// #define MAP_SAVER_CLI "ros2 run nav2_map_server map_saver_cli -t /map -f /home/robogait/Desktop/gui_andri/gui/server/maps"
// #define NAME_MAP_SAVER_CLI "nav2_map_save"

// #define TF_SERVICE "ros2 run tf_service tf_service_node"
// #define NAME_TF_SERVICE "tf_service"

// // launch
// #define CARTOGRAPHER_LAUNCH "ros2 launch turtlebot3_cartographer cartographer_noRviz.launch.py use_sim_time:=True" // &ejecutar en segundo plano
// #define NAME_CARTOGRAPHER_LAUNCH "turtlebot3_cartographer"

// #define NAV2_BRINGUP_LAUNCH "ros2 launch nav2_bringup bringup_launch.py use_sim_time:=True map:="
// #define NAME_NAV2_BRINGUP_LAUNCH "nav2_bringup"

// // #define RVIZ_LAUNCH_MAPING "ros2 launch turtlebot3_cartographer cartographer.launch.py &" // &ejecutar en segundo plano

// // topic
// #define TF_TOPIC "/tf"
// #define CMD_VEL_TOPIC "/cmd_vel"
// #define INITIAL_POSE_TOPIC "/initialpose"
// #define GOAL_POSE_TOPIC "/goal_pose"
// #define WAYPOINT_FOLLOWER_ACTION "/follow_waypoints"

// // turtlesim
// #define CMD_TOPIC_TURTLESIM "/turtle1/cmd_vel"



// // #if EN_CASA
// // #define PATH2MAP "/home/andri/Desktop/gui_nuevo/gui_/server/maps" //casa
// // #else
// // #define PATH2MAP "/home/robogait/Desktop/gui_andri/gui/server/maps" // uni
// // // #define SOURCE_GAZEBO ""bash -i -c 'source /usr/share/gazebo/setup.sh && echo \"Gazebo configurado\"'""
// // #define START_ROBOT "ros2 launch roverrotics_driver mini.launch.py"
// // #define NAME_START_ROBOT "roverrotics_driver"
// // // #else
// // // #define START_ROBOT ""
// // #endif

// // // #define MAP_SAVER_CLI "ros2 run nav2_map_server map_saver_cli -t /map -f " + PATH2MAP + " "
// // #define MAP_SAVER_CLI "ros2 run nav2_map_server map_saver_cli -t /map -f /home/robogait/Desktop/gui_andri/gui/server/maps"

// // // launch
// // #define CARTOGRAPHER_LAUNCH "ros2 launch roverrobotics_driver slam_launch.py" // &ejecutar en segundo plano
// // #define NAME_CARTOGRAPHER_LAUNCH "roverrobotics_driver_slam"

// // #define NAV2_BRINGUP_LAUNCH "ros2 launch roverrobotics_driver navigation_launch.py"
// // #define NAME_NAV2_BRINGUP_LAUNCH "roverrobotics_driver_navigation"

// // // #define RVIZ_LAUNCH_MAPING "ros2 launch turtlebot3_cartographer cartographer.launch.py &" // &ejecutar en segundo plano

// // // topic
// // #define TF_TOPIC "/tf"
// // #define CMD_VEL_TOPIC "/cmd_vel"
// // #define INITIAL_POSE_TOPIC "/initialpose"
// // #define GOAL_POSE_TOPIC "/goal_pose"
// // #define WAYPOINT_FOLLOWER_ACTION "/follow_waypoints"

// // // turtlesim
// // #define CMD_TOPIC_TURTLESIM "/turtle1/cmd_vel"


#endif // HEADER_H
