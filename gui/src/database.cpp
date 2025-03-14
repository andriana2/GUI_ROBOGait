#include "../include/database.h"
#include "include/cliente.h"

Database::Database(
    QObject *parent)
    : QObject{parent}
{}

void Database::setClient(Cliente *cli) { cliente = cli; }
