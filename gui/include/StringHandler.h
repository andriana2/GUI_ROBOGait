#ifndef STRINGHANDLER_H
#define STRINGHANDLER_H

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
#include "MapInfo.h"
#include "include/utils.h"

class Cliente;
class MapInfo;

class StringHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged) //La imagen que se muestra (Teledirigido)
    Q_PROPERTY(bool mapping READ mapping WRITE setMapping NOTIFY mappingChanged FINAL)//Si estoy mapeando o solo moviendo con el joystick (Teledirigido)
    Q_PROPERTY(bool saveMap READ saveMap WRITE setSaveMap NOTIFY saveMapChanged FINAL)//Saber si se ha guaradado la imagen (Teledirigido)
    Q_PROPERTY(int typeSaveMap READ typeSaveMap WRITE setTypeSaveMap NOTIFY typeSaveMapChanged FINAL)//Tipo de mapa si se a guardado o no (Teledirigido)
    Q_PROPERTY(QString nameMap READ nameMap WRITE setNameMap NOTIFY nameMapChanged FINAL)//Nombre del mapa por si se ha guardado el mapa (Teledirigido)
    Q_PROPERTY(QStringListModel* model READ model NOTIFY modelChanged FINAL) // lista que aparece (SelectMap)


public:
    explicit StringHandler(QObject *parent = nullptr);
    Q_INVOKABLE bool isInSameNetwork(const QString &ip1, const std::string& subnetMask = "255.255.255.0");
    Q_INVOKABLE void setImage(const QByteArray &data);
    Q_INVOKABLE QString getImageSource();
    Q_INVOKABLE void sendStateRemoteControlledHandler(bool mapping, bool in);

    void setClient(Cliente *cli);
    void setMapInfo(MapInfo *mapIn);

    // msg send
    Q_INVOKABLE void setCurrentMove(const QString &lineal,const QString & angular);
    void setImageMap(const QByteArray &data);

    // msg recived
    void getImageMapSlam(const QJsonObject &json);
    void getImageMapPath(const QJsonObject &json);
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

    Q_INVOKABLE QStringListModel *model() const;
    Q_INVOKABLE void loadData(const std::vector<std::string> &data);
    Q_INVOKABLE void requestMapName();

    Q_INVOKABLE void menu_page(bool in);

    Q_INVOKABLE void closeConnection();

signals:

    void imageReceived(const QString &image);

    void imageSourceChanged();
    void mappingChanged();
    void saveMapChanged();
    void typeSaveMapChanged();
    void nameMapChanged();

    void modelChanged();

private:
    bool moveStop = 0;
    bool SLAM_ON = 1;
    Cliente *cliente;
    MapInfo *mapInfo;
    float currentAngular;
    float currentLineal;

    QTimer *periodicTimer;

    QByteArray imageBuffer;
    size_t totalSize = 0;
    size_t receivedFrames = 1;
    size_t totalFrames = 0;
    struct FinalPosition finalPosition;

    QString m_imageSource;
    bool m_mapping = 0;
    bool m_saveMap = 0;
    int m_typeSaveMap = -1;
    QString m_nameMap = "";
    QStringListModel *m_model = nullptr;
};

#endif // STRINGHANDLER_H
