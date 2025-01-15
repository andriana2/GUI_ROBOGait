#ifndef TOJSON_H
#define TOJSON_H
#include <QJsonDocument>
#include <QJsonObject>
// #include "utils.h"

QJsonDocument sendJoystickPosition(const float &angular, const float &linear);

QJsonDocument sendRequestMapSlam();

QJsonDocument sendSaveMap(const QString& map_name, bool repeated);

QJsonDocument sendStateRemoteControlled(bool mapping, bool in);

void getRobotPositionPixel(const QJsonDocument &JsonDoc, int x_output, int y_output, float yaw_output);

QJsonDocument sendRequestMapName();

QJsonDocument sendChangeMapName(const QString& new_map_name,const QString& last_map_name);

QJsonDocument sendDeleteMap(const QString& map_name);


#endif // TOJSON_H
