#ifndef TOJSON_H
#define TOJSON_H
#include <QJsonDocument>
#include <QJsonObject>
#include "utils.h"

namespace ToJson
{

    QJsonDocument sendJoystickPosition(const float &angular, const float &linear);

    QJsonDocument sendRequestMap(QString const &map_name = "");

    QJsonDocument sendSaveMap(const QString &map_name, bool repeated);

    QJsonDocument sendStateRemoteControlled(bool mapping, bool in);

    void getRobotPositionPixel(const QJsonDocument &JsonDoc, int x_output, int y_output, float yaw_output);

    QJsonDocument sendRequestMapName();

    QJsonDocument sendRequestRobotPosition(QString const &map_name);

    QJsonDocument sendChangeMapName(const QString &new_map_name, const QString &last_map_name);

    QJsonDocument sendDeleteMap(const QString &map_name);

    QJsonDocument sendStateMenu(bool in);

    QJsonDocument initBringUp(QString const &map_name);

    QJsonDocument sendInitialPose(QString const &map_name, int const &x_initialpose, int const &y_initialpose, float const &theta_initialpose,int const &height);

    QJsonDocument sendGoalPose(QString const &map_name, int const &x_goalpose, int const &y_goalpose, float const &theta_goalpose, int const &height);

    QJsonDocument sendWaypointFollower(QString const &map_name, QList<Pixel> pixels , int const &height);

    QJsonDocument stopProcesses();
}

#endif // TOJSON_H
