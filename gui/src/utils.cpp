#include "../include/utils.h"

// #include <stdexcept>

// #include <iostream>
#include <unistd.h>
// #include <cstring>
#include <sys/types.h>
#include <QNetworkInterface>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QRegularExpression>
#include <QDebug>

QVector<QString> extractJSONObjects(const QString &input)
{
    static QString incompleteFragment; // Guarda fragmentos incompletos entre llamadas
    QVector<QString> jsonObjects;

    // Combina el fragmento incompleto con la nueva entrada
    QString combinedInput = incompleteFragment + input;
    qDebug() << "Combined input:" << combinedInput;

    QRegularExpression jsonRegex(R"(\{(?:[^{}]|\[(?:[^\[\]]|\[.*?\])*\])*\})");
    QRegularExpressionMatchIterator matchIterator = jsonRegex.globalMatch(combinedInput);

    int lastValidEnd = 0;

    while (matchIterator.hasNext())
    {
        QRegularExpressionMatch match = matchIterator.next();
        QString jsonCandidate = match.captured(0);

        // Verificamos si contiene las claves necesarias
        if (jsonCandidate.contains(R"("opt")") && jsonCandidate.contains(R"("target")"))
        {
            jsonObjects.append(jsonCandidate);
            lastValidEnd = match.capturedEnd(0); // Solo se actualiza si fue válido
        }
        else
        {
            // Si no contiene las claves necesarias, lo dejamos en el fragmento
            break;
        }
    }

    // Guardamos el resto del input como posible fragmento incompleto
    incompleteFragment = combinedInput.mid(lastValidEnd);

    return jsonObjects;
}


QByteArray fromHex(const QString &hex)
{
    QByteArray data;
    for (int i = 0; i < hex.size(); i += 2)
    {
        data.append(static_cast<char>(hex.mid(i, 2).toInt(nullptr, 16)));
    }
    return data;
}

QString obtenerIP()
{
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface &interface : interfaces)
    {
        if (interface.flags().testFlag(QNetworkInterface::IsUp) &&
            interface.flags().testFlag(QNetworkInterface::IsRunning) &&
            !interface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {

            // Filtrar las direcciones IPv4
            for (const QNetworkAddressEntry &entry : interface.addressEntries())
            {
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                {
                    return entry.ip().toString();
                }
            }
        }
    }
    return "No se pudo obtener la IP";
}

Header stringToHeader(const QString &str)
{
    if (str == "MSG")
    {
        return MSG;
    }
    else if (str == "REQUEST_MSG")
    {
        return REQUEST_MSG;
    }
    else if (str == "IMG")
    {
        return IMG;
    }
    else if (str == "REQUEST_IMG")
    {
        return REQUEST_IMG;
    }
    else
    {
        qDebug()<< "Error in stringToHeader with string: " << str;
        Q_ASSERT(false);
        return MSG;
    }
}

// Función para convertir un Header enum a QString
QString headerToString(Header header)
{
    switch (header)
    {
    case MSG:
        return "MSG";
    case REQUEST_MSG:
        return "REQUEST_MSG";
    case IMG:
        return "IMG";
    case REQUEST_IMG:
        return "REQUEST_IMG";
    default:
        Q_ASSERT(false);
        return "MSG";
    }
}

Target stringToTarget(const QString &str)
{
    if (str == "Joystick_Position")
        return Joystick_Position;
    else if (str == "Request_Map_SLAM")
        return Request_Map_SLAM;
    else if (str == "Robot_Position_Pixel")
        return Robot_Position_Pixel;
    else if (str == "Request_Robot_Position")
        return Request_Robot_Position;
    else if (str == "Robot_Position_Pixel_Initialpose")
        return Robot_Position_Pixel_Initialpose;
    else if (str == "Img_Map_SLAM")
        return Img_Map_SLAM;
    else if (str == "Img_Map_Path")
        return Img_Map_Path;
    else if (str == "Save_Map")
        return Save_Map;
    else if (str == "State_Remote_Controlled")
        return State_Remote_Controlled;
    else if (str == "State_Menu")
        return State_Menu;
    else if (str == "Img_Map_Select")
        return Img_Map_Select;
    else if (str == "Map_Name")
        return Map_Name;
    else if (str == "Map_Info_Image_Size")
        return Map_Info_Image_Size;
    else if (str == "Change_Map_Name")
        return Change_Map_Name;
    else if (str == "Delete_Map")
        return Delete_Map;
    else if (str == "Img_Map_Select")
        return Img_Map_Select;
    else if (str == "Init_Bringup")
        return Init_Bringup;
    else if (str == "Initial_Pose")
        return Initial_Pose;
    else if (str == "Goal_Pose")
        return Goal_Pose;
    else if (str == "Waypoint_Follower")
        return Waypoint_Follower;
    else if (str == "Stop_Process")
        return Stop_Process;
    else if (str == "Goal_Pose_Path")
        return Goal_Pose_Path;
    else if (str == "All_Information_Pose")
        return All_Information_Pose;
    else if (str == "Battery_Level")    
        return Battery_Level;
    else
    {
        Q_ASSERT(false);
        return Joystick_Position;
    }
}

QString targetToString(Target target)
{
    switch (target)
    {
    case Joystick_Position:
        return "Joystick_Position";
    case Request_Map_SLAM:
        return "Request_Map_SLAM";
    case Robot_Position_Pixel:
        return "Robot_Position_Pixel";
    case Request_Robot_Position:
        return "Request_Robot_Position";
    case Robot_Position_Pixel_Initialpose:
        return "Robot_Position_Pixel_Initialpose";
    case Img_Map_SLAM:
        return "Img_Map_SLAM";
    case Img_Map_Path:
        return "Img_Map_Path";
    case Save_Map:
        return "Save_Map";
    case State_Remote_Controlled:
        return "State_Remote_Controlled";
    case State_Menu:
        return "State_Menu";
    case Map_Name:
        return "Map_Name";
    case Map_Info_Image_Size:
        return "Map_Info_Image_Size";
    case Change_Map_Name:
        return "Change_Map_Name";
    case Delete_Map:
        return "Delete_Map";
    case Img_Map_Select:
        return "Img_Map_Select";
    case Init_Bringup:
        return "Init_Bringup";
    case Initial_Pose:
        return "Initial_Pose";
    case Goal_Pose:
        return "Goal_Pose";
    case Waypoint_Follower:
        return "Waypoint_Follower";
    case Stop_Process:
        return "Stop_Process";
    case Goal_Pose_Path:
        return "Goal_Pose_Path";
    case All_Information_Pose:
        return "All_Information_Pose";
    case Battery_Level:
        return "Battery_Level";
    default:
        Q_ASSERT(false);
        return "Joystick_Position";
    }
}
