#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QJsonObject>
#include <QStringListModel>

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
    // role is admin and doctor
    Q_PROPERTY(QString role READ role WRITE setRole NOTIFY roleChanged FINAL)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged FINAL)
    Q_PROPERTY(QStringListModel* patients READ patients NOTIFY patientsChanged FINAL)
    Q_PROPERTY(int idPatient READ idPatient WRITE setIdPatient NOTIFY idPatientChanged FINAL)


public:
    enum class Target{
        Login,
        SignIn,
        Guest,
        CheckUsername,
        AddPatient,
        SelectPatient,
        GetIdPatient,
        Unknow
    };
    explicit Database(QObject *parent = nullptr);
    void setClient(Cliente *cli);

    Q_INVOKABLE void login(const QString &user, const QString &pass);
    Q_INVOKABLE void signIn(const QString &name, const QString &lastname, const QString &username,const QString &role, const QString &pass);
    Q_INVOKABLE void checkUsername(const QString &user);
    // Q_INVOKABLE void guest(const QString &name, const QString &lastname);
    Q_INVOKABLE void addPatient(const QString &name, const QString &lastname, int age, double weight, double height, const QString &username, const QString &description);
    Q_INVOKABLE void selectAllPatient(const QString &username);

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

    QStringListModel *patients() const;

    int idPatient() const;
    void setIdPatient(int newIdPatient);
    Q_INVOKABLE void getIdFromName(QString const &complete_name);

private slots:
    void handleQueryResponse(const QJsonObject& response);


signals:

    void passLoginChanged();
    void roleChanged();
    void usernameChanged();

    void passCheckUsernameChanged();

    void patientsChanged();

    void idPatientChanged();

private:
    void handleLoginResponse(const QJsonObject& response);
    void handleChechUsernameResponse(const QJsonObject& response);
    void handleAllPatient(const QJsonObject &response);
    void updatePatients(const QJsonArray &result);
    void handleIdPatient(const QJsonObject &response);

    Cliente* cliente;
    NetworkDDBB* networkDDBB;

    bool m_passLogin;
    QString m_role;
    QString m_username;

    bool m_passCheckUsername = false;
    QStringListModel *m_patients = new QStringListModel(this);
    int m_idPatient;
};

#endif // DATABASE_H
