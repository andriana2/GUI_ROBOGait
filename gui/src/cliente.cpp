#include "../include/cliente.h"
#include "../include/utils.h"
#include <QDebug>
#include <QAbstractSocket>
#include <QJsonArray>
#include <vector>
#include <string>

Cliente::Cliente(int port_) : QObject(), port_udp_tcp(port_) //, stringHandler(nullptr)
{
    connect(&udpSocket, &QUdpSocket::readyRead, this, &Cliente::answerUdp);

    socket = new QTcpSocket();
    maping = true;

    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &Cliente::connectionTimeout);

    connect(socket, &QTcpSocket::disconnected, this, &Cliente::closeConnection);

    connect(socket, &QTcpSocket::readyRead, this, &Cliente::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &Cliente::onErrorOccurred);
}

Cliente::~Cliente()
{
    if (socket->isOpen())
    {
        socket->disconnectFromHost();
        if (socket->state() != QAbstractSocket::UnconnectedState)
        {
            socket->waitForDisconnected(3000);
        }
    }
    delete socket;
    delete timeoutTimer;
}

void Cliente::disconnectRobot()
{
    if (socket->isOpen())
    {
        socket->disconnectFromHost();
        if (socket->state() != QAbstractSocket::UnconnectedState)
        {
            socket->waitForDisconnected(3000);
        }
    }
}

void Cliente::setStringHandler(StringHandler *sh) { stringHandler = sh; }
void Cliente::setMapInfo(MapInfo *sh) { mapInfo = sh; }
void Cliente::setDatabase(Database *sh) { database = sh; }

void Cliente::answerUdp()
{
    while (udpSocket.hasPendingDatagrams())
    {
        QByteArray buffer;
        buffer.resize(udpSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 port;
        udpSocket.readDatagram(buffer.data(), buffer.size(), &sender, &port);
        QString mensaje(buffer);
        // qDebug() << "Recibido:" << mensaje;

        if (mensaje.startsWith("SERVER_ACK"))
        {
            servidor = sender;

            QRegularExpression regex("SERVER_ACK:\\s*(\\w+)\\s+TYPE:\\s*(\\w+)");
            QRegularExpressionMatch match = regex.match(mensaje);

            if (match.hasMatch())
            {
                QString serverName = match.captured(1);
                QString serverType = match.captured(2);

                qDebug() << "Servidor encontrado en" << servidor.toString();
                database->setIpServerDDBB(servidor.toString());
                qDebug() << "Nombre del servidor:" << serverName;
                qDebug() << "Tipo de servidor:" << serverType;

                connect2host(servidor.toString());
                stringHandler->setStrFindRobot("Robot " + serverName + " " + serverType + " encontrado");
            }
            else
            {
                qDebug() << "Formato inesperado en SERVER_ACK";
            }
        }
        else if (mensaje.contains("ACK"))
        {
            // qDebug() << "ACK recibido";
            QByteArray buffer2 = {"ACK"};
            udpSocket.writeDatagram(buffer2, sender, port);
        }
        else if (mensaje.contains("battery"))
        {
            QRegularExpression regex("battery:\\s*(\\d+)"); // example: "battery: 75"
            QRegularExpressionMatch match = regex.match(mensaje);

            if (match.hasMatch())
            {
                QString batteryValue = match.captured(1);

                // Optionally, convert the battery value to an integer
                int batteryLevel = batteryValue.toInt();
                qDebug() << "Battery level as integer:" << batteryLevel;

                stringHandler->setBatteryPercentage(batteryLevel);
            }
            else
            {
                qDebug() << "Unexpected format for battery message.";
            }
        }
    }
}

void Cliente::onReadyRead()
{
    while (socket->bytesAvailable())
    {
        QByteArray rawData = socket->readAll();
        QString dataString = QString::fromUtf8(rawData);
        QVector<QString> jsonObjects = extractJSONObjects(dataString);
        for (auto &jsonStr : jsonObjects)
        {
            this->jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());

            if (!jsonDoc.isObject())
            {
                qWarning() << "Invalid JSON received";
                continue;
            }

            // QJsonObject jsonObj = jsonDoc.object();
            processJson(jsonDoc);
        }
    }
}

void Cliente::processJson(const QJsonDocument &json)
{
    QJsonObject jsonObj = json.object();
    qDebug() << "Contenido del JSON:";
    qDebug() << json.toJson(QJsonDocument::Indented);
    if (stringToHeader(jsonObj["opt"].toString()) == IMG)
    {
        if (stringToTarget(jsonObj["target"].toString()) == Img_Map_SLAM)
            stringHandler->getImageMapSlam(jsonObj);
        else if (stringToTarget(jsonObj["target"].toString()) == Img_Map_Path)
            stringHandler->getImageMapPath(jsonObj);
    }
    // else if (stringToHeader(jsonObj["opt"].toString()) == REQUEST_IMG)
    // {
    // }
    // else if (stringToHeader(jsonObj["opt"].toString()) == REQUEST_MSG)
    // {
    // }
    else if (stringToHeader(jsonObj["opt"].toString()) == MSG)
    {
        if (stringToTarget(jsonObj["target"].toString()) == Stop_Process)
        {
            // TODO stop_process with client
            // &
            // &
            // &
            // &
            // &
            // &
            // &
            // &
            // &
        }
        if(stringToTarget(jsonObj["target"].toString()) == Battery_Level)
            stringHandler->batteryLevel(jsonObj);
        if (stringToTarget(jsonObj["target"].toString()) == Robot_Position_Pixel)
            stringHandler->getRobotPositionPixel(jsonObj);
        if (stringToTarget(jsonObj["target"].toString()) == Robot_Position_Pixel_Initialpose)
            mapInfo->getRobotPositionInitialpose(jsonObj);
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
            mapInfo->setResolution(jsonObj["resolution"].toDouble());
            qDebug() << "width: " << jsonObj["width"].toInt() << "height: " << jsonObj["height"].toInt() << " Map name: " << jsonObj["map_name"].toString() << " Resolution: " << jsonObj["resolution"].toDouble();
        }
        if (stringToTarget(jsonObj["target"].toString()) == Goal_Pose_Path)
        {
            QString jsonString = json.toJson(QJsonDocument::Indented);
            mapInfo->parseJsonToQList(jsonObj);
        }
    }
}

void Cliente::connect2host(const QString hostAddress)
{
    host = hostAddress;
    timeoutTimer->start(3000);

    // Reconnect signals if they were disconnected
    
    socket->connectToHost(host, port_udp_tcp);
    connect(socket, &QTcpSocket::connected, this, &Cliente::connected);
    connect(socket, &QTcpSocket::readyRead, this, &Cliente::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &Cliente::onErrorOccurred);
    qDebug() << "Conectado a ip: " << host << " y al puerto " << port_udp_tcp;
    setIpRobot(host);

    if (!socket->waitForConnected())
    {
        qDebug() << "No se pudo conectar al servidor.";
        return;
    }
}

void Cliente::startSearchUdp()
{
    qDebug() << "Buscando el servidor UDP... en el puerto " << port_udp_tcp;
    udpSocket.bind(QHostAddress::AnyIPv4, port_udp_tcp);

    QByteArray first_word_identify_server = "DISCOVER";
    udpSocket.writeDatagram(first_word_identify_server, QHostAddress::Broadcast, port_udp_tcp);
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

void Cliente::sendMessage(const QJsonDocument &json)
{
    if (json.isObject() && json.object().contains("Stop_Process"))
    {
        stringHandler->stopTimerBattery();
    }
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

void Cliente::closeConnection()
{
    qDebug() << "I am in CLOSE CONNECTION!!!";
    timeoutTimer->stop();

    // Disconnect signals
    disconnect(socket, &QTcpSocket::readyRead, this, &Cliente::onReadyRead);
    disconnect(socket, &QTcpSocket::connected, this, &Cliente::connected);
    disconnect(socket, &QTcpSocket::errorOccurred, this, &Cliente::onErrorOccurred);

    // Reset the socket
    socket->abort();
    delete socket;
    socket = new QTcpSocket();

    // Emit status change
    status = false;
    emit statusChanged(status);
}

void Cliente::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qDebug() << "Socket error:" << error;
    stringHandler->setErrorConnection(true);
    clear();
}

QString Cliente::ipRobot() const
{
    return m_ipRobot;
}

void Cliente::setIpRobot(const QString &newIpRobot)
{
    if (m_ipRobot == newIpRobot)
        return;
    m_ipRobot = newIpRobot;
    emit ipRobotChanged();
}

void Cliente::clear()
{
    stringHandler->clear_all();
    mapInfo->clearInfoImage();
    database->clear();
}