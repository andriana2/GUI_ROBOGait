// #include <QGuiApplication>
// #include <QQmlApplicationEngine>

// int main(int argc, char *argv[])
// {
//     QGuiApplication app(argc, argv);

//     QQmlApplicationEngine engine;
//     const QUrl url(QStringLiteral("qrc:/app_con_socket/main.qml"));
//     QObject::connect(
//         &engine,
//         &QQmlApplicationEngine::objectCreated,
//         &app,
//         [url](QObject *obj, const QUrl &objUrl) {
//             if (!obj && url == objUrl)
//                 QCoreApplication::exit(-1);
//         },
//         Qt::QueuedConnection);
//     engine.load(url);

//     return app.exec();
// }


#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Connection2Client.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Crear una instancia del backend
    Connection2Client connection;

    // Registrar la instancia en el contexto de QML
    engine.rootContext()->setContextProperty("connection", &connection);

    // Cargar el archivo QML principal
    const QUrl url(QStringLiteral("qrc:/app_con_socket/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
