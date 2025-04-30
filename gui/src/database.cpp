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
        query = "SELECT role, username FROM user WHERE username = ? AND password =?;";
        args.append(user);
        args.append(pass);
    }
    else
    {
        query = "SELECT role, username FROM user WHERE username = ? AND password =?;";
        args.append(user.toLower());
        args.append(hashPassword(pass));
    }
    networkDDBB->sendSqlCommand(query, targetToString(Target::Login), args);
}

void Database::signIn(const QString &name, const QString &lastname, const QString &username, const QString &role, const QString &pass)
{
    QString query;
    QJsonArray args;

    query = "INSERT INTO user (name, lastname, username, password, role) VALUES (?,?,?,?,?);";
    args.append(name.toLower());
    args.append(lastname.toLower());
    args.append(username.toLower());
    args.append(hashPassword(pass));
    args.append(role.toLower());
    networkDDBB->sendSqlCommand(query, targetToString(Target::SignIn), args);
}

void Database::checkUsername(const QString &user)
{
    QString query;
    QJsonArray args;

    query = "SELECT COUNT(*) AS total_count FROM user WHERE username = ?;";
    args.append(user.toLower());
    networkDDBB->sendSqlCommand(query, targetToString(Target::CheckUsername), args);
}

void Database::addPatient(const QString &name, const QString &lastname, int age, double weight, double height, const QString &username, const QString &description)
{
    QString query;
    QJsonArray args;

    query = "INSERT INTO patient (name, lastname, age, weight, height, description, create_day, id_user) "
            "SELECT ?, ?, ?, ?, ?, ?, CURRENT_TIMESTAMP, id FROM user WHERE username = ?;";

    args.append(name.toLower());
    args.append(lastname.toLower());
    args.append(age);
    args.append(weight);
    args.append(height);
    args.append(description);
    args.append(username.toLower());

    networkDDBB->sendSqlCommand(query, targetToString(Target::AddPatient), args);
}

void Database::selectAllPatient(const QString &username)
{
    QString query;
    QJsonArray args;

    query = "SELECT name, lastname FROM patient WHERE id_user = (SELECT id FROM user WHERE username = ?);";

    args.append(username.toLower());

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
            if (innerArray.size() >= 7) // Ensure all expected fields are present
            {
                int id = innerArray[0].toInt();
                int age = innerArray[1].toInt();
                double weight = innerArray[2].toDouble();
                double height = innerArray[3].toDouble();
                QString description = innerArray[4].toString();
                QString createDay = innerArray[5].toString();
                int userId = innerArray[6].toInt();
                QString name = innerArray[7].toString();
                QString lastname = innerArray[8].toString();

                if (id > 0)
                {
                    qDebug() << "Patient ID:" << id;
                    qDebug() << "Age:" << age;
                    qDebug() << "Weight:" << weight;
                    qDebug() << "Height:" << height;
                    qDebug() << "Description:" << description;
                    qDebug() << "Create Day:" << createDay;
                    qDebug() << "User ID:" << userId;
                    qDebug() << "Name:" << name;
                    qDebug() << "Lastname:" << lastname;

                    // Store the values in appropriate member variables or emit signals
                    setIdPatient(id);
                    setPatient({{"id", id}, {"age", age}, {"weight", weight}, {"height", height}, {"description", description}, {"create_day", createDay}, {"id_user", userId}, {"user_name", name}, {"user_lastname", lastname}});
                    // setPatientDetails(age, weight, height, description, createDay, userId);
                }
                else
                {
                    qWarning() << "The patient ID is 0 or less";
                }
            }
            else
            {
                qWarning() << "Unexpected response structure: insufficient fields";
            }
        }
        else
        {
            qWarning() << "No valid data found in the response";
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
                QString fullName = firstName + ", " + lastName;
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

    query = "SELECT Patient.id, Patient.age, Patient.weight, Patient.height, Patient.description, Patient.create_day, User.id AS user_id, User.name AS user_name, User.lastname AS user_lastname "
            "FROM Patient JOIN User ON Patient.id_user = User.id WHERE Patient.name = ? AND Patient.lastname = ?";
    args.append(firstName_);
    args.append(lastName_);

    networkDDBB->sendSqlCommand(query, targetToString(Target::GetIdPatient), args);
}

QVariantMap Database::patient() const
{
    return m_patient;
}

void Database::setPatient(const QVariantMap &newPatient)
{
    if (m_patient == newPatient)
        return;
    m_patient = newPatient;
    emit patientChanged();
}
