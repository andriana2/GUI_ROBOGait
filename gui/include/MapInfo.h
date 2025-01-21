#ifndef MAPINFO_H
#define MAPINFO_H

#include <QCoreApplication>
#include <QPainter>
#include <QBrush>
#include <QPen>

#include <QObject>
#include <QDebug>
#include <QString>
#include <QStringListModel>
// #include <QImage>
// #include <string>
// #include "utils.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileInfo>

#include <QTimer>

#include "cliente.h"
#include "utils.h"

class Cliente;

class MapInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mapName READ mapName WRITE setMapName NOTIFY mapNameChanged FINAL)
    Q_PROPERTY(float orientation READ orientation WRITE setOrientation NOTIFY orientationChanged FINAL)
    Q_PROPERTY(Pixel originalPosition READ originalPosition NOTIFY originalPositionChanged FINAL)
    Q_PROPERTY(Pixel positionScreen READ positionScreen NOTIFY positionScreenChanged FINAL)

    Q_PROPERTY(Pixel imageSize READ imageSize NOTIFY imageSizeChanged FINAL)
    Q_PROPERTY(Pixel screenSize READ screenSize NOTIFY screenSizeChanged FINAL)
    Q_PROPERTY(QList<Pixel> pixels READ pixels NOTIFY pixelsChanged FINAL)
    Q_PROPERTY(QString imgSource READ imgSource WRITE setImgSource NOTIFY imgSourceChanged FINAL)

    Q_PROPERTY(float finalPathOrientation READ finalPathOrientation WRITE setFinalPathOrientation NOTIFY finalPathOrientationChanged FINAL)
    Q_PROPERTY(Pixel finalPathPosition READ finalPathPosition NOTIFY finalPathPositionChanged FINAL)



public:
    explicit MapInfo(QObject *parent = nullptr);

    // Q_INVOKABLE QString getInfoImageSource();
    // Q_INVOKABLE QString getInfoImageMapName();
    // Q_INVOKABLE float getInfoImageOrientation();
    // void setInfoImageSource(const QString &source);
    // void setInfoImagePixel(const Pixel &pixel);
    // void setInfoImageMapName(const QString &mapName);
    // void setInfoImageOrientation(float orientation);
    // Q_INVOKABLE void addPixelToInfoImage(int x, int y, bool paint_path);
    // Q_INVOKABLE void setPixelScreen(int x, int y);
    // Q_INVOKABLE void clearInfoImage();
    // Q_INVOKABLE void addInfoImageOriginal(int x, int y);


    void setClient(Cliente *cli);

    QString mapName() const;
    void setMapName(const QString &newMapName);

    float orientation() const;
    void setOrientation(float newOrientation);

    Pixel originalPosition() const;
    Q_INVOKABLE void setOriginalPosition(const int &x, const int &y);

    Pixel positionScreen() const;
    Q_INVOKABLE void setPositionScreen(const int &x, const int &y);

    Pixel imageSize() const;
    Q_INVOKABLE void setImageSize(const int &width, const int &height);

    Pixel screenSize() const;
    Q_INVOKABLE void setScreenSize(const int &width, const int &height);

    QList<Pixel> pixels() const;
    Q_INVOKABLE void addInfoImageOriginal(const int &x, const int &y);

    QString imgSource() const;
    Q_INVOKABLE void setImgSource(const QString &newImgSource);

    float finalPathOrientation() const;
    Q_INVOKABLE void setFinalPathOrientation(float newFinalPathOrientation);

    Pixel finalPathPosition() const;
    Q_INVOKABLE void setFinalPathPosition(const int &x, const int &y);

    Q_INVOKABLE void clearInfoImage();

signals:
    void mapNameChanged();
    void orientationChanged();
    void originalPositionChanged();
    void positionScreenChanged();
    void imageSizeChanged();
    void screenSizeChanged();
    void pixelsChanged();
    void imgSourceChanged();
    void finalPathOrientationChanged();
    void finalPathPositionChanged();

private:
    Cliente *cliente;

    QString m_mapName; // nombre del mapa
    float m_orientation; // orietacion del robot en la posicion inicial
    Pixel m_originalPosition; //posicion q tendrias en la imagen
    Pixel m_positionScreen;  // posicion robot de la pantalla orignal
    Pixel m_imageSize; // pixeles de la imagen real
    Pixel m_screenSize; // pixeles de la pantalla relacionada con la imagen
    QList<Pixel> m_pixels; // lista de pixeles en la trayectoria dibujada
    QString m_imgSource; // source que se pone de la image
    float m_finalPathOrientation; // radianes de la posicion final del robot
    Pixel m_finalPathPosition; // si lo haces como punto en la posicion final.
    //Valores de la posicion en funcion del mapa real pero con los datos del mapa screen
    // Es decir inserte la posicion del screen y se guardara la final

};

#endif // MAPINFO_H
