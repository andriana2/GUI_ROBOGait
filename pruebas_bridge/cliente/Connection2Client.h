#ifndef CONNECTION2CLIENT_H
#define CONNECTION2CLIENT_H

#include <QObject>

class Connection2Client: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int counter READ counter WRITE setCounter NOTIFY counterChanged FINAL)
public:
    Connection2Client(QObject *parent = nullptr);
    int counter() const;
    void setCounter(int newCounter);
public slots:
    void ejecutar_imagen();
signals:
    void counterChanged();
private:
    int m_counter;
};

#endif // CONNECTION2CLIENT_H
