#include "../include/database.h"
#include "../include/cliente.h"
#include "../include/utils_ddbb.h"
#include "../include/NetworkDDBB.h"
#include <qjsonarray.h>

Database::Database(QObject *parent) : QObject(parent)
{
    networkDDBB = new NetworkDDBB(this);
    connect(networkDDBB, &NetworkDDBB::queryResponseReceived, this, &Database::handleQueryResponse);
}

void Database::setClient(Cliente *cli) { cliente = cli; }

void Database::login(const QString &user, const QString &pass)
{
    QString query;
    QJsonArray args;
    if (user == "doctor" && pass == "doctor" || user == "a" && pass == "a" || user == "b" && pass == "b" || user == "manager" && pass == "manager")
    {
        // query = "SELECT * FROM doctor;";
        query = "SELECT 'doctor' AS role, username FROM doctor WHERE username=? AND password =? UNION SELECT 'manager' AS role, username FROM manager WHERE username = ? AND password =?;";
        args.append(user);
        args.append(pass);
        args.append(user);
        args.append(pass);
    }
    else
    {
        query = "SELECT 'doctor' AS role, username FROM doctor WHERE username =? AND password =? UNION SELECT 'manager' AS role, username FROM manager WHERE username = ? AND password =?;";
        args.append(user);
        args.append(hashPassword(pass));
        args.append(user);
        args.append(hashPassword(pass));
    }
    networkDDBB->sendSqlCommand(query, targetToString(Target::Login), args);
}

void Database::signIn(const QString &name, const QString &lastname, const QString &username,const QString &role, const QString &pass)
{
    QString query;
    QJsonArray args;

    query = "INSERT INTO "+ role +" (name, lastname, username, password) VALUES (?,?,?,?);";
    args.append(name);
    args.append(lastname);
    args.append(username);
    args.append(hashPassword(pass));
    networkDDBB->sendSqlCommand(query, targetToString(Target::SignIn), args);
}

void Database::checkUsername(const QString &user)
{
    QString query;
    QJsonArray args;

    query = "SELECT ((SELECT COUNT(*) FROM doctor WHERE username=?) + (SELECT COUNT(*) FROM manager WHERE username = ?))AS total_count;";
    args.append(user);
    args.append(user);
    networkDDBB->sendSqlCommand(query, targetToString(Target::CheckUsername), args);
}

void Database::handleQueryResponse(const QJsonObject &response)
{
    qDebug() << "Respuesta de la consulta recibida:" << response;

    // Extraer el target
    Target target = stringToTarget(response["target"].toString());

    switch (target)
    {
    case Target::Login:
        handleLoginResponse(response);
        break;
    case Target::CheckUsername:
        handleChechUsernameResponse(response);
        break;
    default:
        qDebug() << "Target desconocido o sin manejar.";
        break;
    }
}

void Database::handleLoginResponse(const QJsonObject &response)
{
    if (response["status"].toString() == "success")
    {
        QJsonArray result = response["result"].toArray();
        if (!result.isEmpty() && result[0].isArray())
        {
            qDebug() << "Login successful!";
            setPassLogin(true); // Login correcto
            QJsonArray innerArray = result[0].toArray();

            // Obtener el primer elemento si existe
            if (!innerArray.isEmpty() && innerArray[0].isString())
            {
                setRole(innerArray[0].toString());
                setUsername(innerArray[1].toString());
            }
        }
        else
        {
            qDebug() << "Invalid username or password.";
            setPassLogin(false); // Usuario o contraseña incorrectos
        }
    }
    else
    {
        qDebug() << "Error in query:" << response["message"].toString();
        setPassLogin(false); // Error en la consulta
    }
}
void Database::handleChechUsernameResponse(const QJsonObject &response)
{
    if (response["status"].toString() == "success")
    {
        QJsonArray result = response["result"].toArray();
        if (!result.isEmpty() && result[0].isArray())
        {
            QJsonArray innerArray = result[0].toArray();
            if (!innerArray.isEmpty() && innerArray[0].toInt() >= 0)
            {
                if (innerArray[0].toInt() == 0)
                    setPassCheckUsername(true);
                else
                    setPassCheckUsername(false);
            }
        }
    }
    else
    {
        qDebug() << "Error in query:" << response["message"].toString();
    }
}

QString Database::targetToString(Database::Target target)
{
    static const QMap<Target, QString> targetMap = {
        {Target::Login, "Login"},
        {Target::SignIn, "SignIn"},
        {Target::Guest, "Guest"},
        {Target::CheckUsername, "CheckUsername"},
        {Target::Unknow, "Unknow"}};

    return targetMap.value(target, "Unknow"); // Valor por defecto si no se encuentra
}

// Convierte un QString a Target
Database::Target Database::stringToTarget(const QString &str)
{
    static const QMap<QString, Target> stringMap = {
        {"Login", Target::Login},
        {"SignIn", Target::SignIn},
        {"Guest", Target::Guest},
        {"CheckUsername", Target::CheckUsername},
        {"Unknow", Target::Unknow}};

    return stringMap.value(str, Target::Unknow); // Valor por defecto si no se encuentra
}

bool Database::passLogin() const
{
    return m_passLogin;
}

void Database::setPassLogin(bool newPassLogin)
{
    if (m_passLogin == newPassLogin)
    {
        emit passLoginChanged();
        return;
    }
    m_passLogin = newPassLogin;
    emit passLoginChanged();
}

QString Database::role() const
{
    return m_role;
}

void Database::setRole(const QString &newRole)
{
    if (m_role == newRole)
        return;
    m_role = newRole;
    qDebug() << "Role changed to:" << m_role;
    emit roleChanged();
}

QString Database::username() const
{
    return m_username;
}

void Database::setUsername(const QString &newUsername)
{
    if (m_username == newUsername)
        return;
    m_username = newUsername;
    qDebug() << "Username changed to:" << m_username;
    emit usernameChanged();
}

void Database::clear()
{
    m_passLogin = {false};
    setRole("");
    setUsername("");
}

bool Database::passCheckUsername() const
{
    return m_passCheckUsername;
}

void Database::setPassCheckUsername(bool newpassCheckUsername)
{
    if (m_passCheckUsername == newpassCheckUsername)
    {
        emit passCheckUsernameChanged();
        return;
    }
    m_passCheckUsername = newpassCheckUsername;
    emit passCheckUsernameChanged();
}
