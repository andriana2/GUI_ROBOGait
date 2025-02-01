#include "../include/MapInfo.h"
#include "include/ToJson.h"

MapInfo::MapInfo(QObject *parent){ clearInfoImage();}

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

    if (m_originalPosition == Pixel{x_original,y_original})
        return;
    m_originalPosition = Pixel{x_original,y_original};
    // qDebug() << "+++Map name: "<< m_mapName << " position x: " << x_original << " position y: " << y_original;
    emit originalPositionChanged();
}

Pixel MapInfo::positionScreen() const
{
    return m_positionScreen;
}

void MapInfo::setPositionScreen(const int &x, const int &y)
{
    if (m_positionScreen == Pixel{x,y})
        return;
    m_positionScreen = Pixel{x,y};
    setOriginalPosition(x,y);
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

    emit pixelsChanged();
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

    if (m_finalPathPosition == Pixel{x_original,y_original})
        return;
    m_finalPathPosition = Pixel{x_original,y_original};
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
    if (m_imgSource.startsWith("data:image/png;base64,")) {
        base64Data = m_imgSource.mid(QString("data:image/png;base64,").length());
    }

    // Decodificar la imagen de Base64
    QByteArray imageData = QByteArray::fromBase64(base64Data.toUtf8());
    QImage image;
    if (!image.loadFromData(imageData)) {
        qWarning() << "No se pudo cargar la imagen de los datos base64.";
        return false;
    }

    // Verificar si las coordenadas están dentro del rango
    if (x < 0 || x >= m_imageSize.y || y < 0 || y >= m_imageSize.y) {
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
    if (m_finalScreenPosition == Pixel{x,y})
        return;
    m_finalScreenPosition = Pixel{x,y};
    setFinalPathPosition(x,y);
    emit finalScreenPositionChanged();
}
