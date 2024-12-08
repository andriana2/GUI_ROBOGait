#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QLocale>
#include <QTranslator>
#include "../include/StringHandler.h"
#include "../include/cliente.h"
// #include "../include/Manage.h"


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

    Cliente cliente(8080);
    StringHandler stringHandler;
    cliente.setStringHandler(&stringHandler);
    stringHandler.setClient(&cliente);


    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("stringHandler", &stringHandler);

    const QUrl url(QStringLiteral("qrc:/gui/qml/main.qml"));
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

    return app.exec();
}
