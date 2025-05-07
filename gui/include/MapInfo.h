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

// #include <opencv2/opencv.hpp>
#include <vector>

#include "cliente.h"
#include "StringHandler.h"
#include "utils.h"

class Cliente;
class StringHandler;

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
    Q_PROPERTY(Pixel finalScreenPosition READ finalScreenPosition NOTIFY finalScreenPositionChanged FINAL)

    Q_PROPERTY(float resolution READ resolution WRITE setResolution NOTIFY resolutionChanged FINAL)
    Q_PROPERTY(bool checkInitInitialPose READ checkInitInitialPose WRITE setCheckInitInitialPose NOTIFY checkInitInitialPoseChanged FINAL)
    Q_PROPERTY(QList<Pixel> trajectoryGoalPose READ trajectoryGoalPose NOTIFY trajectoryGoalPoseChanged FINAL)

    // Q_PROPERTY(QVariantMap mapInformation READ mapInformation WRITE setMapInformation NOTIFY mapInformationChanged)


public:
    explicit MapInfo(QObject *parent = nullptr);

    void setClient(Cliente *cli);
    void setStringHandler(StringHandler *sh);

    QString mapName() const;
    Q_INVOKABLE void setMapName(const QString &newMapName);

    float orientation() const;
    Q_INVOKABLE void setOrientation(float newOrientation);

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
    Q_INVOKABLE void clearListPixels();

    QString imgSource() const;
    Q_INVOKABLE void setImgSource(const QString &newImgSource);

    float finalPathOrientation() const;
    Q_INVOKABLE void setFinalPathOrientation(float newFinalPathOrientation);

    Pixel finalPathPosition() const;
    Q_INVOKABLE void setFinalPathPosition(const int &x, const int &y);

    Q_INVOKABLE void clearInfoImage();

    Q_INVOKABLE bool checkPixelBlack(const int &x, const int &y);

    Pixel finalScreenPosition() const;
    Q_INVOKABLE void setFinalScreenPosition(const int &x, const int &y);

    Q_INVOKABLE QVariantList getPixels();


    // bool isBlack(const cv::Mat &image, cv::Point point);
    bool isBlack(const QImage &image, const Pixel& point, int radius);
    // std::vector<cv::Point> getLinePixels(cv::Point p1, cv::Point p2);
    bool linePassesThroughBlack(const QImage &image, Pixel p1, Pixel p2);

    QList<Pixel> filtrarPuntosCercanos(const QList<Pixel>& puntos, int distancia);
    double distancia(const Pixel& p1, const Pixel& p2);
    Pixel puntoIntermedio(const Pixel& p1, const Pixel& p2, double distanciaObjetivo);
    QList<Pixel> suavizarTrayectoria(const QList<Pixel>& puntos, double distanciaSuavizado = 2.0);
    QList<Pixel> rdp(const QList<Pixel>& pts, double eps);
    double puntoLineaDist(const Pixel& p, const Pixel& a, const Pixel& b);

    // cv::Mat base64ToMat(const QString &base64);
    Q_INVOKABLE bool checkPathBlack();

    std::vector<Pixel> getLinePixels(Pixel p1, Pixel p2);

    Q_INVOKABLE void initBringUp();
    Q_INVOKABLE void sendInitialPose();
    Q_INVOKABLE void sendAllInformationPose();
    Q_INVOKABLE void sendGoalPose();
    Q_INVOKABLE void sendWaypointFollower();
    Q_INVOKABLE void sendStopProcesses();

    float resolution() const;
    void setResolution(float newResolution);

    bool checkInitInitialPose() const;
    Q_INVOKABLE void setCheckInitInitialPose(bool newCheckInitInitialPose);

    void getRobotPositionInitialpose(const QJsonObject &json);

    Q_INVOKABLE QList<Pixel> trajectoryGoalPose() const;
    void setTrajectoryGoalPose(QList<Pixel> const &trajectory);
    Q_INVOKABLE void clearTrajectoryGoalPose();

    void parseJsonToQList(const QJsonObject &jsonObj);

    Q_INVOKABLE void clearNextPath();
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

    void finalScreenPositionChanged();

    void resolutionChanged();

    void checkInitInitialPoseChanged();

    void trajectoryGoalPoseChanged();

private:
    Cliente *cliente;
    StringHandler *stringHandler;
    bool repeated_delegate_list_view = 0;

    QTimer *periodicTimerMapInfo;

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

    Pixel m_finalScreenPosition;
    float m_resolution;
    bool m_checkInitInitialPose;


    QList<Pixel> m_trajectoryGoalPose;
};

#endif // MAPINFO_H
