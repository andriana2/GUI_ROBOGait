#include "../include/utils.h"

// #include <stdexcept>

// #include <iostream>
#include <unistd.h>
// #include <cstring>
#include <sys/types.h>
#include <QNetworkInterface>
#include <QRegularExpression>

QVector<QString> extractJSONObjects(const QString &input)
{
    static QString incompleteFragment; // Guarda fragmentos incompletos entre llamadas
    QVector<QString> jsonObjects;

    // Combina el fragmento incompleto con la nueva entrada
    QString combinedInput = incompleteFragment + input;

    QRegularExpression jsonRegex(R"(\{(?:[^{}]|(?R))*\})");
    QRegularExpressionMatchIterator matchIterator = jsonRegex.globalMatch(combinedInput);

    int lastValidEnd = 0; // Para rastrear hasta dónde se procesó exitosamente

    while (matchIterator.hasNext())
    {
        QRegularExpressionMatch match = matchIterator.next();
        jsonObjects.append(match.captured(0));
        lastValidEnd = match.capturedEnd(0); // Registra el final del último JSON válido
    }

    // Guarda cualquier fragmento después del último JSON válido
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
    {
        return Joystick_Position;
    }
    else if (str == "Request_Map_SLAM")
    {
        return Request_Map_SLAM;
    }
    else if (str == "Robot_Position_Pixel")
    {
        return Robot_Position_Pixel;
    }
    else if (str == "Img_Map_SLAM")
    {
        return Img_Map_SLAM;
    }
    else if (str == "Img_Map_Path")
    {
        return Img_Map_Path;
    }
    else if (str == "Save_Map")
    {
        return Save_Map;
    }
    else if (str == "State_Remote_Controlled")
    {
        return State_Remote_Controlled;
    }
    else if (str == "Img_Map_Select")
    {
        return Img_Map_Select;
    }
    else if (str == "Map_Name")
    {
        return Map_Name;
    }
    else if (str == "Map_Info_Image_Size")
    {
        return Map_Info_Image_Size;
    }
    else if (str == "Change_Map_Name")
    {
        return Change_Map_Name;
    }
    else if (str == "Delete_Map")
    {
        return Delete_Map;
    }
    else if (str == "Img_Map_Select")
    {
        return Img_Map_Select;
    }
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
    case Img_Map_SLAM:
        return "Img_Map_SLAM";
    case Img_Map_Path:
        return "Img_Map_Path";
    case Save_Map:
        return "Save_Map";
    case State_Remote_Controlled:
        return "State_Remote_Controlled";
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
    default:
        Q_ASSERT(false);
        return "Joystick_Position";
    }
}
