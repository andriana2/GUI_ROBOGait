#include "ImageServer.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ImageServer server;
    server.startServer(12345);  // Escucha en el puerto 12345

    return a.exec();
}
