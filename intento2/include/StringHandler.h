#ifndef STRINGHANDLER_H
#define STRINGHANDLER_H

#include <QObject>
#include <QString>
#include <string>
#include "utils.h"

class StringHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString inputString READ inputString WRITE setInputString NOTIFY inputStringChanged)
    Q_PROPERTY(QString resultString READ resultString NOTIFY resultStringChanged)

public:
    Q_INVOKABLE bool isInSameNetwork(const QString &ip1, const std::string& subnetMask = "255.255.255.0");

public:
    explicit StringHandler(QObject *parent = nullptr);

    QString inputString() const;
    void setInputString(const QString &newString);

    QString resultString() const;

    // bool isInSameNetwork(const QString &ip1, const std::string& subnetMask = "255.255.255.0");

public slots:
    void compareWith(const QString &compareString);
    void sendFromTerminal(const QString &text);

signals:
    void inputStringChanged();
    void resultStringChanged();

private:
    QString m_inputString;
    QString m_resultString;
};

#endif // STRINGHANDLER_H
