#include "../include/utils_ddbb.h"
#include <QCryptographicHash>
#include <QString>
#include <QStringList> // Include the header for QStringList

QString hashPassword(const QString &password)
{
    QByteArray hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hashed.toHex()); // Convert to hexadecimal string
}

QString capitalizeWords(const QString &str)
{
    QStringList words = str.split(' ', Qt::SkipEmptyParts);
    for (QString &word : words)
    {
        if (!word.isEmpty())
        {
            word[0] = word[0].toUpper();
        }
    }
    return words.join(' ');
}

std::pair<QString, QString> splitNameSurname(const QString &fullName)
{
    QStringList parts = fullName.split(',');

    if (parts.size() != 2)
    {
        // Formato inesperado
        return {fullName.trimmed().toLower(), ""};
    }

    QString firstName = parts[1].trimmed().toLower();
    QString lastName = parts[0].trimmed().toLower();

    return {firstName, lastName};
}

