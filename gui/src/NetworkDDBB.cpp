#include "../include/NetworkDDBB.h"
// #include <QtConcurrent>

NetworkDDBB::NetworkDDBB(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &NetworkDDBB::onReplyFinished);
}

void NetworkDDBB::sendSqlCommand(const QString& sqlQuery, const QString& target, const QJsonArray& args) {
    QUrl url("http://127.0.0.1:5000/execute");  // URL del servidor Flask
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    qDebug() << "Enviando consulta SQL:" << sqlQuery;
    // Crear JSON con la consulta SQL
    QJsonObject json;
    json["query"] = sqlQuery;
    json["target"] = target;
    json["args"] = args;

    // Enviar petición POST con JSON
    QNetworkReply* reply = manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::errorOccurred, this, &NetworkDDBB::onError);
}

void NetworkDDBB::onReplyFinished(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error en respuesta:" << reply->errorString();
        return;
    }

    // Leer la respuesta JSON
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = jsonResponse.object();

    qDebug() << "Respuesta del servidor Flask:" << jsonResponse.toJson(QJsonDocument::Indented);

    emit queryResponseReceived(jsonObject);  // Emit the signal with the response

    reply->deleteLater();
}

void NetworkDDBB::onError(QNetworkReply::NetworkError error) {
    qDebug() << "Error en la solicitud:" << error;
}
