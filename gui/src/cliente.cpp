#include "../include/cliente.h"
#include <QDebug>

//Cliente::Cliente(QObject *parent) : QObject(parent), socket(new QTcpSocket(this))
Cliente::Cliente(QObject *parent) : QObject(parent)
{
    // connect(socket, &QTcpSocket::connected, this, []() {
    //     qDebug() << "Conectado al servidor.";
    // });
    // ip = "127.0.0.1";
    puerto = 8080;
    // Conectar la señal para recibir datos del servidor
    //connect(socket, &QTcpSocket::readyRead, this, &Cliente::processServerResponse);
}
Cliente::~Cliente()
{
   // socket->close();
}

// Cliente::~Cliente()
// {
//     socket->close();
// }

// void Cliente::connectToServer(const QString &host, quint16 port)
// {
//     socket->connectToHost(host, port);
//     if (!socket->waitForConnected()) {
//         qDebug() << "No se pudo conectar al servidor.";
//         return;
//     }
// }

void Cliente::sendMessage(const QString &message)
{
    QTcpSocket socket;
    socket.connectToHost(ip, puerto);
    qDebug() << "Conectado a ip: " << ip << " y al puerto " << puerto;

    if (!socket.waitForConnected()) {
        qDebug() << "No se pudo conectar al servidor.";
        return;
    }

    QByteArray data = message.toUtf8() + "\n";

    if (socket.write(data) == -1) {
        qDebug() << "Error al enviar el mensaje.";
    } else {
        socket.waitForBytesWritten();  // Espera a que se haya enviado el mensaje
        qDebug() << message + ": Mensaje enviado correctamente.";
    }
    socket.disconnectFromHost();
    // if (socket->state() == QTcpSocket::ConnectedState) {
    //     qDebug() << "MENSAGE " + message;
    //     socket->write(message.toUtf8());  // Convertir el string a bytes y enviarlo
    //     socket->flush();  // Asegurarse de que el mensaje se envíe inmediatamente
    // }
    // else
    //     qDebug() << "NO ME HE CONECTADO";
}

void Cliente::processServerResponse()
{
    // QByteArray response = socket->readAll();  // Leer la respuesta del servidor
    // qDebug() << "Respuesta del servidor:" << response;
}
