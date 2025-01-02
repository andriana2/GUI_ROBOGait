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
    connect(periodicTimer, &QTimer::timeout, this, [this]()
            {
                static int i = 0;
                if (SLAM_ON && i == 18) {
                    cliente->sendMessage(sendRequestMapSlam());
                    i = 0;
                }
                else
                    cliente->sendMessage(sendJoystickPosition(currentAngular, currentLineal));
                i++; });
}
void StringHandler::setClient(Cliente *cli) { cliente = cli; }

bool StringHandler::isInSameNetwork(const QString &ip1, const std::string &subnetMask)
{
    if (ip1.isEmpty() || ip1 == "")
    {
        return 0;
    }
    std::string ip1_ = ip1.toStdString();
    for (char ch : ip1_)
    {
        if (!(std::isdigit(ch) || ch == '.'))
        {
            return false;
        }
    }

    QString ip2 = obtenerIP();
    std::string ip2_ = ip2.toStdString();
    std::cout << ip2_ << std::endl;
    auto ipToInt = [](const std::string &ip) -> std::vector<int>
    {
        std::vector<int> parts;
        std::stringstream ss(ip);
        std::string segment;
        while (std::getline(ss, segment, '.'))
        {
            parts.push_back(std::stoi(segment));
        }
        return parts;
    };

    std::vector<int> ip1Parts = ipToInt(ip1_);
    std::vector<int> ip2Parts = ipToInt(ip2_);
    std::vector<int> maskParts = ipToInt(subnetMask);

    for (int i = 0; i < 4; ++i)
    {
        if ((ip1Parts[i] & maskParts[i]) != (ip2Parts[i] & maskParts[i]))
        {
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
    // qDebug() << m_imageSource;
    return m_imageSource;
}

void StringHandler::setCurrentMove(const QString &lineal, const QString &angular)
{
    bool ok;
    bool moveStopLocal;

    // Convertir lineal a float y redondear
    float lineal_f = std::round(lineal.toFloat(&ok) * 10000.0f) / 10000.0f;
    if (!ok)
        return; // Salir si la conversión falla

    // Convertir angular a float y redondear
    float angular_f = std::round(angular.toFloat(&ok) * 10000.0f) / 10000.0f;
    if (!ok)
        return; // Salir si la conversión falla

    // Determinar si el robot está detenido
    float margin = 0.0001;
    moveStopLocal = (std::abs(lineal_f) <= margin && std::abs(angular_f) <= margin);
    if (moveStopLocal && moveStop)
    {
        // Si ya está detenido y no hay cambios, no hacemos nada
        return;
    }
    else if (moveStopLocal && !moveStop)
    {
        // El robot se detuvo: enviar posición cero y detener mensajes periódicos
        cliente->sendMessage(sendJoystickPosition(0.0f, 0.0f));
        periodicTimer->stop();
        moveStop = true;
    }
    else
    {
        // El robot está en movimiento: actualizar valores y activar el temporizador
        currentAngular = angular_f;
        currentLineal = lineal_f;

        if (!periodicTimer->isActive())
        {
            periodicTimer->start(200);
        }
        moveStop = false;
    }
}

QString StringHandler::updateMapPaintPoint(QImage &mapa, int columna, int fila, float yaw)
{
    if (mapa.isNull())
    {
        qWarning("Error al cargar el mapa");
        return "";
    }
    if (mapa.format() != QImage::Format_ARGB32)
    {
        mapa = mapa.convertToFormat(QImage::Format_ARGB32);
    }
    if (columna < 0 || columna >= mapa.width() || fila < 0 || fila >= mapa.height())
    {
        qWarning("La posición del robot está fuera de los límites del mapa");
        return "";
    }
    double longitud_flecha = 5.0; // Longitud de la flecha en píxeles
    int columna_flecha = columna + static_cast<int>(longitud_flecha * std::cos(yaw));
    int fila_flecha = fila - static_cast<int>(longitud_flecha * std::sin(yaw)); // Invertir Y para coordenadas

    // Pintar en la imagen
    QPainter painter(&mapa);

    // Dibujar el punto rojo (posición del robot)
    painter.setBrush(QBrush(Qt::red));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPoint(columna, fila), 2, 2); // Radio de 3 píxeles

    // Dibujar la flecha azul (dirección del robot)
    painter.setPen(QPen(Qt::blue, 1)); // Línea azul de 2 píxeles de ancho
    painter.drawLine(QPoint(columna, fila), QPoint(columna_flecha, fila_flecha));

    painter.end();

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);

    if (!mapa.save(&buffer, "PNG"))
    {
        qWarning("Error al guardar el mapa modificado como PNG");
    }
    else
    {
        qDebug() << "Mapa modificado guardado como";
    }
    return QString(buffer.data().toBase64());
}

void StringHandler::getImageMapSlam(const QJsonObject &json)
{
    periodicTimer->stop();
    QByteArray data = QByteArray::fromBase64(json["data"].toString().toUtf8());
    totalSize = json["total_size"].toInt();
    totalFrames = json["total_frame"].toInt();
    if(json["num_frame"].toInt() == 0 && receivedFrames != 0)
    {
        receivedFrames = 0;
    }

    // Append the received fragment to the image buffer
    imageBuffer.append(data);

    qDebug() << "Received frame:" << json["num_frame"].toInt() << "of" << totalFrames << "num recivedFrames: " << receivedFrames;
    receivedFrames++;

    // If all frames are received, save the image
    if (receivedFrames == totalFrames)
    {
        qDebug() << "TODOS LOS FRAMS RECIBIDOS";
        if (imageBuffer.isEmpty())
        {
            qWarning() << "Error: imageBuffer is empty";
            return;
        }

        QImage image;
        if (!image.loadFromData(imageBuffer, "PGM")) // Verificar si la imagen se carga correctamente
        {
            qWarning() << "Error: Unable to load image from imageBuffer";
            return;
        }
        qDebug() << "Image successfully loaded. Size:" << image.size();

        // Modificar el mapa
        QString image_str = updateMapPaintPoint(image, 91, 65, 1.5123);
        if (image_str.isEmpty())
        {
            qWarning() << "Error updating the map";
            return;
        }
        setImageSource(image_str);
        // // Convertir a base64 y guardar
        // m_imageSource = "data:image/png;base64," + image_str; // Usa "png" en lugar de "pgm"
        // //qDebug() << "Path guardado en m_imageSource:" << m_imageSource;
        // emit imageSourceChanged();

        // QImage image;
        // qDebug() << "HAN LLEGADO TODOS LOS FRAMES";
        // QBuffer buffer(&imageBuffer);
        // buffer.open(QIODevice::WriteOnly);
        // image.save(&buffer, "PNG");
        // // MI APORTACION
        // QString image_str = updateMap(image, 91, 65, 1.5123);

        // // FIN MI APORTACION
        // m_imageSource = "data:image/pgm;base64," + image_str; // Guarda el path absoluto
        // qDebug() << "Path guardado en m_imageSource:" << m_imageSource;
        // emit imageSourceChanged();

        // QFile imageFile("../image/temporal_map.pgm");
        // if (!imageFile.open(QIODevice::WriteOnly))
        // {
        //     qWarning() << "Failed to save the image file";
        //     return;
        // }
        // imageFile.write(imageBuffer);
        // imageFile.close();

        // Reset for the next image
        imageBuffer.clear();
        totalSize = 0;
        receivedFrames = 0;
        totalFrames = 0;
    }
}

void StringHandler::setImageSource(const QString &source)
{
    m_imageSource = "data:image/png;base64," + source;
    emit imageSourceChanged();
}

void StringHandler::getRobotPositionPixel(const QJsonObject &json)
{
}

void StringHandler::setImage(const QByteArray &data)
{
    if (!data.isEmpty())
    {
        QImage image;
        // qDebug() << data;
        if (image.loadFromData(data))
        { // Intenta cargar los datos como una imagen
            // Convertir la imagen a un URL de datos en memoria
            qDebug() << "CONVIRTIENDO";
            QByteArray imageData;
            QBuffer buffer(&imageData);
            buffer.open(QIODevice::WriteOnly);
            image.save(&buffer, "PGM"); // Guarda la imagen en formato PGM en memoria

            m_imageSource = "data:image/pgm;base64," + imageData.toBase64();
            qDebug() << "poraquí " << m_imageSource;
            emit imageSourceChanged();
        }
        else
        {
            qWarning() << "Invalid image data!";
        }
    }
}

QString StringHandler::imageSource() const
{
    return m_imageSource;
}
