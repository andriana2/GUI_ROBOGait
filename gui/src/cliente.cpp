#include "../include/cliente.h"
#include "../include/utils.h"
#include <QDebug>
#include <QAbstractSocket>

Cliente::Cliente(int portNumber) : QObject()//, stringHandler(nullptr)
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

void Cliente::setStringHandler(StringHandler *sh){ stringHandler = sh;}

void Cliente::onReadyRead() {
    while (socket->bytesAvailable()) {
        QByteArray rawData = socket->readAll();
        QString dataString = QString::fromUtf8(rawData);
        QVector<QString> jsonObjects = extractJSONObjects(dataString);
        for (const QString& jsonStr : jsonObjects) {
            this->jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());

            if (!jsonDoc.isObject()) {
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
    if(stringToHeader(jsonObj["opt"].toString()) == IMG)
    {
        if(stringToTarget(jsonObj["target"].toString()) == Img_Map_SLAM)
            stringHandler->getImageMapSlam(jsonObj);
    }
    else if(stringToHeader(jsonObj["opt"].toString()) == REQUEST_IMG)
    {

    }
    else if(stringToHeader(jsonObj["opt"].toString()) == MSG)
    {
        if(stringToTarget(jsonObj["target"].toString()) == Robot_Position_Pixel)
            stringHandler->getRobotPositionPixel(jsonObj);
    }
    else if(stringToHeader(jsonObj["opt"].toString()) == REQUEST_MSG)
    {

    }
}


// void Cliente::onReadyRead() {
//     static QByteArray buffer;
//     static qint64 expectedSize = -1;
//     static QString dataType;

//     // Mientras haya datos disponibles
//     while (socket->bytesAvailable()) {
//         // Leer encabezado si aún no lo tenemos
//         if (expectedSize == -1 && dataType.isEmpty()) {
//             // Leer encabezado completo (terminado en '\n')
//             if (!buffer.contains('\n')) {
//                 buffer.append(socket->readAll());
//                 if (!buffer.contains('\n')) {
//                     return; // Aún no hemos recibido el encabezado completo
//                 }
//             }

//             // Procesar el encabezado
//             QByteArray headerData = buffer.left(buffer.indexOf('\n'));
//             buffer.remove(0, buffer.indexOf('\n') + 1);

//             // Ejemplo de encabezado: "IMG:12345:map_drawing\n"
//             QStringList headerParts = QString(headerData).split(':');
//             if (headerParts.size() != 3) {
//                 qWarning() << "Encabezado inválido:" << headerData;
//                 return;
//             }

//             dataType = headerParts[0];
//             expectedSize = headerParts[1].toLongLong();
//             qDebug() << "Recibiendo" << dataType << "de tamaño" << expectedSize;
//         }

//         // Leer contenido del mensaje
//         if (expectedSize > 0) {
//             buffer.append(socket->readAll());
//             if (buffer.size() >= expectedSize) {
//                 // Procesar contenido según el tipo
//                 if (dataType == "IMG") {
//                     // qDebug() << buffer;
//                     stringHandler->setImage(buffer);
//                 } else if (dataType == "MSG") {
//                     QString convertedString = QString::fromUtf8(buffer);
//                     qDebug() << convertedString;
//                     //processMessage(buffer);
//                 } else {
//                     qWarning() << "Tipo de datos no reconocido:" << dataType;
//                 }

//                 // Limpiar para el próximo mensaje
//                 buffer.clear();
//                 expectedSize = -1;
//                 dataType.clear();

//                 // // Enviar confirmación al servidor
//                 // socket->write("ACK");
//                 // socket->flush();
//             }
//         }
//     }
// }

void Cliente::connect2host(const QString hostAddress)
{
    host = hostAddress;
    timeoutTimer->start(3000);
    socket->connectToHost(host, port);
    connect(socket, &QTcpSocket::connected, this, &Cliente::connected);
    qDebug() << "Conectado a ip: " << host << " y al puerto " << port;

    if (!socket->waitForConnected()) {
        qDebug() << "No se pudo conectar al servidor.";
        return;
    }
}

void Cliente::connectionTimeout()
{
    //qDebug() << tcpSocket->state();
    if(socket->state() == QAbstractSocket::ConnectingState)
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

bool Cliente::getStatus() {return status;}

void Cliente::sendMessage(const QJsonDocument &json)
{
    if (socket->state() == QTcpSocket::ConnectedState)
    {
        QByteArray byteArray = json.toJson(QJsonDocument::Compact);
        socket->write(byteArray);
        // socket->flush(); // Enviar todo junto
        qDebug() << "Full message sent: " << QString::fromUtf8(byteArray);
    }else {
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

    //qDebug() << tcpSocket->state();
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

void Cliente::onErrorOccurred(QAbstractSocket::SocketError error) {
    qDebug() << "Socket error:" << error;
}


