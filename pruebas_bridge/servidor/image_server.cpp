#include "ImageServer.h"

#include <iostream>

ImageServer::ImageServer(QObject *parent) : QTcpServer(parent), socket(nullptr), saludo("HOLA"), imageFile("imagen_recibida.jpg"){
    // QFile imageFile("imagen_recibida.jpg");
}

void ImageServer::startServer(quint16 port) {
    if (listen(QHostAddress::Any, port)) {
        qDebug() << "Servidor escuchando en el puerto" << port;
    } else {
        qDebug() << "No se pudo iniciar el servidor.";
    }
}

// void ImageServer::incomingConnection(qintptr socketDescriptor)
// {
//     this->socket = new QTcpSocket;
//     socket->setSocketDescriptor(socketDescriptor);

//     if (imageFile.open(QIODevice::WriteOnly)) {
//         connect(socket, &QTcpSocket::readyRead, this, [this]() {
//             this->imageFile.write(this->socket->readAll());
//             std::cout << this->saludo.toStdString() << "que tal" << std::endl;
//         });
//         connect(socket, &QTcpSocket::disconnected, this, [this]() {
//             this->imageFile.close();
//             this->socket->deleteLater();
//             qDebug() << "Imagen recibida correctamente.";
//         });
//     } else {
//         qDebug() << "No se pudo abrir el archivo de imagen para escribir.";
//         socket->deleteLater();
//     }
// }


void ImageServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    qDebug() << "Cliente conectado.";

    QFile imageFile("image.jpg");
    if (imageFile.open(QIODevice::ReadOnly)) {
        QByteArray data = imageFile.readAll();
        socket->write(data);
        socket->flush();  // Asegura que todos los datos se envíen inmediatamente.
        socket->waitForBytesWritten();

        qDebug() << "Imagen enviada al cliente.";
        imageFile.close();
    } else {
        qDebug() << "No se pudo abrir el archivo de imagen para enviar.";
    }

    socket->disconnectFromHost();
    socket->deleteLater();
}

