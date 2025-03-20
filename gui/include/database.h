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
    Q_PROPERTY(bool passCheckUsername READ passCheckUsername WRITE setPassCheckUsername NOTIFY passCheckUsernameChanged FINAL)
    // role is manager and doctor
    Q_PROPERTY(QString role READ role WRITE setRole NOTIFY roleChanged FINAL)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged FINAL)

public:
    enum class Target{
        Login,
        SignIn,
        Guest,
        CheckUsername,
        Unknow
    };
    explicit Database(QObject *parent = nullptr);
    void setClient(Cliente *cli);

    Q_INVOKABLE void login(const QString &user, const QString &pass);
    Q_INVOKABLE void signIn(const QString &name, const QString &lastname, const QString &username,const QString &role, const QString &pass);
    Q_INVOKABLE void checkUsername(const QString &user);
    // Q_INVOKABLE void guest(const QString &name, const QString &lastname);


    QString targetToString(Target target);
    Target stringToTarget(const QString& str);
    bool passLogin() const;
    void setPassLogin(bool newPassLogin);

    QString role() const;
    void setRole(const QString &newRole);

    QString username() const;
    void setUsername(const QString &newUsername);

    Q_INVOKABLE void clear();

    bool passCheckUsername() const;
    void setPassCheckUsername(bool newPassCheckUsername);

private slots:
    void handleQueryResponse(const QJsonObject& response);


signals:

    void passLoginChanged();
    void roleChanged();
    void usernameChanged();

    void passCheckUsernameChanged();

private:
    void handleLoginResponse(const QJsonObject& response);
    void handleSignInResponse(const QJsonObject& response);
    void handleGuestResponse(const QJsonObject& response);
    void handleChechUsernameResponse(const QJsonObject& response);

    Cliente* cliente;
    NetworkDDBB* networkDDBB;

    bool m_passLogin;
    QString m_role;
    QString m_username;

    bool m_passCheckUsername = false;
};

#endif // DATABASE_H
