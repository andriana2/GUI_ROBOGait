#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qtconcurrentrun.h>
#include <QLocale>
#include <QQmlContext>
#include <QTranslator>
// #include "include/NetworkDDBB.h"
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
    // QFuture<QJsonObject> future = sqlClient.sendSqlCommand("SELECT * FROM doctor;");
    // // QJsonObject result = future.result();
    // // qDebug() << "Response JSON:" << QJsonDocument(result).toJson(QJsonDocument::Indented);

    // (void) QtConcurrent::run([&future]() {
    //     future.waitForFinished();
    //     QJsonObject result = future.result();
    //     qDebug() << "Response JSON:" << QJsonDocument(result).toJson(QJsonDocument::Indented);
    // });

    return app.exec();
}
