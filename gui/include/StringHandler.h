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
    Q_PROPERTY(QString imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged) //La imagen que se muestra (Teledirigido)
    Q_PROPERTY(bool mapping READ mapping WRITE setMapping NOTIFY mappingChanged FINAL)//Si estoy mapeando o solo moviendo con el joystick (Teledirigido)
    Q_PROPERTY(bool saveMap READ saveMap WRITE setSaveMap NOTIFY saveMapChanged FINAL)//Saber si se ha guaradado la imagen (Teledirigido)
    Q_PROPERTY(int typeSaveMap READ typeSaveMap WRITE setTypeSaveMap NOTIFY typeSaveMapChanged FINAL)//Tipo de mapa si se a guardado o no (Teledirigido)
    Q_PROPERTY(QString nameMap READ nameMap WRITE setNameMap NOTIFY nameMapChanged FINAL)//Nombre del mapa por si se ha guardado el mapa (Teledirigido)


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

    //edit image
    QString updateMapPaintPoint(QImage &mapa, int columna, int fila, float yaw);

    QString imageSource() const;
    Q_INVOKABLE void setImageSource(const QString &source);

    bool mapping() const;
    Q_INVOKABLE void setMapping(bool newMapping);

    bool saveMap() const;
    Q_INVOKABLE void setSaveMap(bool newSaveMap);

    int typeSaveMap() const;
    Q_INVOKABLE void setTypeSaveMap(int newTypeSaveMap);

    QString nameMap() const;
    Q_INVOKABLE void setNameMap(const QString &newNameMap);

signals:

    void imageReceived(const QString &image);

    void imageSourceChanged();
    void mappingChanged();
    void saveMapChanged();
    void typeSaveMapChanged();
    void nameMapChanged();

private:
    bool moveStop = 0;
    bool SLAM_ON = 1;
    Cliente *cliente;
    float currentAngular;
    float currentLineal;

    QTimer *periodicTimer;

    QByteArray imageBuffer;
    size_t totalSize = 0;
    size_t receivedFrames = 1;
    size_t totalFrames = 0;
    struct FinalPosition finalPosition;

    QString m_imageSource;
    bool m_mapping;
    bool m_saveMap = 0;
    int m_typeSaveMap = -1;
    QString m_nameMap = "";
};

#endif // STRINGHANDLER_H
