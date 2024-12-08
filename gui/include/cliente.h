#ifndef CLIENTE_H
#define CLIENTE_H

#include "StringHandler.h"
#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QImage>

class StringHandler;

class Cliente : public QObject
{
    Q_OBJECT
public:
    Cliente(int portNumber); //

    QTcpSocket *socket; //
    void setStringHandler(StringHandler *sh);

    void connectToServer(const QString &host, quint16 port);
    void sendMessagePosition(const QString &message);
    void receiveImageMap(const QByteArray &link);
    void processServerResponse();

    bool getStatus(); //
    void sendRequestImg(const QString &target);

public slots:
    void closeConnection(); //
    void connect2host(const QString hostAddress); //

signals:
    void statusChanged(bool);

private slots:
    void onReadyRead();
    // void readyRead();
    void connected(); //
    void connectionTimeout(); //
    void onErrorOccurred(QAbstractSocket::SocketError error);

private:
    bool maping;
    QString host;
    int port;
    bool status;
    QTimer *timeoutTimer;

    StringHandler *stringHandler;
};

#endif // CLIENTE_H
