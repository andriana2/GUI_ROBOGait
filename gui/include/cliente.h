#ifndef CLIENTE_H
#define CLIENTE_H

#include "StringHandler.h"
#include "MapInfo.h"

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

#include <QJsonDocument>
#include <QJsonObject>

#include <QImage>


class StringHandler;
class MapInfo;

class Cliente : public QObject
{
    Q_OBJECT
public:
    Cliente(int portNumber); //
    ~Cliente();

    QTcpSocket *socket;
    void setStringHandler(StringHandler *sh);//
    void setMapInfo(MapInfo *sh);

    void sendMessage(const QJsonDocument &jsone);  //
    // void receiveImageMap(const QByteArray &link);
    // void processServerResponse();

    bool getStatus(); //
    // void sendRequestImg(const QString &target);

public slots:
    void closeConnection(); //
    void connect2host(const QString hostAddress); //

signals:
    void statusChanged(bool);

private slots:
    void onReadyRead();//
    void processJson(const QJsonDocument &json);//
    void connected(); //
    void connectionTimeout(); //
    void onErrorOccurred(QAbstractSocket::SocketError error); //

private:

    //json
    QJsonDocument jsonDoc;
    //map
    bool maping;

    //connection
    QString host;
    int port;
    bool status;
    QTimer *timeoutTimer;

    StringHandler *stringHandler;
    MapInfo *mapInfo;
};

#endif // CLIENTE_H
