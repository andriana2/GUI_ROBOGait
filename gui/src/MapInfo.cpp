#include "../include/MapInfo.h"
#include "include/ToJson.h"
#include <qjsonarray.h>

MapInfo::MapInfo(QObject *parent)
{
    periodicTimerMapInfo = new QTimer(this);
    clearInfoImage();
    connect(periodicTimerMapInfo, &QTimer::timeout, this, [this]()
            {
                static int i = 0;
                if (m_checkInitInitialPose && i == 20) {
                    cliente->sendMessage(ToJson::sendRequestRobotPosition(mapName()));
                    i = 0;
                }
                else
                {
                    if (i == 20)
                        i = 0;
                }
                i++; });
}

void MapInfo::setClient(Cliente *cli)
{
    if (cliente == cli)
        return;
    cliente = cli;
}
void MapInfo::setStringHandler(StringHandler *sh)
{
    if (stringHandler == sh)
        return;
    stringHandler = sh;
}

QString MapInfo::mapName() const
{
    return m_mapName;
}

void MapInfo::setMapName(const QString &newMapName)
{
    if (m_mapName == newMapName)
        return;
    clearInfoImage();
    cliente->sendMessage(ToJson::sendRequestMap(newMapName));
    m_mapName = newMapName;
    emit mapNameChanged();
}

float MapInfo::orientation() const
{
    return m_orientation;
}

void MapInfo::setOrientation(float newOrientation)
{
    if (qFuzzyCompare(m_orientation, newOrientation))
        return;
    m_orientation = newOrientation;
    emit orientationChanged();
}

Pixel MapInfo::originalPosition() const
{
    return m_originalPosition;
}

void MapInfo::setOriginalPosition(const int &x, const int &y)
{
    int x_original = std::round((static_cast<double>(x) * m_imageSize.x) / m_screenSize.x);
    int y_original = std::round((static_cast<double>(y) * m_imageSize.y) / m_screenSize.y);

    if (m_originalPosition == Pixel{x_original, y_original})
        return;
    m_originalPosition = Pixel{x_original, y_original};
    emit originalPositionChanged();
}

Pixel MapInfo::positionScreen() const
{
    return m_positionScreen;
}

void MapInfo::setPositionScreen(const int &x, const int &y)
{
    if (m_positionScreen == Pixel{x, y})
        return;
    m_positionScreen = Pixel{x, y};
    setOriginalPosition(x, y);
    emit positionScreenChanged();
}

Pixel MapInfo::imageSize() const
{
    return m_imageSize;
}

void MapInfo::setImageSize(const int &width, const int &height)
{
    if (m_imageSize == Pixel{width, height})
        return;
    m_imageSize = Pixel{width, height};
    emit imageSizeChanged();
}

Pixel MapInfo::screenSize() const
{
    return m_screenSize;
}

void MapInfo::setScreenSize(const int &width, const int &height)
{
    if (m_screenSize == Pixel{width, height})
        return;
    m_screenSize = Pixel{width, height};
    emit screenSizeChanged();
}

QList<Pixel> MapInfo::pixels() const
{
    return m_pixels;
}

void MapInfo::addInfoImageOriginal(const int &x, const int &y)
{
    int x_original = std::round((static_cast<double>(x) * m_imageSize.x) / m_screenSize.x);
    int y_original = std::round((static_cast<double>(y) * m_imageSize.y) / m_screenSize.y);

    m_pixels.append(Pixel{x_original, y_original});
    // qDebug() << "x_original  " << x_original << " y_original  " << y_original;

    // emit pixelsChanged();
}

void MapInfo::clearListPixels()
{
    m_pixels.clear();
}

QString MapInfo::imgSource() const
{
    return m_imgSource;
}

void MapInfo::setImgSource(const QString &newImgSource)
{
    if (newImgSource.isEmpty())
    {
        m_imgSource = "";
    }
    else
    {
        m_imgSource = "data:image/png;base64," + newImgSource;
    }
    emit imgSourceChanged();
}

float MapInfo::finalPathOrientation() const
{
    return m_finalPathOrientation;
}

void MapInfo::setFinalPathOrientation(float newFinalPathOrientation)
{
    if (qFuzzyCompare(m_finalPathOrientation, newFinalPathOrientation))
        return;
    m_finalPathOrientation = newFinalPathOrientation;
    emit finalPathOrientationChanged();
}

Pixel MapInfo::finalPathPosition() const
{
    return m_finalPathPosition;
}

void MapInfo::setFinalPathPosition(const int &x, const int &y)
{
    int x_original = std::round((static_cast<double>(x) * m_imageSize.x) / m_screenSize.x);
    int y_original = std::round((static_cast<double>(y) * m_imageSize.y) / m_screenSize.y);
    // qDebug() << "++++++++++++++"<< "x_original  " <<x_original <<" y_original  " << y_original ;
    // qDebug() << "--------------" << "x_original  " <<m_finalPathPosition.x <<" y_original  " << m_finalPathPosition.y ;

    if (m_finalPathPosition == Pixel{x_original, y_original})
        return;
    m_finalPathPosition = Pixel{x_original, y_original};
    // qDebug() << "x_original  " <<m_finalPathPosition.x <<" y_original  " << m_finalPathPosition.y ;
    emit finalPathPositionChanged();
}

void MapInfo::clearInfoImage()
{
    repeated_delegate_list_view = 0;
    
    m_mapName = "";
    m_orientation = 0.0f;
    m_originalPosition = Pixel();
    m_positionScreen = Pixel();
    m_imageSize = Pixel();
    m_screenSize = Pixel();
    m_pixels.clear();
    m_imgSource = "";
    m_finalPathOrientation = 0.0f; // radianes de la posicion final del robot
    m_finalPathPosition = Pixel();
    
    m_finalScreenPosition = Pixel();
    m_resolution = 0.0;
    m_checkInitInitialPose = false;
    
    m_trajectoryGoalPose.clear();
    if (periodicTimerMapInfo->isActive())
    {
        periodicTimerMapInfo->stop();
    }
}

void MapInfo::clearNextPath()
{
    setFinalPathOrientation(0.0f);

    m_pixels.clear();
    emit pixelsChanged();

    m_finalPathPosition = Pixel(0, 0);
    emit finalPathPositionChanged();

    m_trajectoryGoalPose.clear();
    emit trajectoryGoalPoseChanged();

    repeated_delegate_list_view = 0;

    if (periodicTimerMapInfo->isActive())
    {
        periodicTimerMapInfo->stop();
    }
    qDebug() << "Final Path Orientation:" << m_finalPathOrientation;
    qDebug() << "Pixels count:" << m_pixels.count();
    qDebug() << "Final Path Position:" << m_finalPathPosition.x << m_finalPathPosition.y;
    qDebug() << "Trajectory Goal Pose count:" << m_trajectoryGoalPose.count();
    qDebug() << "Repeated Delegate List View:" << repeated_delegate_list_view;
}

bool MapInfo::checkPixelBlack(const int &x, const int &y)
{
    QString base64Data = m_imgSource;
    if (m_imgSource.startsWith("data:image/png;base64,"))
    {
        base64Data = m_imgSource.mid(QString("data:image/png;base64,").length());
    }

    // Decodificar la imagen de Base64
    QByteArray imageData = QByteArray::fromBase64(base64Data.toUtf8());
    QImage image;
    if (!image.loadFromData(imageData))
    {
        qWarning() << "No se pudo cargar la imagen de los datos base64.";
        return false;
    }

    // Verificar si las coordenadas están dentro del rango
    if (x < 0 || x >= m_imageSize.y || y < 0 || y >= m_imageSize.y)
    {
        qDebug() << "Las coordenadas están fuera del rango de la imagen.";
        return false;
    }

    // Obtener el color del píxel
    QColor pixelColor = image.pixelColor(x, y);

    int intensity = pixelColor.red(); // O green() o blue(), todos serán iguales
    // qDebug() << "Intensidad " << intensity;
    return intensity == 0;
}

Pixel MapInfo::finalScreenPosition() const
{
    return m_finalScreenPosition;
}

void MapInfo::setFinalScreenPosition(const int &x, const int &y)
{
    if (m_finalScreenPosition == Pixel{x, y})
        return;
    m_finalScreenPosition = Pixel{x, y};
    setFinalPathPosition(x, y);
    emit finalScreenPositionChanged();
}

QVariantList MapInfo::getPixels()
{
    if (m_pixels.empty())
        return QVariantList();
    m_pixels.prepend(m_originalPosition);
    QList<Pixel> pixelList = filtrarPuntosCercanos(rdp(m_pixels, 1), 5);
    // QList<Pixel> pixelList = filtrarPuntosCercanos(suavizarTrayectoria(filtrarPuntosCercanos(m_pixels, 6), 3), 3);
    m_pixels = pixelList;
    QVariantList points;

    for (const Pixel &p : pixelList)
    {
        int x_screen = std::round((static_cast<double>(p.x) * m_screenSize.x) / m_imageSize.x);
        int y_screen = std::round((static_cast<double>(p.y) * m_screenSize.y) / m_imageSize.y);
        QVariantMap point;
        point["x"] = x_screen;
        point["y"] = y_screen;
        points.append(point);
    }
    emit pixelsChanged();
    return points;
}

QList<Pixel> MapInfo::filtrarPuntosCercanos(const QList<Pixel> &puntos, int distancia)
{
    if (puntos.empty())
        return {};

    QList<Pixel> puntosOrdenados = puntos;
    QList<Pixel> filtrados;
    // filtrados.append(m_originalPosition);
    filtrados.push_back(puntosOrdenados[0]);

    for (size_t i = 1; i < puntosOrdenados.size(); ++i)
    {
        const Pixel &ultimo = filtrados.back();
        const Pixel &actual = puntosOrdenados[i];

        // Si la diferencia en x e y es mayor a la distancia, se agrega el punto
        if (std::abs(actual.x - ultimo.x) >= distancia || std::abs(actual.y - ultimo.y) >= distancia)
        {
            filtrados.push_back(actual);
        }
    }
    filtrados.push_back(puntos.back());

    return filtrados;
}

double MapInfo::puntoLineaDist(const Pixel &p, const Pixel &a, const Pixel &b)
{
    double ux = b.x - a.x, uy = b.y - a.y;
    double vx = p.x - a.x, vy = p.y - a.y;
    double area = std::abs(ux * vy - uy * vx);
    double len = std::hypot(ux, uy);
    return area / len;
}

// Algoritmo RDP con QList<Pixel>
QList<Pixel> MapInfo::rdp(const QList<Pixel> &pts, double eps)
{
    if (pts.size() < 3)
        return pts;

    int idx = -1;
    double dmax = 0.0;

    for (int i = 1; i < pts.size() - 1; ++i)
    {
        double d = puntoLineaDist(pts[i], pts.first(), pts.last());
        if (d > dmax)
        {
            idx = i;
            dmax = d;
        }
    }

    if (dmax < eps || idx == -1)
    {
        return {pts.first(), pts.last()};
    }

    // Dividir en dos sublistas
    QList<Pixel> leftInput, rightInput;
    for (int i = 0; i <= idx; ++i)
        leftInput.append(pts[i]);
    for (int i = idx; i < pts.size(); ++i)
        rightInput.append(pts[i]);

    // Recursión
    QList<Pixel> left = rdp(leftInput, eps);
    QList<Pixel> right = rdp(rightInput, eps);

    // Fusionar quitando duplicado
    left.removeLast(); // evita duplicar el punto en común
    left.append(right);

    return left;
}

double MapInfo::distancia(const Pixel &p1, const Pixel &p2)
{
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Función para crear un punto intermedio a una distancia específica
Pixel MapInfo::puntoIntermedio(const Pixel &p1, const Pixel &p2, double distanciaObjetivo)
{
    double distTotal = distancia(p1, p2);
    if (distTotal < 1e-6)
        return p1; // Evitar divisiones por cero
    double t = distanciaObjetivo / distTotal;
    return {static_cast<int>(p1.x + t * (p2.x - p1.x)), static_cast<int>(p1.y + t * (p2.y - p1.y))};
}

// Función para suavizar giros de 90° eliminando la esquina y agregando puntos intermedios
QList<Pixel> MapInfo::suavizarTrayectoria(const QList<Pixel> &puntos, double distanciaSuavizado)
{
    if (puntos.size() < 3)
        return puntos; // No hay giros que suavizar con menos de 3 puntos

    QList<Pixel> resultado;
    resultado.push_back(puntos[0]); // Primer punto siempre se mantiene

    for (size_t i = 1; i < puntos.size() - 1; ++i)
    {
        Pixel A = puntos[i - 1];
        Pixel B = puntos[i];
        Pixel C = puntos[i + 1];

        // Crear puntos intermedios a distancia "distanciaSuavizado"
        Pixel P1 = puntoIntermedio(A, B, distanciaSuavizado);
        Pixel P2 = puntoIntermedio(C, B, distanciaSuavizado);

        // Agregar los puntos intermedios y saltar B (eliminamos la esquina)
        resultado.push_back(P1);
        resultado.push_back(P2);
    }

    resultado.push_back(puntos.back()); // Último punto siempre se mantiene
    return resultado;
}

bool MapInfo::isBlack(const QImage &image, const Pixel &point, int radius)
{
    for (int dx = -radius; dx <= radius; ++dx)
    {
        for (int dy = -radius; dy <= radius; ++dy)
        {
            int x = point.x + dx;
            int y = point.y + dy;

            // Validar que no esté fuera de los bordes de la imagen
            if (x >= 0 && x < m_imageSize.x && y >= 0 && y < m_imageSize.y)
            {
                QColor color = image.pixelColor(x, y);
                int intensity = color.red();

                if (intensity == 0) // negro
                    return true;
            }
        }
    }
    return false; // Ningún píxel negro en el área
}

std::vector<Pixel> MapInfo::getLinePixels(Pixel p1, Pixel p2)
{
    std::vector<Pixel> points;
    int dx = std::abs(p2.x - p1.x), sx = p1.x < p2.x ? 1 : -1;
    int dy = -std::abs(p2.y - p1.y), sy = p1.y < p2.y ? 1 : -1;
    int err = dx + dy, e2;

    while (true)
    {
        points.push_back(p1);
        if (p1.x == p2.x && p1.y == p2.y)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            p1.x += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            p1.y += sy;
        }
    }
    return points;
}

bool MapInfo::linePassesThroughBlack(const QImage &image, Pixel p1, Pixel p2)
{
    std::vector<Pixel> pixels = getLinePixels(p1, p2);
    for (const Pixel &p : pixels)
    {
        if (isBlack(image, p, 3))
        {
            return true;
        }
    }
    return false;
}

bool MapInfo::checkPathBlack()
{
    QList<Pixel> trajectory = m_pixels;

    if (m_pixels.empty())
    {
        qWarning() << "No hay puntos en la trayectoria.";
        return false;
    }
    QString base64Data = m_imgSource;
    if (base64Data.startsWith("data:image/png;base64,"))
    {
        base64Data = base64Data.mid(QString("data:image/png;base64,").length());
    }

    QByteArray imageData = QByteArray::fromBase64(base64Data.toUtf8());
    QImage image;
    if (!image.loadFromData(imageData))
    {
        qWarning() << "No se pudo cargar la imagen de los datos base64.";
        return false;
    }

    bool foundBlack = false;

    for (const Pixel &p : trajectory)
    {
        if (isBlack(image, p, 3))
        {
            foundBlack = true;
        }
    }

    for (size_t i = 0; i < trajectory.size() - 1; i++)
    {
        if (linePassesThroughBlack(image, trajectory[i], trajectory[i + 1]))
        {
            foundBlack = true;
        }
    }

    return foundBlack;
}

void MapInfo::initBringUp()
{
    cliente->sendMessage(ToJson::initBringUp(m_mapName));
}

void MapInfo::sendInitialPose()
{
    cliente->sendMessage(ToJson::sendInitialPose(m_mapName, m_originalPosition.x, m_originalPosition.y, m_orientation, m_imageSize.y));

    // if (!periodicTimerMapInfo->isActive())
    // {
    //     periodicTimerMapInfo->start(200);
    // }
    setCheckInitInitialPose(true);
}

void MapInfo::sendAllInformationPose()
{
    cliente->sendMessage(ToJson::sendAllInformationPose(m_mapName, m_originalPosition.x, m_originalPosition.y, m_orientation, m_finalPathPosition.x, m_finalPathPosition.y, m_finalPathOrientation, m_imageSize.y));
}

void MapInfo::sendGoalPose()
{
    // send periodically the position of the robot (tf_service)
    if (!periodicTimerMapInfo->isActive())
    {
        periodicTimerMapInfo->start(200);
    }
    cliente->sendMessage(ToJson::sendGoalPose(m_mapName, m_finalPathPosition.x, m_finalPathPosition.y, m_finalPathOrientation, m_imageSize.y));
}

void MapInfo::sendWaypointFollower()
{
    // send periodically the position of the robot (tf_service)
    if (!periodicTimerMapInfo->isActive())
    {
        periodicTimerMapInfo->start(200);
    }
    cliente->sendMessage(ToJson::sendWaypointFollower(m_mapName, m_pixels, m_imageSize.y));
}

void MapInfo::sendStopProcesses()
{
    if (checkInitInitialPose() == true)
        setCheckInitInitialPose(false);

    cliente->sendMessage(ToJson::stopProcesses());
}

float MapInfo::resolution() const
{
    return m_resolution;
}

void MapInfo::setResolution(float newResolution)
{
    if (qFuzzyCompare(m_resolution, newResolution))
        return;
    m_resolution = newResolution;
    emit resolutionChanged();
}

bool MapInfo::checkInitInitialPose() const
{
    return m_checkInitInitialPose;
}

void MapInfo::setCheckInitInitialPose(bool newCheckInitInitialPose)
{
    if (m_checkInitInitialPose == newCheckInitInitialPose)
        return;
    m_checkInitInitialPose = newCheckInitInitialPose;
    emit checkInitInitialPoseChanged();
}

void MapInfo::getRobotPositionInitialpose(const QJsonObject &json)
{
    setOrientation(json["yaw"].toDouble());

    int x_screen = std::round((static_cast<double>(json["x"].toInt()) * m_screenSize.x) / m_imageSize.x);
    int y_screen = screenSize().y - std::round((static_cast<double>(json["y"].toInt()) * m_screenSize.y) / m_imageSize.y);
    setPositionScreen(x_screen, y_screen);
}

QList<Pixel> MapInfo::trajectoryGoalPose() const
{
    return m_trajectoryGoalPose;
}

void MapInfo::setTrajectoryGoalPose(const QList<Pixel> &trajectory)
{
    m_trajectoryGoalPose = trajectory;
    emit trajectoryGoalPoseChanged();
}

void MapInfo::clearTrajectoryGoalPose()
{
    m_trajectoryGoalPose.clear();
}

void MapInfo::parseJsonToQList(const QJsonObject &jsonObj)
{
    if (!jsonObj.contains("points") || !jsonObj["points"].isArray())
    {
        qWarning() << "No se encontró el array 'points' en el JSON";
        return;
    }

    QJsonArray jsonArray = jsonObj["points"].toArray();
    QList<Pixel> pointsList;

    // Iterar sobre el array y convertir cada objeto en un QPointF
    for (const QJsonValue &value : jsonArray)
    {
        if (value.isObject())
        {
            QJsonObject pointObj = value.toObject();
            if (pointObj.contains("x") && pointObj.contains("y"))
            {
                double x = pointObj["x"].toDouble();
                double y = m_imageSize.y - pointObj["y"].toDouble();

                int x_original = std::round((x * m_screenSize.x) / m_imageSize.x);
                int y_original = std::round((y * m_screenSize.y) / m_imageSize.y);

                pointsList.append(Pixel{x_original, y_original});

                // Imprimir valores en consola
                // qDebug().nospace() << "x: " << x
                //                    << ", y: " << y
                //                    << " | m_imageSize: (" << m_imageSize.x << ", " << m_imageSize.y << ")"
                //                    << " | m_screenSize: (" << m_screenSize.x << ", " << m_screenSize.y << ")"
                //                    << " | x_original: " << x * m_imageSize.x
                //                    << ", y_original: " << y * m_imageSize.y;
            }
        }
    }

    // Imprimir todos los puntos convertidos
    qDebug() << "Lista de puntos convertidos:";
    QList<Pixel> trayectory_temp = filtrarPuntosCercanos(rdp(pointsList, 3), 30);
    qDebug() << "^^^^^^^^^^^^ NUM vector despues filtro:" << trayectory_temp.size() << "  NUM vector antes filtro:" << pointsList.size();
    setTrajectoryGoalPose(trayectory_temp);
    for (const Pixel &p : trayectory_temp)
    {
        qDebug().nospace() << "Pixel -> x: " << p.x << ", y: " << p.y;
    }
    // filtrarPuntosCercanos(rdp(pointsList, 1), 5);
}
