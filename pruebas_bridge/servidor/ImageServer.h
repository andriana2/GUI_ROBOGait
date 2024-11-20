#ifndef IMAGESERVER_H
#define IMAGESERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QDebug>
#include <QApplication>
#include <QString>

class ImageServer : public QTcpServer {
    Q_OBJECT

public:
    ImageServer(QObject *parent = nullptr);

    void startServer(quint16 port);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QFile imageFile;      // Archivo donde se guardará la imagen
    QTcpSocket *socket;
    QString saludo;
};

#endif // IMAGESERVER_H
