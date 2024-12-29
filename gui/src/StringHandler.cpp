#include "../include/StringHandler.h"
#include "../include/utils.h"
#include "../include/ToJson.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <QBuffer>
#include <QDebug>
#include <QFile>
#include <QTimer>

StringHandler::StringHandler(QObject *parent) : QObject(parent), cliente(nullptr)
{
    periodicTimer = new QTimer(this);
    connect(periodicTimer, &QTimer::timeout, this, [this]() {
        cliente->sendMessage(sendJoystickPosition(currentAngular, currentLineal));
        if (SLAM_ON) {
            cliente->sendMessage(sendRequestMapSlam());
        }
    });
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

void StringHandler::setCurrentMove(const QString &lineal, const QString &angular) {
    bool ok;
    bool moveStopLocal;

    // Convertir lineal a float y redondear
    float lineal_f = std::round(lineal.toFloat(&ok) * 10000.0f) / 10000.0f;
    if (!ok) return; // Salir si la conversión falla

    // Convertir angular a float y redondear
    float angular_f = std::round(angular.toFloat(&ok) * 10000.0f) / 10000.0f;
    if (!ok) return; // Salir si la conversión falla

    // Determinar si el robot está detenido
    float margin = 0.0001;
    moveStopLocal = (std::abs(lineal_f) <= margin && std::abs(angular_f) <= margin);
    if (moveStopLocal && moveStop) {
        // Si ya está detenido y no hay cambios, no hacemos nada
        return;
    } else if (moveStopLocal && !moveStop) {
        // El robot se detuvo: enviar posición cero y detener mensajes periódicos
        cliente->sendMessage(sendJoystickPosition(0.0f, 0.0f));
        periodicTimer->stop();
        moveStop = true;
    } else {
        // El robot está en movimiento: actualizar valores y activar el temporizador
        currentAngular = angular_f;
        currentLineal = lineal_f;

        if (!periodicTimer->isActive()) {
            periodicTimer->start(500);
        }
        moveStop = false;
    }
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

            m_imageSource = "data:image/pgm;base64," + imageData.toBase64();
            qDebug() <<"poraquí"<< m_imageSource;
            emit imageSourceChanged();
        } else {
            qWarning() << "Invalid image data!";
        }
    }
}

QString StringHandler::imageSource() const
{
    return m_imageSource;
}
