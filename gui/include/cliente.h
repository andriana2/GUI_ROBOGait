#ifndef CLIENTE_H
#define CLIENTE_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class Cliente : public QObject
{
    Q_OBJECT
public:
    Cliente(int portNumber); //

    QTcpSocket *socket; //

    void connectToServer(const QString &host, quint16 port);
    void sendMessagePosition(const QString &message);
    void sendImageMap(const QString &link);
    void processServerResponse();

    bool getStatus(); //

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
    QString host;
    int port;
    bool status;
    QTimer *timeoutTimer;
};

#endif // CLIENTE_H
