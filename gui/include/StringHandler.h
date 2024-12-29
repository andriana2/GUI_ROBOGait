#ifndef STRINGHANDLER_H
#define STRINGHANDLER_H

#include <QObject>
#include <QDebug>
#include <QString>
// #include <QImage>
// #include <string>
// #include "utils.h"
#include <QJsonDocument>
#include <QJsonObject>

#include "cliente.h"

class Cliente;

class StringHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Move currentMove READ currentMove WRITE setCurrentMove NOTIFY currentMoveChanged)
    Q_PROPERTY(QString imageSource READ imageSource NOTIFY imageSourceChanged)

public:
    explicit StringHandler(QObject *parent = nullptr);
    Q_INVOKABLE bool isInSameNetwork(const QString &ip1, const std::string& subnetMask = "255.255.255.0");
    Q_INVOKABLE void setImage(const QByteArray &data);
    Q_INVOKABLE QString getImageSource();

    void setClient(Cliente *cli);
    enum Move {
        Recto,
        Atras,
        Giro_Izquierda,
        Giro_Derecha,
        Mas_Rapido,
        Mas_Lento,
        Stop
    };
    Q_ENUM(Move)
    Q_INVOKABLE Move stringToMove(const QString &move) const;
    Move currentMove() const { return m_currentMove; }

    // msg send
    void setCurrentMove(Move newCurrentMove);
    void setImageMap(const QByteArray &data);

    // msg recived
    void getImageMapSlam(const QJsonObject &json);
    void getRobotPositionPixel(const QJsonObject &json);


    // public slots:


    QString imageSource() const;

signals:

    void currentMoveChanged();
    void imageReceived(const QString &image);

    void imageSourceChanged();

private:
    void moveToString(StringHandler::Move move, float& linear, float& angular) const;
    Move m_currentMove;

    Cliente *cliente;

    QString m_imageSource;

    QByteArray imageBuffer;
    size_t totalSize = 0;
    size_t receivedFrames = 0;
    size_t totalFrames = 0;
};

#endif // STRINGHANDLER_H
