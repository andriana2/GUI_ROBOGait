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
        query = "SELECT 'doctor' AS role, username FROM doctor WHERE username=? AND password =? UNION SELECT 'manager' AS role, username FROM manager WHERE username = ? AND password =?;";
        args.append(user);
        args.append(pass);
        args.append(user);
        args.append(pass);
    }
    else
    {
        query = "SELECT 'doctor' AS role, username FROM doctor WHERE username =? AND password =? UNION SELECT 'manager' AS role, username FROM manager WHERE username = ? AND password =?;";
        args.append(user.toLower());
        args.append(hashPassword(pass));
        args.append(user.toLower());
        args.append(hashPassword(pass));
    }
    networkDDBB->sendSqlCommand(query, targetToString(Target::Login), args);
}

void Database::signIn(const QString &name, const QString &lastname, const QString &username,const QString &role, const QString &pass)
{
    QString query;
    QJsonArray args;

    query = "INSERT INTO "+ role +" (name, lastname, username, password) VALUES (?,?,?,?);";
    args.append(name.toLower());
    args.append(lastname.toLower());
    args.append(username.toLower());
    args.append(hashPassword(pass));
    networkDDBB->sendSqlCommand(query, targetToString(Target::SignIn), args);
}

void Database::checkUsername(const QString &user)
{
    QString query;
    QJsonArray args;

    query = "SELECT ((SELECT COUNT(*) FROM doctor WHERE username=?) + (SELECT COUNT(*) FROM manager WHERE username = ?))AS total_count;";
    args.append(user.toLower());
    args.append(user.toLower());
    networkDDBB->sendSqlCommand(query, targetToString(Target::CheckUsername), args);
}

void Database::addPatient(const QString &name, const QString &lastname, int age, double weight, double height, const QString &doctor_username) {
    QString query;
    QJsonArray args;

    query = "INSERT INTO Patient (name, lastname, age, weight, height, id_doctor) "
            "SELECT ?, ?, ?, ?, ?, id FROM doctor WHERE username = ?;";

    args.append(name.toLower());
    args.append(lastname.toLower());
    args.append(age);
    args.append(weight);
    args.append(height);
    args.append(doctor_username.toLower());

    networkDDBB->sendSqlCommand(query, targetToString(Target::AddPatient), args);
}

void Database::selectAllPatient(const QString &username_doctor)
{
    QString query;
    QJsonArray args;

    query = "SELECT name, lastname FROM Patient WHERE id_doctor = (SELECT id FROM doctor WHERE username = ?);";

    args.append(username_doctor.toLower());

    networkDDBB->sendSqlCommand(query, targetToString(Target::SelectPatient), args);
}

void Database::handleQueryResponse(const QJsonObject &response)
{
    qDebug() << "Respuesta de la consulta recibida:" << response;

    Target target = stringToTarget(response["target"].toString());

    switch (target)
    {
    case Target::Login:
        handleLoginResponse(response);
        break;
    case Target::CheckUsername:
        handleChechUsernameResponse(response);
        break;
    case Target::SelectPatient:
        handleAllPatient(response);
        break;
    case Target::GetIdPatient:
        handleIdPatient(response);
        break;
    default:
        if (response["status"].toString() != "success")
            qWarning() << "ERROR IN TARGET: " << targetToString(target) << " Error: " << response["result"].toString();
        qDebug() << "Target desconocido o sin manejar. Is: " << response["target"].toString();
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
            setPassLogin(true);
            QJsonArray innerArray = result[0].toArray();

            if (!innerArray.isEmpty() && innerArray[0].isString())
            {
                setRole(innerArray[0].toString());
                setUsername(innerArray[1].toString());
            }
        }
        else
        {
            qDebug() << "Invalid username or password.";
            setPassLogin(false);
        }
    }
    else
    {
        qDebug() << "Error in query:" << response["message"].toString();
        setPassLogin(false);
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

void Database::handleIdPatient(const QJsonObject &response)
{
    if (response["status"].toString() == "success")
    {
        QJsonArray result = response["result"].toArray();
        if (!result.isEmpty() && result[0].isArray())
        {
            QJsonArray innerArray = result[0].toArray();
            if (!innerArray.isEmpty() && innerArray[0].toInt() >= 0)
            {
                if (innerArray[0].toInt() > 0){
                    qDebug()<< "El valor del id patient es: "<<innerArray[0].toInt();
                    setIdPatient(innerArray[0].toInt());
                }
                else
                    qWarning() << "The id in patient is 0 or less";
            }
        }
    }
    else
    {
        qDebug() << "Error in query:" << response["message"].toString();
    }
}

void Database::handleAllPatient(const QJsonObject &response)
{
    if (response["status"].toString() == "success")
    {
        qDebug() << "handle all patient";
        qDebug() << response;
        QJsonArray result = response["result"].toArray();
        updatePatients(result);
    }
    else
    {
        qDebug() << "Error in query:" << response["message"].toString();
    }
}

void Database::updatePatients(const QJsonArray &result)
{
    QStringList patientList;
    for (const QJsonValue &value : result)
    {
        if (value.isArray())
        {
            QJsonArray patientArray = value.toArray();
            if (patientArray.size() == 2)
            {
                QString firstName = capitalizeWords(patientArray[0].toString());
                QString lastName = capitalizeWords(patientArray[1].toString());
                QString fullName = firstName + " " + lastName;
                patientList.append(fullName);
            }
        }
    }
    m_patients->setStringList(patientList);
    emit patientsChanged();
}

QString Database::targetToString(Database::Target target)
{
    static const QMap<Target, QString> targetMap = {
        {Target::Login, "Login"},
        {Target::SignIn, "SignIn"},
        {Target::Guest, "Guest"},
        {Target::CheckUsername, "CheckUsername"},
        {Target::AddPatient, "AddPatient"},
        {Target::SelectPatient, "SelectPatient"},
        {Target::GetIdPatient, "GetIdPatient"},
        {Target::Unknow, "Unknow"}};

    return targetMap.value(target, "Unknow");
}

Database::Target Database::stringToTarget(const QString &str)
{
    static const QMap<QString, Target> stringMap = {
        {"Login", Target::Login},
        {"SignIn", Target::SignIn},
        {"Guest", Target::Guest},
        {"CheckUsername", Target::CheckUsername},
        {"AddPatient", Target::AddPatient},
        {"SelectPatient", Target::SelectPatient},
        {"GetIdPatient", Target::GetIdPatient},
        {"Unknow", Target::Unknow}};

    return stringMap.value(str, Target::Unknow);
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
    emit usernameChanged();
}

void Database::clear()
{
    m_passLogin = {false};
    m_role = ("");
    m_username = ("");
    m_passCheckUsername = false;
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

QStringListModel *Database::patients() const
{
    return m_patients;
}

int Database::idPatient() const
{
    return m_idPatient;
}

void Database::setIdPatient(int newIdPatient)
{
    if (m_idPatient == newIdPatient)
        return;
    m_idPatient = newIdPatient;
    emit idPatientChanged();
}

void Database::getIdFromName(const QString &complete_name)
{
    QString query;
    QJsonArray args;
    auto [firstName_, lastName_] = splitNameSurname(complete_name);

    query = "SELECT id FROM Patient WHERE name = ? AND lastname = ?;";
    args.append(firstName_);
    args.append(lastName_);

    networkDDBB->sendSqlCommand(query, targetToString(Target::GetIdPatient), args);

}
