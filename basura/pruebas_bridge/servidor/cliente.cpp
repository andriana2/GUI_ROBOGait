#include "ImageClient.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ImageClient client;
    client.sendImage("127.0.0.1", 12345, "/home/andri/Downloads/paisaje.jpg");

    return a.exec();
}
