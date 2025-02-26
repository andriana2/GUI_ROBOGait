#ifndef UTILS_H
#define UTILS_H

// #include <iostream>
// #include <stdexcept>
// #include <string>

#include <QString>
#include <QVector>
#include <QJsonObject>

#define EN_CASA 1

enum Header
{
    MSG,
    REQUEST_MSG,
    IMG,
    REQUEST_IMG
};

enum Target
{
    Joystick_Position,
    Request_Map_SLAM,
    Request_Robot_Position,
    Robot_Position_Pixel,
    Robot_Position_Pixel_Initialpose,
    Img_Map_SLAM,
    Img_Map_Path,
    Save_Map,
    State_Remote_Controlled,
    State_Menu,
    Map_Name,
    Map_Info_Image_Size,
    Change_Map_Name,
    Delete_Map,
    Img_Map_Select,
    Init_Bringup,
    Initial_Pose,
    Goal_Pose,
    Waypoint_Follower,
    Stop_Process,
    Goal_Pose_Path
};

struct FinalPosition
{
    int x_pixel;
    int y_pixel;
    float yaw;
    bool active;
};

struct Pixel
{
    Q_GADGET
    Q_PROPERTY(int x MEMBER x)
    Q_PROPERTY(int y MEMBER y)

public:
    int x = 0; // Inicialización predeterminada
    int y = 0; // Inicialización predeterminada

    Pixel() = default;                  // Constructor predeterminado
    Pixel(int x, int y) : x(x), y(y) {} // Constructor con parámetros

    bool operator==(const Pixel &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Pixel &other) const
    {
        return !(*this == other);
    }
    QJsonObject toJson() const
    {
        QJsonObject jsonObject;
        jsonObject["x"] = x;
        jsonObject["y"] = y;
        return jsonObject;
    }
};

QVector<QString> extractJSONObjects(const QString &input);
QByteArray fromHex(const QString &hex);

QString obtenerIP();

Header stringToHeader(const QString &str);
QString headerToString(Header header);

Target stringToTarget(const QString &str);
QString targetToString(Target target);

#endif // UTILS_H
