#ifndef TOJSON_H
#define TOJSON_H
#include <QJsonDocument>
#include <QJsonObject>
// #include "utils.h"

QJsonDocument sendJoystickPosition(const float &angular, const float &linear);

QJsonDocument sendRequestMapSlam();

QJsonDocument sendSaveMap(const QString& map_name);

#endif // TOJSON_H
