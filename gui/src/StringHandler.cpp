#include "../include/StringHandler.h"
#include "../include/utils.h"
#include "../include/ToJson.h"
#include <vector>
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
                    cliente->sendMessage(ToJson::sendJoystickPosition(m_angularVelocity, m_linealVelocity));
                    if (i == 10)
                        i = 0;
                }
                i++; });

    periodicTimerBattery = new QTimer(this);
    connect(periodicTimerBattery, &QTimer::timeout, this, [this]()
            {
                static int i = 0;
                if (i == 10)
                {
                    cliente->sendMessage(ToJson::sendRequestBattery());
                    i = 0;
                }
                if (i == 10)
                    i = 0;
                i++; });
}
void StringHandler::setClient(Cliente *cli) { cliente = cli; }

void StringHandler::setMapInfo(MapInfo *mapIn)
{
    mapInfo = mapIn;
}

void StringHandler::searchRobotIp()
{
    cliente->startSearchUdp();
}

void StringHandler::disconnectRobot()
{
    cliente->disconnectRobot();
}

QString StringHandler::getImageSource()
{
    // qDebug() << m_imageSource;
    return m_imageSource;
}

void StringHandler::startSLAM()
{
    setMapping(true);
    cliente->sendMessage(ToJson::sendStateRemoteControlled(true));
} 

void StringHandler::stopSLAM()
{
    setMapping(false);
    cliente->sendMessage(ToJson::sendStateRemoteControlled(false));
}
// void StringHandler::sendStateRemoteControlledHandler(bool mapping, bool in)
// {
//     cliente->sendMessage(ToJson::sendStateRemoteControlled(mapping, in));
// }

QString StringHandler::updateMapPaintPoint(QImage &mapa, int columna, int fila, float yaw)
{
    fila = mapa.height() - 1 - fila; // OOOOJJJJOOOO porque en qt el origen de coordenadas esta invertido
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
    if (json["data"].toString().isEmpty())
    {
        setImageSource("");
        return;
    }
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
    if (source.isEmpty() || source == "")
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

void StringHandler::loadData(const std::vector<std::string> &data)
{
    QStringList list;
    for (const std::string &str : data)
    {
        qDebug() << "Loading: " << QString::fromStdString(str);
        list.append(QString::fromStdString(str));
    }

    m_model->setStringList(list);
    emit modelChanged(); // Notifica a QML que los datos han cambiado
}

void StringHandler::requestMapName()
{
    cliente->sendMessage(ToJson::sendRequestMapName());
}

void StringHandler::menu_page(bool in)
{
    if (in)
    {
        if (!periodicTimerBattery->isActive())
        {
            periodicTimerBattery->start(20000);
        }
    }
    mapInfo->setCheckInitInitialPose(false); // OJOOOOOOOOOOOOOOOOOOOOOO
    cliente->sendMessage(ToJson::sendStateMenu(in));
}

void StringHandler::closeConnection()
{
    cliente->closeConnection();
}

QString StringHandler::strFindRobot() const
{
    return m_strFindRobot;
}

void StringHandler::setStrFindRobot(const QString &newStrFindRobot)
{
    if (m_strFindRobot == newStrFindRobot)
        return;
    m_strFindRobot = newStrFindRobot;
    qDebug() << m_strFindRobot;
    emit strFindRobotChanged();
}

bool StringHandler::errorConnection() const
{
    return m_errorConnection;
}

void StringHandler::setErrorConnection(bool newErrorConnection)
{
    if (m_errorConnection == newErrorConnection)
        return;
    m_errorConnection = newErrorConnection;
    emit errorConnectionChanged();
}

void StringHandler::stopTimerBattery()
{
    if (periodicTimerBattery->isActive())
    {
        periodicTimerBattery->stop();
    }
}

QString StringHandler::stateBottomBar() const
{
    return m_stateBottomBar;
}

void StringHandler::setStateBottomBar(const QString &newStateBottomBar)
{
    if (m_stateBottomBar == newStateBottomBar)
        return;
    if (newStateBottomBar == "MP_cbb" || newStateBottomBar == "nMP_cbb" || newStateBottomBar == "MnP_cbb" || newStateBottomBar == "nMnP_cbb" || newStateBottomBar == "nothing_cbb" || newStateBottomBar == "onlyBattery")
    {
        m_stateBottomBar = newStateBottomBar;
    }
    else
        return;
    emit stateBottomBarChanged();
}

void StringHandler::batteryLevel(const QJsonObject &json)
{
    const QJsonValue value = json.value("battery_level");

    if (!value.isDouble())
    {
        qWarning() << "Invalid or missing 'battery_level' in JSON.";
        return;
    }

    double batteryLevel = value.toDouble();
    qDebug() << batteryLevel << "batteryLevel++++++++++++++++++++++++++++++++++++++++++++++";
    if (batteryLevel == -1.0)
    {
        qDebug() << "Paso a -1";
        setBatteryPercentage(static_cast<int>(batteryLevel));
        return;
    }
    if (batteryLevel < 0.0 || batteryLevel > 100.0)
    {
        qWarning() << "Battery level out of expected range (0–100):" << batteryLevel;
        return;
    }

    setBatteryPercentage(static_cast<int>(batteryLevel));
}

int StringHandler::batteryPercentage() const
{
    return m_batteryPercentage;
}

void StringHandler::setBatteryPercentage(int newBatteryPercentage)
{
    if (m_batteryPercentage == newBatteryPercentage)
        return;
    m_batteryPercentage = newBatteryPercentage;
    emit batteryPercentageChanged();
}

void StringHandler::clear_all()
{
    moveStop = 0;
    SLAM_ON = 1;

    m_linealVelocity = 0.0;
    m_angularVelocity = 0.0;

    imageBuffer.clear();
    receivedFrames = 1;
    totalFrames = 0;
    totalSize = 0;
    finalPosition.x_pixel = 0;
    finalPosition.y_pixel = 0;
    finalPosition.yaw = 0;
    finalPosition.active = false;

    m_imageSource = "";
    m_mapping = false;
    m_saveMap = false;
    m_typeSaveMap = -1;
    m_nameMap = "";
    m_model->setStringList(QStringList());

    m_strFindRobot = "";
    m_errorConnection = false;
    m_stateBottomBar = "nMnP_cbb";
    m_batteryPercentage = -10;

    m_mapNameTest = "";
    m_patientName = "";
}

QString StringHandler::patientName() const
{
    return m_patientName;
}

void StringHandler::setPatientName(const QString &newPatientName)
{
    if (m_patientName == newPatientName)
        return;
    m_patientName = newPatientName;
    emit patientNameChanged();
}

QString StringHandler::mapNameTest() const
{
    return m_mapNameTest;
}

void StringHandler::setMapNameTest(const QString &newMapNameTest)
{
    if (m_mapNameTest == newMapNameTest)
        return;
    m_mapNameTest = newMapNameTest;
    emit mapNameTestChanged();
}
// void StringHandler::setStateBottomBar(const QString &newStateBottomBar)

void StringHandler::updateBottomBarState()
{
    QString state;

    // Determinar estado según si hay mapa (M) o no (nM), y paciente (P) o no (nP)
    if (!m_mapNameTest.isEmpty() && !m_patientName.isEmpty())
    {
        state = "MP_cbb";
    }
    else if (m_mapNameTest.isEmpty() && !m_patientName.isEmpty())
    {
        state = "nMP_cbb";
    }
    else if (!m_mapNameTest.isEmpty() && m_patientName.isEmpty())
    {
        state = "MnP_cbb";
    }
    else if (m_mapNameTest.isEmpty() && m_patientName.isEmpty())
    {
        state = "nMnP_cbb";
    }

    // Llamar a la función original con el estado generado
    setStateBottomBar(state);
}

void StringHandler::setCurrentVelocity(const float &newAngularVelocity, const float &newLinealVelocity)
{
    bool ok;
    bool moveStopLocal;

    // Convertir lineal a float y redondear
    float angular_f = std::round(newAngularVelocity * 10000.0f) / 10000.0f;
    float lineal_f = std::round(newLinealVelocity * 10000.0f) / 10000.0f;

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
        m_angularVelocity = 0.0;
        m_linealVelocity = 0.0;
        emit angularVelocityChanged();
        emit linealVelocityChanged();
    }
    else
    {
        // El robot está en movimiento: actualizar valores y activar el temporizador
        m_angularVelocity = angular_f;
        m_linealVelocity = lineal_f;

        if (!periodicTimer->isActive())
        {
            periodicTimer->start(200);
        }
        moveStop = false;
        emit angularVelocityChanged();
        emit linealVelocityChanged();
    }
}

float StringHandler::angularVelocity() const
{
    return m_angularVelocity;
}

float StringHandler::linealVelocity() const
{
    return m_linealVelocity;
}



int StringHandler::idExperiment() const
{
    return m_idExperiment;
}

void StringHandler::setIdExperiment(int newIdExperiment)
{
    if (m_idExperiment == newIdExperiment)
        return;
    m_idExperiment = newIdExperiment;
    emit idExperimentChanged();
}
