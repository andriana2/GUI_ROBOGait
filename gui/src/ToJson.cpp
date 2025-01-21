#include "../include/ToJson.h"
#include "../include/utils.h"

// QJsonDocument sendJoystickPosition(QJsonDocument& jsonDoc, const int &angular, const int &linear)
QJsonDocument sendJoystickPosition(const float &angular, const float &linear)
{
    QJsonObject jsonObj;
    jsonObj["opt"] = headerToString(MSG);
    jsonObj["target"] = targetToString(Joystick_Position);
    jsonObj["angular"] = QString::number(angular, 'f', 4); // 'f' para formato de punto flotante
    jsonObj["linear"] = QString::number(linear, 'f', 4);

    //jsonDoc.setObject(jsonObj);
    return QJsonDocument(jsonObj);
}

QJsonDocument sendRequestMap(QString const &map_name) {
    QJsonObject jsonObj;
    jsonObj["opt"] = headerToString(REQUEST_IMG);
    jsonObj["target"] = targetToString(Map_SLAM);
    jsonObj["map_name"] = map_name;


    //jsonDoc.setObject(jsonObj);
    return QJsonDocument(jsonObj);
}

QJsonDocument sendSaveMap(const QString& map_name, bool repeated) {
    QJsonObject jsonObj;
    jsonObj["opt"] = headerToString(MSG);
    jsonObj["target"] = targetToString(Save_Map);
    jsonObj["map_name"] = map_name;
    jsonObj["repeated"] = repeated;
    //jsonDoc.setObject(jsonObj);
    return QJsonDocument(jsonObj);
}

QJsonDocument sendStateRemoteControlled(bool mapping, bool in) {
    QJsonObject jsonObj;
    jsonObj["opt"] = headerToString(MSG);
    jsonObj["target"] = targetToString(State_Remote_Controlled);
    // jsonObj["stop"] = stop;
    jsonObj["mapping"] = mapping;
    jsonObj["in"] = in;
    return QJsonDocument(jsonObj);
}

void getRobotPositionPixel(const QJsonDocument &JsonDoc, int &x_output, int &y_output, float &yaw_output)
{
    if (!JsonDoc.isObject()) {
        qWarning() << "El documento JSON no es un objeto.";
        return;
    }

    QJsonObject jsonObj = JsonDoc.object();

    // Extraer los valores del JSON
    if (jsonObj.contains("x") && jsonObj["x"].isString()) {
        x_output = jsonObj["x"].toString().toInt();
    }

    if (jsonObj.contains("y") && jsonObj["y"].isString()) {
        y_output = jsonObj["y"].toString().toInt();
    }

    if (jsonObj.contains("yaw") && jsonObj["yaw"].isString()) {
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

QJsonDocument sendChangeMapName(const QString &new_map_name, const QString &last_map_name)
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
