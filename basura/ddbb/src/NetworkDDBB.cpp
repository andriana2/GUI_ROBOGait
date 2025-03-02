#include "../include/NetworkDDBB.h"
#include <QtConcurrent>

NetworkDDBB::NetworkDDBB(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
}

QFuture<QJsonObject> NetworkDDBB::sendSqlCommand(const QString &query) {
    QPromise<QJsonObject> promise;
    auto future = promise.future();

    QUrl url("http://127.0.0.1:5000/execute");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["query"] = query;
    QByteArray data = QJsonDocument(json).toJson();

    QNetworkReply *reply = manager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [reply, promise = std::move(promise)]() mutable {
        QJsonObject result;
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
            result = jsonResponse.object();
        } else {
            result["error"] = reply->errorString();
        }
        reply->deleteLater();
        promise.addResult(result);
        promise.finish();
    });

    return future;
}
