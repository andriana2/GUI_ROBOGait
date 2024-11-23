#ifndef STRINGHANDLER_H
#define STRINGHANDLER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <string>
// #include "utils.h"

class StringHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Move currentMove READ currentMove WRITE setCurrentMove NOTIFY currentMoveChanged)


public:
    Q_INVOKABLE bool isInSameNetwork(const QString &ip1, const std::string& subnetMask = "255.255.255.0");


public:
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
    explicit StringHandler(QObject *parent = nullptr);
 Q_INVOKABLE Move stringToMove(const QString &move) const;

    Move currentMove() const { return m_currentMove; }
    void setCurrentMove(Move newCurrentMove);

public slots:
    QString moveToString(StringHandler::Move move) const;

signals:

    void currentMoveChanged();

private:

    QString m_inputString;
    QString m_resultString;
    Move m_currentMove;
};

#endif // STRINGHANDLER_H
