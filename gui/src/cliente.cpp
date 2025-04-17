#include "../include/cliente.h"
#include "../include/utils.h"
#include <QDebug>
#include <QAbstractSocket>
#include <QJsonArray>
#include <vector>
#include <string>

Cliente::Cliente(int port_tcp, int port_udp) : QObject(), port_tcp(port_tcp) //, stringHandler(nullptr)
{
    connect(&udpSocket, &QUdpSocket::readyRead, this, &Cliente::answerUdp);

    socket = new QTcpSocket();
    maping = true;

    port_udp = port_udp;

    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &Cliente::connectionTimeout);

    connect(socket, &QTcpSocket::disconnected, this, &Cliente::closeConnection);

    connect(socket, &QTcpSocket::readyRead, this, &Cliente::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &Cliente::onErrorOccurred);
}

Cliente::~Cliente() {
    if (socket->isOpen()) {
        socket->disconnectFromHost();
        if (socket->state() != QAbstractSocket::UnconnectedState) {
            socket->waitForDisconnected(3000);
        }
    }
    delete socket;
    delete timeoutTimer;
}

void Cliente::setStringHandler(StringHandler *sh) { stringHandler = sh; }
void Cliente::setMapInfo(MapInfo *sh) { mapInfo = sh; }
void Cliente::setDatabase(Database *sh) { database = sh; }

void Cliente::answerUdp()
{
    while (udpSocket.hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(udpSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 port;
        udpSocket.readDatagram(buffer.data(), buffer.size(), &sender, &port);
        QString mensaje(buffer);
        qDebug() << "Recibido:" << mensaje;

        if (mensaje.startsWith("SERVER_ACK")) {
            servidor = sender;

            QRegularExpression regex("SERVER_ACK:\\s*(\\w+)\\s+TYPE:\\s*(\\w+)");
            QRegularExpressionMatch match = regex.match(mensaje);

            if (match.hasMatch()) {
                QString serverName = match.captured(1);
                QString serverType = match.captured(2);

                qDebug() << "Servidor encontrado en" << servidor.toString();
                qDebug() << "Nombre del servidor:" << serverName;
                qDebug() << "Tipo de servidor:" << serverType;

                connect2host(servidor.toString());
                stringHandler->setStrFindRobot("Robot " + serverName + " " + serverType + " encontrado");
            } else {
                qDebug() << "Formato inesperado en SERVER_ACK";
            }
        } else if (mensaje.contains("ACK")) {
            qDebug() << "ACK recibido";
            QByteArray buffer2 = {"ACK"};
            udpSocket.writeDatagram(buffer2, sender, port);
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
            qDebug()<< "************************************";
            QString jsonString = json.toJson(QJsonDocument::Indented);

            // Imprimirlo en la consola con qDebug()
            qDebug().noquote() << "JSON recibido:\n" << jsonString;
            mapInfo->parseJsonToQList(jsonObj);
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
    socket->connectToHost(host, port_tcp);
    connect(socket, &QTcpSocket::connected, this, &Cliente::connected);
    qDebug() << "Conectado a ip: " << host << " y al puerto " << port_tcp;
    setIpRobot(host);

    if (!socket->waitForConnected())
    {
        qDebug() << "No se pudo conectar al servidor.";
        return;
    }
}

void Cliente::startSearchUdp()
{
    udpSocket.bind(QHostAddress::AnyIPv4, port_udp);

    QByteArray first_word_identify_server = "DISCOVER";
    udpSocket.writeDatagram(first_word_identify_server, QHostAddress::Broadcast, 45454);
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

void Cliente::closeConnection() {
    qDebug() << "Estoy en CLOSE CONNECTION!!!";
    timeoutTimer->stop();

    disconnect(socket, &QTcpSocket::readyRead, 0, 0);

    bool shouldEmit = false;

    switch (socket->state()) {
    case QAbstractSocket::UnconnectedState:
        socket->disconnectFromHost();
        shouldEmit = true;
        break;
    case QAbstractSocket::ConnectedState:
        socket->abort();
        shouldEmit = true;
        break;
    default:
        socket->abort();
    }

    if (shouldEmit) {
        status = false;
        emit statusChanged(status);
    }
}

void Cliente::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qDebug() << "Socket error:" << error;
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
