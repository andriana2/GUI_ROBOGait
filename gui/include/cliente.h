#ifndef CLIENTE_H
#define CLIENTE_H

#include "database.h"
#include "StringHandler.h"
#include "MapInfo.h"

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTimer>

#include <QJsonDocument>
#include <QJsonObject>

#include <QImage>


class StringHandler;
class MapInfo;
class Database;

class Cliente : public QObject
{
    Q_OBJECT
public:
    Cliente(int port_tcp, int port_udp); //
    ~Cliente();

    QTcpSocket *socket;
    QUdpSocket udpSocket;
    QHostAddress servidor;

    void setStringHandler(StringHandler *sh);//
    void setMapInfo(MapInfo *sh);
    void setDatabase(Database *sh);

    void sendMessage(const QJsonDocument &jsone);  //
    // void receiveImageMap(const QByteArray &link);
    // void processServerResponse();

    bool getStatus(); //
    // void sendRequestImg(const QString &target);

    void parseJsonToQList(const QJsonObject &jsonObj);
    void answerUdp();
    void startSearchUdp();
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
    int port_tcp;
    int port_udp;
    bool status;
    QTimer *timeoutTimer;

    Database *database;
    StringHandler *stringHandler;
    MapInfo *mapInfo;
};

#endif // CLIENTE_H
