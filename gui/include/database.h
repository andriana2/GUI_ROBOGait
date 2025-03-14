#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include "cliente.h"

class Cliente;

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);

    void setClient(Cliente *cli);
private:
    Cliente *cliente;

signals:
};

#endif // DATABASE_H
