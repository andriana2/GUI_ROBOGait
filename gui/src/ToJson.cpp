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

QJsonDocument sendRequestMapSlam() {
    QJsonObject jsonObj;
    jsonObj["opt"] = headerToString(REQUEST_IMG);
    jsonObj["target"] = targetToString(Map_SLAM);

    //jsonDoc.setObject(jsonObj);
    return QJsonDocument(jsonObj);
}

QJsonDocument sendSaveMap(const QString& map_name) {
    QJsonObject jsonObj;
    jsonObj["opt"] = headerToString(MSG);
    jsonObj["target"] = targetToString(Save_Map);
    jsonObj["map_name"] = map_name;
    //jsonDoc.setObject(jsonObj);
    return QJsonDocument(jsonObj);
}



// void actualizarJson(QJsonDocument& jsonDoc, const QString& opt, const QString& target) {
//     QJsonObject jsonObj;
//     jsonObj["opt"] = opt;
//     jsonObj["target"] = name;


//     // Asignar el objeto JSON al documento
//     jsonDoc.setObject(jsonObj);
// }



