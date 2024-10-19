#include <QColor>                 // Incluye la clase QColor para trabajar con colores (no se usa explícitamente en este código).
#include <QDebug>                 // Permite utilizar la función de depuración qDebug() para imprimir información en la consola.
#include <QObject>                // Clase base de la mayoría de las clases de Qt. Sirve para manejar señales y slots.
#include <QQmlContext>            // Permite manipular el contexto QML y pasar propiedades de C++ a QML.
#include <QGuiApplication>        // La clase principal para aplicaciones Qt con interfaz gráfica (sin widgets).
#include <QQmlApplicationEngine>  // Motor de Qt que carga y ejecuta archivos QML.
#include <QIcon>

#include "lib/rosnode.h"              // Incluye el archivo de encabezado de la clase RosNode, que contiene la lógica de ROS 2.

int main(int argc, char *argv[])
{
    // Inicializa la aplicación gráfica Qt.
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon("qrc:/images/icon.png"));

    // Inicializa ROS 2, permitiendo la interacción de ROS 2 en esta aplicación.
    rclcpp::init(argc, argv);

    // Declaración de un puntero al contexto QML, que se utilizará más adelante.
    //QQmlContext* context;

    // Crea el motor de QML, que se encargará de cargar y mostrar los archivos QML (la interfaz gráfica).
    QQmlApplicationEngine engine;

    // Crea una instancia de la clase RosNode, que es el nodo de ROS 2 que se utilizará para la lógica de ROS.
    //RosNode node;

    // Define la URL del archivo QML que se cargará. Usa la sintaxis 'qrc:/' para indicar que el archivo está en los recursos del proyecto.
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    // Obtiene el contexto raíz del motor QML. Este contexto es el que permitirá compartir propiedades entre C++ y QML.
    //context = engine.rootContext();

    // Establece una propiedad de contexto llamada "_rosNode", que será accesible desde QML.
    // Esta propiedad contiene una referencia al objeto 'node', es decir, la instancia de RosNode.
    //context->setContextProperty("_rosNode", &node);

    // Carga el archivo QML que contiene la interfaz gráfica de la aplicación, en este caso 'main.qml'.
    engine.load(url);

    // Ejecuta el bucle de eventos de Qt. Esto mantiene la aplicación en ejecución y la hace capaz de responder a eventos (como clics, teclas, etc.).
    return app.exec();
}
