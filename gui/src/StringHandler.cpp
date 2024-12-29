#include "../include/StringHandler.h"
#include "../include/utils.h"
#include "../include/ToJson.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <QBuffer>
#include <QDebug>
#include <QFile>

StringHandler::StringHandler(QObject *parent) : QObject(parent), cliente(nullptr)
{
    m_currentMove = Stop;
}
void StringHandler::setClient(Cliente *cli){ cliente = cli;}

bool StringHandler::isInSameNetwork(const QString &ip1, const std::string& subnetMask) {
    if (ip1.isEmpty() || ip1 == "")
    {
        return 0;
    }
    std::string ip1_ = ip1.toStdString();
    for (char ch : ip1_) {
        if (!(std::isdigit(ch) || ch == '.')) {
            return false;
        }
    }

    QString ip2 = obtenerIP();
    std::string ip2_ = ip2.toStdString();
    std::cout << ip2_ << std::endl;
    auto ipToInt = [](const std::string& ip) -> std::vector<int> {
        std::vector<int> parts;
        std::stringstream ss(ip);
        std::string segment;
        while (std::getline(ss, segment, '.')) {
            parts.push_back(std::stoi(segment));
        }
        return parts;
    };

    std::vector<int> ip1Parts = ipToInt(ip1_);
    std::vector<int> ip2Parts = ipToInt(ip2_);
    std::vector<int> maskParts = ipToInt(subnetMask);

    for (int i = 0; i < 4; ++i) {
        if ((ip1Parts[i] & maskParts[i]) != (ip2Parts[i] & maskParts[i])) {
            return false;
        }
    }
    // ip a la que nos conectamos
    // cliente.connectToServer(ip1, 8080);
    // cliente.connectToServer("127.0.0.1", 8080);
    cliente->connect2host(ip1);
    //--------------
    return true;
}

QString StringHandler::getImageSource()
{
    qDebug() << m_imageSource;
    return m_imageSource;
}

// void StringHandler::setCurrentMove(StringHandler::Move newCurrentMove)
// {
//     if (m_currentMove == newCurrentMove)
//         return;
//     m_currentMove = newCurrentMove;
//     emit currentMoveChanged();
//     qDebug() << "Movimiento seleccionado:" << moveToString(newCurrentMove);
//     //--------enviar mensaje-------------//
//     // if (newCurrentMove == Stop)
//     // {
//     //     //cliente->sendImageMap(imagen_link);

//     // }
//     cliente->sendMessagePosition(moveToString(newCurrentMove));
//     cliente->sendRequestImg("map_scan");
// }

void StringHandler::setCurrentMove(StringHandler::Move newCurrentMove)
{
    if (m_currentMove == newCurrentMove)
        return;
    m_currentMove = newCurrentMove;
    emit currentMoveChanged();
    //qDebug() << "Movimiento seleccionado:" << moveToString(newCurrentMove);
    //--------enviar mensaje-------------//
    // if (newCurrentMove == Stop)
    // {
    //     //cliente->sendImageMap(imagen_link);

    // }
    float angular;
    float lineal;
    moveToString(newCurrentMove, lineal, angular);
    cliente->sendMessage(sendJoystickPosition(angular, lineal));
    cliente->sendMessage(sendRequestMapSlam());
}

void StringHandler::getImageMapSlam(const QJsonObject &json)
{
    QString name = json["name"].toString();
    QByteArray data = fromHex(json["data"].toString());
    size_t size = json["size"].toInt();
    totalSize = json["total_size"].toInt();
    totalFrames = json["total_frame"].toInt();
    receivedFrames++;

    // Append the received fragment to the image buffer
    imageBuffer.append(data);

    qDebug() << "Received frame:" << json["num_frame"].toInt() << "of" << totalFrames;

    // If all frames are received, save the image
    if (receivedFrames == totalFrames)
    {
        QFile imageFile(name + ".pgm");
        if (!imageFile.open(QIODevice::WriteOnly))
        {
            qWarning() << "Failed to save the image file";
            return;
        }
        imageFile.write(imageBuffer);
        imageFile.close();
        qDebug() << "Image saved as:" << imageFile.fileName();

        // Reset for the next image
        imageBuffer.clear();
        totalSize = 0;
        receivedFrames = 0;
        totalFrames = 0;
    }

}

void StringHandler::getRobotPositionPixel(const QJsonObject &json)
{

}


void StringHandler::setImage(const QByteArray &data)
{
    if (!data.isEmpty()) {
        QImage image;
        // qDebug() << data;
        if (image.loadFromData(data)) { // Intenta cargar los datos como una imagen
            // Convertir la imagen a un URL de datos en memoria
            qDebug() << "CONVIRTIENDO";
            QByteArray imageData;
            QBuffer buffer(&imageData);
            buffer.open(QIODevice::WriteOnly);
            image.save(&buffer, "PGM"); // Guarda la imagen en formato PGM en memoria

            qDebug() << "HOLA";
            m_imageSource = "data:image/pgm;base64," + imageData.toBase64();
            qDebug() <<"poraquí"<< m_imageSource;
            emit imageSourceChanged();
        } else {
            qWarning() << "Invalid image data!";
        }
    }
}

void StringHandler::moveToString(StringHandler::Move move, float& linear, float& angular) const {
    switch (move) {
    case Recto:
        linear = 0.2f;
        angular = 0.0f;
        break;
    case Atras:
        linear = -0.2f;
        angular = 0.0f;
        break;
    case Giro_Izquierda:
        linear = 0.0f;
        angular = 0.2f;
        break;
    case Giro_Derecha:
        linear = 0.0f;
        angular = -0.2f;
        break;
    case Mas_Rapido:
        linear = 0.4f;
        angular = 0.0f;
        break;
    case Mas_Lento:
        linear = 0.1f;
        angular = 0.0f;
        break;
    case Stop:
        linear = 0.0f;
        angular = 0.0f;
        break;
    default:
        linear = 0.0f;
        angular = 0.0f;
        break;
    }
}

StringHandler::Move StringHandler::stringToMove(const QString &move) const {
    if (move == "Recto") return Recto;
    if (move == "Atras") return Atras;
    if (move == "Giro_Izquierda") return Giro_Izquierda;
    if (move == "Giro_Derecha") return Giro_Derecha;
    if (move == "Mas_Rapido") return Mas_Rapido;
    if (move == "Mas_Lento") return Mas_Lento;
    if (move == "Stop") return Stop;
    return Stop; // Valor predeterminado
}




QString StringHandler::imageSource() const
{
    return m_imageSource;
}
