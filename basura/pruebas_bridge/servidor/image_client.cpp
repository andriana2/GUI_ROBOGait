#include "ImageClient.h"

ImageClient::ImageClient(QObject *parent) : QObject(parent) {}

void ImageClient::sendImage(const QString &host, quint16 port, const QString &imagePath)
{
    QTcpSocket socket;
    socket.connectToHost(host, port);

    if (!socket.waitForConnected()) {
        qDebug() << "No se pudo conectar al servidor.";
        return;
    }

    QFile file(imagePath);
    if (file.open(QIODevice::ReadOnly)) {
        qDebug() << "Enviando imagen...";

        QByteArray data = file.readAll();
        socket.write(data);
        socket.waitForBytesWritten();
        qDebug() << "Imagen enviada correctamente.";

    } else {
        qDebug() << "No se pudo abrir el archivo de imagen para leer.";
    }

    socket.disconnectFromHost();
}

