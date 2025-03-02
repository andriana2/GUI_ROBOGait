#ifndef NETWORKDDBB_H
#define NETWORKDDBB_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFuture>
#include <QPromise>

class NetworkDDBB : public QObject {
    Q_OBJECT
public:
    explicit NetworkDDBB(QObject *parent = nullptr);
    QFuture<QJsonObject> sendSqlCommand(const QString &query);

private:
    QNetworkAccessManager *manager;
};

#endif // NETWORKDDBB_H
