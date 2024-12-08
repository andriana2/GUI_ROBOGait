#include "../include/cliente.h"
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
    QByteArray data = socket->readAll();
    QString info = QString(data);
    if (info.size() > 600)
    {
        qDebug() << "es una imagen";
        if (maping)
        {
            qDebug() << "estoy maping";
            stringHandler->setImage(data);
            //                reciveImageMap(data);
        }
    }
    else
    {
        qDebug() << "Data received:" << QString(data);

    }
}

void Cliente::connect2host(const QString hostAddress)
{
    host = hostAddress;
    timeoutTimer->start(3000);

    socket->connectToHost(host, port);
    connect(socket, &QTcpSocket::connected, this, &Cliente::connected);
    // connect(tcpSocket, &QTcpSocket::readyRead, this, &Cliente::readyRead);
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

void Cliente::sendMessagePosition(const QString &message)
{
    qDebug() << message;

    if (socket->state() == QTcpSocket::ConnectedState)
    {
        QString start = "MSG:" + QString::number(message.size()) + ":Position_joystick\n";
        QString char_ = "\0";
        QByteArray fullMessage = start.toUtf8() + message.toUtf8() + char_.toUtf8();
        socket->write(fullMessage);
        socket->flush(); // Enviar todo junto
        qDebug() << "Full message sent: " << fullMessage;
    }else {
        qDebug() << "Socket is not connected!";
    }
}

void Cliente::sendRequestImg(const QString &target)
{
    if (target == "map_scan")
    {
        QString start = "REQUEST_IMG:0:" + target + "\n\0";
        QByteArray full = start.toUtf8();
        socket->write(full);
        socket->flush();
        qDebug() << "Full send request img " << full;
    }
}

void Cliente::receiveImageMap(const QByteArray &data)
{
    QImage image;
    if (image.loadFromData(data)) {
        //stringHandler->setImage(data);  // Emitir la señal con la imagen
    }


}
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


