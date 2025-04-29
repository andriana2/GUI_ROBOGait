#ifndef NETWORKDDBB_H
#define NETWORKDDBB_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


class NetworkDDBB : public QObject {
    Q_OBJECT
public:
    explicit NetworkDDBB(QObject *parent = nullptr);
    void sendSqlCommand(const QString& sqlQuery, const QString& target, const QJsonArray& args = QJsonArray());

signals:
    void queryResponseReceived(const QJsonObject& response);

private slots:
    void onReplyFinished(QNetworkReply* reply);
    void onError(QNetworkReply::NetworkError error);

private:
    QNetworkAccessManager* manager;
};

#endif // NETWORKDDBB_H
