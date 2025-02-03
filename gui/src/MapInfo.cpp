#include "../include/MapInfo.h"
#include "include/ToJson.h"

MapInfo::MapInfo(QObject *parent) { clearInfoImage(); }

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
    // qDebug() << "+++Map name: "<< m_mapName << " position x: " << x_original << " position y: " << y_original;
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
    qDebug() << "x_original  " << x_original << " y_original  " << y_original;

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
    repeated_delegate_list_view = 0;
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

    QList<Pixel> pixelListSubsampling = subsampling(m_pixels, 10);
    QList<Pixel> pixelList = smoothBezierPath(pixelListSubsampling);
    m_pixels = pixelList;
    QVariantList points;

    for (const Pixel &p : pixelList)
    {
        int x_original = std::round((static_cast<double>(p.x) * m_screenSize.x) / m_imageSize.x);
        int y_original = std::round((static_cast<double>(p.y) * m_screenSize.y) / m_imageSize.y);
        QVariantMap point;
        point["x"] = x_original;
        point["y"] = y_original;
        points.append(point);
    }
    emit pixelsChanged();
    return points;
}

Pixel MapInfo::cubicBezier(float t, const Pixel &p0, const Pixel &p1, const Pixel &p2, const Pixel &p3) const
{
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    Pixel pixel;
    pixel.x = uuu * p0.x + 3 * uu * t * p1.x + 3 * u * tt * p2.x + ttt * p3.x;
    pixel.y = uuu * p0.y + 3 * uu * t * p1.y + 3 * u * tt * p2.y + ttt * p3.y;

    return pixel;
}

QList<Pixel> MapInfo::smoothBezierPath(const QList<Pixel> &pixel) const
{
    QList<Pixel> result;
    if (pixel.size() < 4)
        return pixel; // Si hay menos de 4 puntos, devolver la lista original

    for (int i = 0; i < pixel.size() - 3; i += 3)
    {
        for (float t = 0; t <= 1; t += 0.05)
        {
            result.append(cubicBezier(t, pixel[i], pixel[i + 1], pixel[i + 2], pixel[i + 3]));
        }
    }

    // Asegurar que el último punto siempre se incluya
    if (result.last().x != pixel.last().x || result.last().y != pixel.last().y)
    {
        result.append(pixel.last());
    }

    return result;
}

QList<Pixel> MapInfo::subsampling(const QList<Pixel> &pixel, double umbral) const
{
    QList<Pixel> result;
    if (pixel.isEmpty())
        return result;

    result.append(m_originalPosition);
    result.append(pixel.first()); // Agregar el primer punto

    for (int i = 1; i < pixel.size(); ++i)
    {
        double distancia = std::hypot(pixel[i].x - result.last().x, pixel[i].y - result.last().y);
        if (distancia > umbral)
        {
            result.append(pixel[i]);
        }
    }

    // Asegurar que el último punto siempre se incluya
    if (result.last().x != pixel.last().x || result.last().y != pixel.last().y)
    {
        result.append(pixel.last());
    }
    return result;
}

bool MapInfo::isBlack(const QImage &image, cv::Point point)
{
    if (point.x >= 0 && point.x < m_imageSize.x && point.y >= 0 && point.y < m_imageSize.y)
    {
        QColor pixelColor = image.pixelColor(point.x, point.y);

        int intensity = pixelColor.red(); // Black in a binary image is 0
        return intensity == 0;
    }
    return false;
}

std::vector<cv::Point> MapInfo::getLinePixels(cv::Point p1, cv::Point p2)
{
    std::vector<cv::Point> points;
    cv::LineIterator it(cv::Mat(), p1, p2, 8);
    for (int i = 0; i < it.count; i++, ++it)
    {
        points.push_back(it.pos());
    }
    return points;
}

bool MapInfo::linePassesThroughBlack(const QImage &image, cv::Point p1, cv::Point p2)
{
    std::vector<cv::Point> pixels = getLinePixels(p1, p2);
    for (const cv::Point &p : pixels)
    {
        if (isBlack(image, p))
        {
            return true;
        }
    }
    return false;
}

cv::Mat MapInfo::base64ToMat(const QString &base64Data)
{
    // Remove Base64 prefix if present
    QString data = base64Data;
    if (data.startsWith("data:image/png;base64,"))
    {
        data = data.mid(QString("data:image/png;base64,").length());
    }

    // Decode Base64 to QByteArray
    QByteArray byteArray = QByteArray::fromBase64(data.toUtf8());

    // Convert QByteArray to cv::Mat using OpenCV
    std::vector<uchar> buffer(byteArray.begin(), byteArray.end());
    cv::Mat image = cv::imdecode(buffer, cv::IMREAD_COLOR);

    if (image.empty())
    {
        qDebug() << "Failed to decode Base64 image.";
    }
    else
    {
        qDebug() << "Image decoded successfully: " << image.cols << "x" << image.rows;
    }

    return image;
}

bool MapInfo::checkPathBlack()
{
    std::vector<cv::Point> trajectory;
    for (const Pixel &p : m_pixels)
    {
        trajectory.emplace_back(p.x, p.y);
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

    // Convertir base64 a cv::Mat
    // cv::Mat image = base64ToMat(base64Data);
    // if (image.empty())
    // {
    //     std::cerr << "Error loading the image" << std::endl;
    //     return false;
    // }

    // Convertir la imagen a escala de grises y binarizarla
    // cv::threshold(image, image, 128, 255, cv::THRESH_BINARY);

    bool foundBlack = false;

    for (const cv::Point &p : trajectory) {
        if (isBlack(image, p)) {
            std::cout << "Point (" << p.x << "," << p.y << ") is in a black area." << std::endl;

            // Dibujar un punto rojo en la imagen original
            cv::Mat imgColor = base64ToMat(base64Data); // Recargar imagen a color
            cv::circle(imgColor, p, 5, cv::Scalar(0, 0, 255), -1); // Rojo (BGR: 0,0,255)

            // Guardar la imagen con la marca
            cv::imwrite("/home/andri/Desktop/marked_image.png", imgColor);

            foundBlack = true;
            break; // Si solo queremos marcar el primer punto negro encontrado
        }
    }

    // Verificar si alguna línea pasa por un área negra
    for (size_t i = 0; i < trajectory.size() - 1; i++) {
        
        if (linePassesThroughBlack(image, trajectory[i], trajectory[i + 1])) {
            std::cout << "The line between (" << trajectory[i].x << "," << trajectory[i].y
                      << ") and (" << trajectory[i + 1].x << "," << trajectory[i + 1].y
                      << ") passes through a black area." << std::endl;
            
            // Dibujar un punto rojo en el centro de la línea
            cv::Mat imgColor = base64ToMat(base64Data); // Recargar imagen a color
            cv::Point midPoint = (trajectory[i] + trajectory[i + 1]) / 2;
            cv::circle(imgColor, midPoint, 5, cv::Scalar(0, 0, 255), -1);

            // Guardar la imagen con la marca
            cv::imwrite("/home/andri/Desktop/marked_image.png", imgColor);

            foundBlack = true;
            break;
        }
    }

    return foundBlack;
}

