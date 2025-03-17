#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QJsonObject>
#include "NetworkDDBB.h"
#include "cliente.h"
#include "include/NetworkDDBB.h"
#include "cliente.h"
#include "include/NetworkDDBB.h"
class Cliente;

class Database : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool passLogin READ passLogin WRITE setPassLogin NOTIFY passLoginChanged FINAL)
    // role is manager and doctor
    Q_PROPERTY(QString role READ role WRITE setRole NOTIFY roleChanged FINAL)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged FINAL)

public:
    enum class Target{
        Login,
        Unknow
    };
    explicit Database(QObject *parent = nullptr);
    void setClient(Cliente *cli);
    Q_INVOKABLE void login(const QString &user, const QString &pass);
    QString targetToString(Target target);
    Target stringToTarget(const QString& str);
    bool passLogin() const;
    void setPassLogin(bool newPassLogin);

    QString role() const;
    void setRole(const QString &newRole);

    QString username() const;
    void setUsername(const QString &newUsername);

    Q_INVOKABLE void clear();

private slots:
    void handleQueryResponse(const QJsonObject& response);

signals:

    void passLoginChanged();
    void roleChanged();
    void usernameChanged();

private:
    void handleLoginResponse(const QJsonObject& response);

    Cliente* cliente;
    NetworkDDBB* networkDDBB;

    bool m_passLogin;
    QString m_role;
    QString m_username;

};

#endif // DATABASE_H
