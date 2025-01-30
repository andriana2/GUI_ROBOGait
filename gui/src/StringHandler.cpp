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

StringHandler::StringHandler(QObject *parent) : QObject(parent), cliente(nullptr), m_model(new QStringListModel(this))
{
    periodicTimer = new QTimer(this);
    connect(periodicTimer, &QTimer::timeout, this, [this]()
            {
                static int i = 0;
                if (m_mapping && i == 10) {
                    cliente->sendMessage(ToJson::sendRequestMap());
                    i = 0;
                }
                else

                {
                    cliente->sendMessage(ToJson::sendJoystickPosition(currentAngular, currentLineal));
                    if (i == 10)
                        i = 0;
                }
                i++; });
}
void StringHandler::setClient(Cliente *cli) { cliente = cli; }

void StringHandler::setMapInfo(MapInfo *mapIn)
{
    mapInfo = mapIn;
}

bool StringHandler::isInSameNetwork(const QString &ip1, const std::string &subnetMask)
{
    // QString ip_borrar_en_cuanto_sea_posible = "10.0.2.15";
    if (ip1.isEmpty() || ip1 == "")
    {
        return 0;
    }
    std::string ip1_ = ip1.toStdString(); // CAAAAAAAMMMMMMMBIAAAAAAR
    // std::string ip1_ = ip_borrar_en_cuanto_sea_posible.toStdString();
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
    // cliente->connect2host(ip_borrar_en_cuanto_sea_posible);



    //--------------
    return true;
}

QString StringHandler::getImageSource()
{
    // qDebug() << m_imageSource;
    return m_imageSource;
}

void StringHandler::sendStateRemoteControlledHandler(bool mapping, bool in)
{
    cliente->sendMessage(ToJson::sendStateRemoteControlled(mapping, in));
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
        cliente->sendMessage(ToJson::sendJoystickPosition(0.0f, 0.0f));
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
    fila = mapa.height() - 1 - fila;
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
    if (json["num_frame"].toInt() == 0 && receivedFrames != 0)
        receivedFrames = 0;

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
        if (!image.loadFromData(imageBuffer, "PNG")) // Verificar si la imagen se carga correctamente
        {
            qWarning() << "Error: Unable to load image from imageBuffer";
            return;
        }
        qDebug() << "Image successfully loaded. Size:" << image.size();

        // Modificar el mapa
        QString image_str;
        if (finalPosition.active)
        {
            image_str = updateMapPaintPoint(image, finalPosition.x_pixel, finalPosition.y_pixel, finalPosition.yaw);
            finalPosition.active = false;
        }
        if (image_str.isEmpty())
        {
            qWarning() << "Error updating the map";
            return;
        }
        setImageSource(image_str);
        imageBuffer.clear();
        totalSize = 0;
        receivedFrames = 0;
        totalFrames = 0;
    }
}

void StringHandler::getImageMapPath(const QJsonObject &json)
{
    QByteArray data = QByteArray::fromBase64(json["data"].toString().toUtf8());
    totalSize = json["total_size"].toInt();
    totalFrames = json["total_frame"].toInt();
    if (json["num_frame"].toInt() == 0 && receivedFrames != 0)
        receivedFrames = 0;

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
        if (!image.loadFromData(imageBuffer, "PNG")) // Verificar si la imagen se carga correctamente
        {
            qWarning() << "Error: Unable to load image from imageBuffer";
            return;
        }
        qDebug() << "Image successfully loaded. Size:" << image.size();
        QString imageSource;
        {
            if (image.isNull())
            {
                qWarning("Error al cargar el image");
                return;
            }
            if (image.format() != QImage::Format_ARGB32)
            {
                image = image.convertToFormat(QImage::Format_ARGB32);
            }
            QBuffer buffer;
            buffer.open(QIODevice::WriteOnly);

            if (!image.save(&buffer, "PNG"))
            {
                qWarning("Error al guardar el mapa modificado como PNG");
            }
            else
            {
                qDebug() << "Mapa guardado";
            }
            imageSource = (buffer.data().toBase64());
        }
        mapInfo->setImgSource(imageSource);
        imageBuffer.clear();
        totalSize = 0;
        receivedFrames = 0;
        totalFrames = 0;
    }
}


void StringHandler::setImageSource(const QString &source)
{
    if (source.isEmpty())
    {
        m_imageSource = "";
    }
    else
    {
        m_imageSource = "data:image/png;base64," + source;
    }
    emit imageSourceChanged();
}

void StringHandler::getRobotPositionPixel(const QJsonObject &json)
{
    finalPosition.x_pixel = json["x"].toInt();
    finalPosition.y_pixel = json["y"].toInt();
    finalPosition.yaw = json["yaw"].toDouble();
    finalPosition.active = true;
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
            QByteArray imageData;
            QBuffer buffer(&imageData);
            buffer.open(QIODevice::WriteOnly);
            image.save(&buffer, "PGM"); // Guarda la imagen en formato PGM en memoria

            m_imageSource = "data:image/pgm;base64," + imageData.toBase64();
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

bool StringHandler::mapping() const
{
    return m_mapping;
}

void StringHandler::setMapping(bool newMapping)
{
    if (m_mapping == newMapping)
        return;
    m_mapping = newMapping;
    emit mappingChanged();
}

bool StringHandler::saveMap() const
{
    return m_saveMap;
}

void StringHandler::setSaveMap(bool newSaveMap)
{
    if (m_saveMap == newSaveMap)
        return;
    m_saveMap = newSaveMap;
    emit saveMapChanged();
}

int StringHandler::typeSaveMap() const
{
    return m_typeSaveMap;
}

void StringHandler::setTypeSaveMap(int newTypeSaveMap)
{
    if (m_typeSaveMap == newTypeSaveMap)
        return;
    m_typeSaveMap = newTypeSaveMap;
    emit typeSaveMapChanged();
}

QString StringHandler::nameMap() const
{
    return m_nameMap;
}

void StringHandler::setNameMap(const QString &newNameMap)
{
    // void Cliente::sendMessage(const QJsonDocument &json)
    if (newNameMap != "")
    {
        if (m_nameMap == newNameMap)
        {
            cliente->sendMessage(ToJson::sendSaveMap(newNameMap, 1));
            return;
        }
        cliente->sendMessage(ToJson::sendSaveMap(newNameMap, 1)); // Si se repite en algun futuro dar un error cliente->sendMessage(sendSaveMap(newNameMap, 0));
    }
    m_nameMap = newNameMap;
    emit nameMapChanged();
}

QStringListModel *StringHandler::model() const
{
    return m_model;
}

void StringHandler::loadData(const std::vector<std::string> &data) {
    QStringList list;
    for (const std::string &str : data) {
        qDebug() << "Loading: " << QString::fromStdString(str);
        list.append(QString::fromStdString(str));
    }

    m_model->setStringList(list);
    emit modelChanged();  // Notifica a QML que los datos han cambiado
}



void StringHandler::requestMapName()
{
    cliente->sendMessage(ToJson::sendRequestMapName());
}
