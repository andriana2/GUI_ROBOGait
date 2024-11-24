#ifndef IMAGECLIENT_H
#define IMAGECLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>
#include <QDebug>
#include <QApplication>


class ImageClient : public QObject {
    Q_OBJECT

public:
    ImageClient(QObject *parent = nullptr);
    void sendImage(const QString &host, quint16 port, const QString &imagePath);
    void receiveImage(const QString &host, quint16 port, const QString &outputPath);

};

#endif // IMAGECLIENT_H
