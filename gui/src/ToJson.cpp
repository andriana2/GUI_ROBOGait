#include "../include/ToJson.h"
#include "../include/utils.h"
#include "qjsonarray.h"

namespace ToJson
{
    // QJsonDocument sendJoystickPosition(QJsonDocument& jsonDoc, const int
    // &angular, const int &linear)
    QJsonDocument sendJoystickPosition(const float &angular, const float &linear)
    {
        QJsonObject jsonObj;
        jsonObj["opt"] = headerToString(MSG);
        jsonObj["target"] = targetToString(Joystick_Position);
        jsonObj["angular"] =
            QString::number(angular, 'f', 4); // 'f' para formato de punto flotante
        jsonObj["linear"] = QString::number(linear, 'f', 4);

        // jsonDoc.setObject(jsonObj);
        return QJsonDocument(jsonObj);
    }

    QJsonDocument sendRequestMap(QString const &map_name)
    {
        QJsonObject jsonObj;
        jsonObj["opt"] = headerToString(REQUEST_IMG);
        jsonObj["target"] = targetToString(Request_Map_SLAM);
        jsonObj["map_name"] = map_name;

        // jsonDoc.setObject(jsonObj);
        return QJsonDocument(jsonObj);
    }

    QJsonDocument sendSaveMap(const QString &map_name, bool repeated)
    {
        QJsonObject jsonObj;
        jsonObj["opt"] = headerToString(MSG);
        jsonObj["target"] = targetToString(Save_Map);
        jsonObj["map_name"] = map_name;
        jsonObj["repeated"] = repeated;
        // jsonDoc.setObject(jsonObj);
        return QJsonDocument(jsonObj);
    }

    QJsonDocument sendStateRemoteControlled(bool mapping, bool in)
    {
        QJsonObject jsonObj;
        jsonObj["opt"] = headerToString(MSG);
        jsonObj["target"] = targetToString(State_Remote_Controlled);
        // jsonObj["stop"] = stop;
        jsonObj["mapping"] = mapping;
        jsonObj["in"] = in;
        return QJsonDocument(jsonObj);
    }

    void getRobotPositionPixel(const QJsonDocument &JsonDoc, int &x_output,
                               int &y_output, float &yaw_output)
    {
        if (!JsonDoc.isObject())
        {
            qWarning() << "El documento JSON no es un objeto.";
            return;
        }

        QJsonObject jsonObj = JsonDoc.object();

        // Extraer los valores del JSON
        if (jsonObj.contains("x") && jsonObj["x"].isString())
        {
            x_output = jsonObj["x"].toString().toInt();
        }

        if (jsonObj.contains("y") && jsonObj["y"].isString())
        {
            y_output = jsonObj["y"].toString().toInt();
        }

        if (jsonObj.contains("yaw") && jsonObj["yaw"].isString())
        {
            yaw_output = jsonObj["yaw"].toString().toFloat();
        }
    }

    QJsonDocument sendRequestMapName()
    {
        QJsonObject jsonObj;
        jsonObj["opt"] = headerToString(REQUEST_MSG);
        jsonObj["target"] = targetToString(Map_Name);
        return QJsonDocument(jsonObj);
    }

    QJsonDocument sendChangeMapName(const QString &new_map_name,
                                    const QString &last_map_name)
    {
        QJsonObject jsonObj;
        jsonObj["opt"] = headerToString(MSG); // no tengo en cuenta si se repite mirar
        jsonObj["target"] = targetToString(Change_Map_Name);
        jsonObj["new_map_name"] = new_map_name;
        jsonObj["last_map_name"] = last_map_name;
        return QJsonDocument(jsonObj);
    }

    QJsonDocument sendDeleteMap(const QString &map_name)
    {
        QJsonObject jsonObj;
        jsonObj["opt"] = headerToString(MSG);
        jsonObj["target"] = targetToString(Delete_Map);
        jsonObj["map_name"] = map_name;
        return QJsonDocument(jsonObj);
    }

    QJsonDocument sendRequestMapSelected(const QString &map_name)
    {
        QJsonObject jsonObj;
        jsonObj["opt"] = headerToString(REQUEST_IMG);
        jsonObj["target"] = targetToString(Img_Map_Select);
        jsonObj["map_name"] = map_name;
        return QJsonDocument(jsonObj);
    }

    QJsonDocument sendStateMenu(bool in)
    {
        QJsonObject jsonObj;
        jsonObj["opt"] = headerToString(MSG);
        jsonObj["target"] = targetToString(State_Menu);
        jsonObj["in"] = in;
        return QJsonDocument(jsonObj);
    }

    QJsonDocument sendGoalPose(QString const &map_name, int const &x_initialpose, int const &y_initialpose, float const &theta_initialpose, int const &x_goalpose, int const &y_goalpose, float const &theta_goalpose, int const &height)
    {
        QJsonObject jsonObj;
        jsonObj["opt"] = headerToString(MSG);
        jsonObj["target"] = targetToString(Goal_Pose);
        jsonObj["map_name"] = map_name;
        // int original_fila = mapa.height() - 1 - inverted_fila;
        // jsonObj["x_initialpose"] = wight - 1 - x_initialpose;// OOOOJJJJOOOO porque en qt el origen de coordenadas esta invertido
        // jsonObj["x_goalpose"] = wight - 1 - x_goalpose;// OOOOJJJJOOOO porque en qt el origen de coordenadas esta invertido
        jsonObj["x_initialpose"] = x_initialpose;// OOOOJJJJOOOO porque en qt el origen de coordenadas esta invertido
        jsonObj["x_goalpose"] = x_goalpose;// OOOOJJJJOOOO porque en qt el origen de coordenadas esta invertido
        jsonObj["y_initialpose"] = height - 1 - y_initialpose;
        jsonObj["y_goalpose"] = height - 1 - y_goalpose;

        float originalAngle = 360 - theta_initialpose;
        if (originalAngle >= 360) {
            originalAngle -= 360;
        }
        jsonObj["theta_initialpose"] = originalAngle;

        float originalAngleGoalPose = 360 - theta_goalpose;
        if (originalAngleGoalPose >= 360) {
            originalAngleGoalPose -= 360;
        }
        jsonObj["theta_goalpose"] = originalAngleGoalPose;
        return QJsonDocument(jsonObj);
    }

    QJsonDocument sendWaypointFollower(QString const &map_name, int const &x_initialpose, int const &y_initialpose, float const &theta_initialpose, QList<Pixel> pixels , int const &height)
    {
        QJsonObject jsonObj;
        jsonObj["opt"] = headerToString(MSG);
        jsonObj["target"] = targetToString(Waypoint_Follower);
        jsonObj["map_name"] = map_name;
        jsonObj["x_initialpose"] = x_initialpose;
        // jsonObj["x_goalpose"] = x_goalpose;
        jsonObj["y_initialpose"] = height - 1 - y_initialpose; // OOOOJJJJOOOO porque en qt el origen de coordenadas esta invertido
        // jsonObj["y_goalpose"] = height - 1 - y_goalpose; // OOOOJJJJOOOO porque en qt el origen de coordenadas esta invertido

        float originalAngle = 360 - theta_initialpose;
        if (originalAngle >= 360) {
            originalAngle -= 360;
        }
        jsonObj["theta_initialpose"] = originalAngle;

        QJsonArray jsonArray;
        for (auto& pixel : pixels)
        {
            QJsonObject pixelObject;
            pixelObject["x"] = pixel.x;
            pixelObject["y"] = height - 1 - pixel.y;
            jsonArray.append(pixelObject);
        }
        jsonObj["waypoints"] = jsonArray;

        return QJsonDocument(jsonObj);
    }
    QJsonDocument stopProcesses()
    {
        QJsonObject jsonObj;
        jsonObj["opt"] = headerToString(MSG);
        jsonObj["target"] = targetToString(Stop_Process);
        jsonObj["stop"] = true;
        return QJsonDocument(jsonObj);
    }


} // namespace ToJson
