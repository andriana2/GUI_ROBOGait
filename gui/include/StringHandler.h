#ifndef STRINGHANDLER_H
#define STRINGHANDLER_H

#include <QCoreApplication>
#include <QPainter>
#include <QBrush>
#include <QPen>

#include <QObject>
#include <QDebug>
#include <QString>
// #include <QImage>
// #include <string>
// #include "utils.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileInfo>

#include <QTimer>

#include "cliente.h"
#include "include/utils.h"

class Cliente;

class StringHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged)
    Q_PROPERTY(bool mapping READ mapping WRITE setMapping NOTIFY mappingChanged FINAL)

public:
    explicit StringHandler(QObject *parent = nullptr);
    Q_INVOKABLE bool isInSameNetwork(const QString &ip1, const std::string& subnetMask = "255.255.255.0");
    Q_INVOKABLE void setImage(const QByteArray &data);
    Q_INVOKABLE QString getImageSource(); // QUITAR MIRAR SI FUNCIONA
    Q_INVOKABLE void sendStateRemoteControlledHandler(bool mapping, bool in);

    void setClient(Cliente *cli);

    // msg send
    Q_INVOKABLE void setCurrentMove(const QString &lineal,const QString & angular);
    void setImageMap(const QByteArray &data);

    // msg recived
    void getImageMapSlam(const QJsonObject &json);
    void getRobotPositionPixel(const QJsonObject &json);
    Q_INVOKABLE void setImageSource(const QString &source);

    //edit image
    QString updateMapPaintPoint(QImage &mapa, int columna, int fila, float yaw);

    QString imageSource() const;

    bool mapping() const;
    void setmapping(bool newMapping);

signals:

    void imageReceived(const QString &image);

    void imageSourceChanged();

    void mappingChanged();

private:
    bool moveStop = 0;
    bool SLAM_ON = 1;
    Cliente *cliente;
    float currentAngular;
    float currentLineal;

    QTimer *periodicTimer;

    QString m_imageSource;
    QByteArray imageBuffer;
    size_t totalSize = 0;
    size_t receivedFrames = 1;
    size_t totalFrames = 0;

    struct FinalPosition finalPosition;
    bool m_mapping;
};

#endif // STRINGHANDLER_H
