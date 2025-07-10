#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <stringHandler.h>

int main(
    int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    StringHandler stringHandler;
    stringHandler.loadData();
    engine.rootContext()->setContextProperty("stringHandler", &stringHandler);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("untitled4", "Main");

    return app.exec();
}
