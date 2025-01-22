#include "../include/cliente.h"
#include "../include/utils.h"
#include <QDebug>
#include <QAbstractSocket>
#include <QJsonArray>
#include <vector>
#include <string>

Cliente::Cliente(int portNumber) : QObject() //, stringHandler(nullptr)
{
    socket = new QTcpSocket();
    maping = true;

    port = portNumber;

    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &Cliente::connectionTimeout);

    connect(socket, &QTcpSocket::disconnected, this, &Cliente::closeConnection);

    connect(socket, &QTcpSocket::readyRead, this, &Cliente::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &Cliente::onErrorOccurred);
}

void Cliente::setStringHandler(StringHandler *sh) { stringHandler = sh; }

void Cliente::onReadyRead()
{
    while (socket->bytesAvailable())
    {
        QByteArray rawData = socket->readAll();
        QString dataString = QString::fromUtf8(rawData);
        // qDebug() << dataString;
        // qDebug() << "su tamaño es de --------------->" << dataString.size();
        QVector<QString> jsonObjects = extractJSONObjects(dataString);
        for (const QString &jsonStr : jsonObjects)
        {
            this->jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());

            if (!jsonDoc.isObject())
            {
                qWarning() << "Invalid JSON received";
                continue;
            }

            QJsonObject jsonObj = jsonDoc.object();
            processJson(jsonDoc);
        }
    }
}

void Cliente::processJson(const QJsonDocument &json)
{
    QJsonObject jsonObj = json.object();
    if (stringToHeader(jsonObj["opt"].toString()) == IMG)
    {
        if (stringToTarget(jsonObj["target"].toString()) == Img_Map_SLAM)
            stringHandler->getImageMapSlam(jsonObj);
        else if (stringToTarget(jsonObj["target"].toString()) == Img_Map_Path)
            stringHandler->getImageMapPath(jsonObj);
    }
    else if (stringToHeader(jsonObj["opt"].toString()) == REQUEST_IMG)
    {
    }
    else if (stringToHeader(jsonObj["opt"].toString()) == MSG)
    {
        if (stringToTarget(jsonObj["target"].toString()) == Robot_Position_Pixel)
            stringHandler->getRobotPositionPixel(jsonObj);
        if (stringToTarget(jsonObj["target"].toString()) == Map_Name) // vector de mapas
        {
            if (jsonObj.contains("vec_map_name") && jsonObj["vec_map_name"].isArray())
            {
                QJsonArray jsonArray = jsonObj["vec_map_name"].toArray();
                std::vector<std::string> vec_map_name;
                for (const auto &item : jsonArray)
                {
                    vec_map_name.push_back(item.toString().toStdString());
                }
                stringHandler->loadData(vec_map_name);
            }
            else
            {
                qWarning() << "Error: 'vec_map_name' no existe o no es un array.";
            }
        }
        if (stringToTarget(jsonObj["target"].toString()) == Map_Info_Image_Size)
        {
            mapInfo->setImageSize(jsonObj["width"].toInt(), jsonObj["height"].toInt());
            mapInfo->setMapName(jsonObj["map_name"].toString());
            qDebug() << "width: " << jsonObj["width"].toInt() << "height: " << jsonObj["height"].toInt() << " Map name: " << jsonObj["map_name"].toString();
        }
    }
    else if (stringToHeader(jsonObj["opt"].toString()) == REQUEST_MSG)
    {
    }
}

void Cliente::connect2host(const QString hostAddress)
{
    host = hostAddress;
    timeoutTimer->start(3000);
    socket->connectToHost(host, port);
    connect(socket, &QTcpSocket::connected, this, &Cliente::connected);
    qDebug() << "Conectado a ip: " << host << " y al puerto " << port;

    if (!socket->waitForConnected())
    {
        qDebug() << "No se pudo conectar al servidor.";
        return;
    }
}

void Cliente::connectionTimeout()
{
    // qDebug() << tcpSocket->state();
    if (socket->state() == QAbstractSocket::ConnectingState)
    {
        socket->abort();
        // emit tcpSocket->error(QAbstractSocket::SocketTimeoutError);
    }
}

void Cliente::connected()
{
    status = true;
    emit statusChanged(status);
}

bool Cliente::getStatus() { return status; }

void Cliente::sendMessage(const QJsonDocument &json)
{
    if (socket->state() == QTcpSocket::ConnectedState)
    {
        QByteArray byteArray = json.toJson(QJsonDocument::Compact);
        socket->write(byteArray);
        // socket->flush(); // Enviar todo junto
        qDebug() << "Full message sent: " << QString::fromUtf8(byteArray);
    }
    else
    {
        qDebug() << "Socket is not connected!";
    }
}

// void Cliente::sendRequestImg(const QString &target)
// {
//     if (target == "map_scan")
//     {
//         QString start = "REQUEST_IMG:0:" + target + "\n";
//         QByteArray full = start.toUtf8();
//         socket->write(full);
//         socket->flush();
//         qDebug() << "Full send request img " << full;
//     }
// }

// void Cliente::receiveImageMap(const QByteArray &data)
// {
//     QImage image;
//     if (image.loadFromData(data)) {
//         //stringHandler->setImage(data);  // Emitir la señal con la imagen
//     }

// }

// void Cliente::sendMessage(const QString &message)
// {
//     QTcpSocket socket;
//     socket.connectToHost(ip, puerto);
//     qDebug() << "Conectado a ip: " << ip << " y al puerto " << puerto;

//     if (!socket.waitForConnected()) {
//         qDebug() << "No se pudo conectar al servidor.";
//         return;
//     }

//     QByteArray data = message.toUtf8() + "\n";

//     if (socket.write(data) == -1) {
//         qDebug() << "Error al enviar el mensaje.";
//     } else {
//         socket.waitForBytesWritten();  // Espera a que se haya enviado el mensaje
//         qDebug() << message + ": Mensaje enviado correctamente.";
//     }
//     socket.disconnectFromHost();
//     // if (socket->state() == QTcpSocket::ConnectedState) {
//     //     qDebug() << "MENSAGE " + message;
//     //     socket->write(message.toUtf8());  // Convertir el string a bytes y enviarlo
//     //     socket->flush();  // Asegurarse de que el mensaje se envíe inmediatamente
//     // }
//     // else
//     //     qDebug() << "NO ME HE CONECTADO";
// }

void Cliente::closeConnection()
{
    timeoutTimer->stop();

    // qDebug() << tcpSocket->state();
    disconnect(socket, &QTcpSocket::connected, 0, 0);
    disconnect(socket, &QTcpSocket::readyRead, 0, 0);

    bool shouldEmit = false;
    switch (socket->state())
    {
    case 0:
        socket->disconnectFromHost();
        shouldEmit = true;
        break;
    case 2:
        socket->abort();
        shouldEmit = true;
        break;
    default:
        socket->abort();
    }

    if (shouldEmit)
    {
        status = false;
        emit statusChanged(status);
    }
}

void Cliente::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qDebug() << "Socket error:" << error;
}

void Cliente::setMapInfo(MapInfo *sh)
{
    if (mapInfo == sh)
        return;
    mapInfo = sh;
}
