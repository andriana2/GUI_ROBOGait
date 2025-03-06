#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qtconcurrentrun.h>
#include <QLocale>
#include <QQmlContext>
#include <QTranslator>
#include "include/NetworkDDBB.h"
#include "include/database.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "gui_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
    Database database;


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("database", &database);
    const QUrl url(QStringLiteral("qrc:/ddbb/qml/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    // NetworkDDBB sqlClient;
    // sqlClient.sendSqlCommand("SELECT * FROM doctor;");
    // sqlClient.sendSqlCommand("SELECT * FROM manager;");

    return app.exec();
}




// #include <QCoreApplication>
// #include <QNetworkAccessManager>
// #include <QNetworkRequest>
// #include <QNetworkReply>
// #include <QJsonDocument>
// #include <QJsonObject>
// #include <QJsonArray>
// #include <QDebug>

// class NetworkDDBBB : public QObject {
//     Q_OBJECT

// public:
//     NetworkDDBBB(QObject* parent = nullptr) : QObject(parent) {
//         manager = new QNetworkAccessManager(this);
//         connect(manager, &QNetworkAccessManager::finished, this, &NetworkDDBBB::onReplyFinished);
//     }

//     void sendSqlCommand(const QString& sqlQuery) {
//         QUrl url("http://127.0.0.1:5000/execute");  // URL del servidor Flask
//         QNetworkRequest request(url);
//         request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//         // Crear JSON con la consulta SQL
//         QJsonObject json;
//         json["query"] = sqlQuery;

//         // Enviar petición POST con JSON
//         QNetworkReply* reply = manager->post(request, QJsonDocument(json).toJson());
//         connect(reply, &QNetworkReply::errorOccurred, this, &NetworkDDBBB::onError);
//     }

// private slots:
//     void onReplyFinished(QNetworkReply* reply) {
//         if (reply->error() != QNetworkReply::NoError) {
//             qDebug() << "Error en respuesta:" << reply->errorString();
//             return;
//         }

//         // Leer la respuesta JSON
//         QByteArray responseData = reply->readAll();
//         QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
//         QJsonObject jsonObject = jsonResponse.object();

//         qDebug() << "Respuesta del servidor Flask:" << jsonResponse.toJson(QJsonDocument::Indented);

//         reply->deleteLater();
//     }

//     void onError(QNetworkReply::NetworkError error) {
//         qDebug() << "Error en la solicitud:" << error;
//     }

// private:
//     QNetworkAccessManager* manager;
// };

// int main(int argc, char* argv[]) {
//     QGuiApplication a(argc, argv);

//     NetworkDDBBB sqlClient;
//     sqlClient.sendSqlCommand("SELECT * FROM doctor;");
//     sqlClient.sendSqlCommand("SELECT * FROM manager;");

//     return a.exec();
// }

// #include "main.moc"
