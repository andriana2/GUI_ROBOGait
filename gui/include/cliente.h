#ifndef CLIENTE_H
#define CLIENTE_H

#include <QObject>
#include <QTcpSocket>

class Cliente : public QObject
{
    Q_OBJECT
public:
    explicit Cliente(QObject *parent = nullptr);
    ~Cliente();

    void connectToServer(const QString &host, quint16 port);
    void sendMessage(const QString &message);
    void processServerResponse();
    void setIp(QString const &ip_){ip = ip_;}

private:
    QString ip;
    int puerto;
    // QTcpSocket *socket;
};

#endif // CLIENTE_H
