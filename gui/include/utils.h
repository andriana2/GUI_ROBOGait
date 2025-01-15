#ifndef UTILS_H
#define UTILS_H

// #include <iostream>
// #include <stdexcept>
// #include <string>

#include <QString>
#include <QVector>

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
    bool active;
};

QVector<QString> extractJSONObjects(const QString& input);
QByteArray fromHex(const QString &hex);

QString obtenerIP();

Header stringToHeader(const QString& str);
QString headerToString(Header header);

Target stringToTarget(const QString& str);
QString targetToString(Target target);

#endif // UTILS_H
