#include "../include/utils_ddbb.h"
#include <QCryptographicHash>
#include <QString>

QString quote(const QString &value)
{
    QString escaped = value;

    // Escapar comillas simples reemplazándolas por dobles comillas simples (' -> '')
    int pos = 0;
    while ((pos = escaped.indexOf("'", pos)) != -1) {
        escaped.replace(pos, 1, "''");
        pos += 2; // Avanzar después del reemplazo
    }

    // Envolver el valor entre comillas simples
    return "'" + escaped + "'";
}

QString quote(int value) {
    return QString::number(value);
}

QString quote(double value) {
    return QString::number(value);
}

QString hashPassword(const QString &password) {
    QByteArray hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hashed.toHex());  // Convert to hexadecimal string
}
