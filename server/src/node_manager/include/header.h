#ifndef HEADER_H
#define HEADER_H


#define EN_CASA 0
#define ROBOT 1
#define NAV 1
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


#endif // HEADER_H
