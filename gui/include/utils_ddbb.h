#ifndef UTILS_DDBB_H
#define UTILS_DDBB_H

#include <QString>

QString hashPassword(const QString &password);
QString capitalizeWords(const QString &str);
std::pair<QString, QString> splitNameSurname(const QString &fullName);

#endif // UTILS_DDBB_H
