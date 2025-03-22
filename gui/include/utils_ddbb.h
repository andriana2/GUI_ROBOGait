#ifndef UTILS_DDBB_H
#define UTILS_DDBB_H

#include <QString>

QString quote(const QString &value);
QString quote(int value);
QString quote(double value);
QString hashPassword(const QString &password);
QString capitalizeWords(const QString &str);

#endif // UTILS_DDBB_H
