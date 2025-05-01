#ifndef NETWORKDDBB_H
#define NETWORKDDBB_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

class NetworkDDBB : public QObject {
    Q_OBJECT

public:
    explicit NetworkDDBB(QObject *parent = nullptr);

    void sendSqlCommand(const QString& sqlQuery, const QString& target, const QJsonArray& args = QJsonArray());
    void setServerIp(const QString& ip);  // Setter for the server IP

signals:
    void queryResponseReceived(const QJsonObject& response);

private slots:
    void onReplyFinished(QNetworkReply* reply);
    void onError(QNetworkReply::NetworkError error);

private:
    QNetworkAccessManager* manager;
    QString serverIp = "127.0.0.1";  // Default IP address
};

#endif // NETWORKDDBB_H
