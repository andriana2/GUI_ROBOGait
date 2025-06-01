#include "../include/database.h"
#include "../include/cliente.h"
#include "../include/StringHandler.h"
#include "../include/utils_ddbb.h"
#include "../include/NetworkDDBB.h"
#include <qjsonarray.h>

Database::Database(QObject *parent) : QObject(parent)
{
    networkDDBB = new NetworkDDBB(this);
    connect(networkDDBB, &NetworkDDBB::queryResponseReceived, this, &Database::handleQueryResponse);
}

void Database::setClient(Cliente *cli) { cliente = cli; }
void Database::setIpServerDDBB(const QString &ip)
{
    networkDDBB->setServerIp(ip);
}
void Database::setStringHandler(StringHandler *sh)
{
    if (stringHandler == sh)
        return;
    stringHandler = sh;
}

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

void Database::selectAllMap()
{
    QString query;
    QJsonArray args;

    query = "SELECT name FROM map;";

    networkDDBB->sendSqlCommand(query, targetToString(Target::SelectMaps), args);
}

void Database::getIdFromName(const QString &complete_name)
{
    QString query;
    QJsonArray args;
    auto [firstName_, lastName_] = splitNameSurname(complete_name);

    query = "SELECT Patient.name, Patient.lastname, Patient.id, Patient.age, Patient.weight, Patient.height, Patient.description, Patient.create_day, User.id AS user_id, User.name AS user_name, User.lastname AS user_lastname "
            "FROM Patient JOIN User ON Patient.id_user = User.id WHERE Patient.name = ? AND Patient.lastname = ?";
    args.append(firstName_);
    args.append(lastName_);

    networkDDBB->sendSqlCommand(query, targetToString(Target::GetIdPatient), args);
}

void Database::getMapInformation(const QString &map_name)
{
    QString query;
    QJsonArray args;

    query = "SELECT map.name, map.location, map.details, map.create_day, User.name AS user_name, User.lastname AS user_lastname "
            "FROM map JOIN user WHERE map.id_user = user.id AND map.name = ?;";

    args.append(map_name);

    networkDDBB->sendSqlCommand(query, targetToString(Target::GetMapInformation), args);
}

void Database::setMapInformation(const QString &username,const QString &map_name,  const QString &location, const QString &details)
{
    QString query;
    QJsonArray args;

    query = "INSERT INTO map (name, map_save, location, details, create_day, id_user) "
            "SELECT ?, 0, ?, ?, CURRENT_TIMESTAMP, id FROM user WHERE username = ? RETURNING name;";

    args.append(map_name.toLower());
    args.append(location);
    args.append(details);
    args.append(username.toLower());

    networkDDBB->sendSqlCommand(query, targetToString(Target::SetMapInformation), args);
}

void Database::mapCreateSave(bool save)
{
    QString query;
    QJsonArray args;

    if (save)
    {
        query = "UPDATE map SET map_save = 1 WHERE name = ?;";

        args.append(m_mapNameTemporal);

    }
    else
    {
        query = "DELETE FROM map WHERE name = ?;";

        args.append(m_mapNameTemporal);
    }

    networkDDBB->sendSqlCommand(query, targetToString(Target::SetMapInformation), args);
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
    case Target::SelectMaps:
        handleAllMaps(response);
        break;
    case Target::GetIdPatient:
        handleIdPatient(response);
        break;
    case Target::GetMapInformation:
        handleMapInfo(response);
        break;
    case Target::SetMapInformation:
        handleMapInformation(response);
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
            QJsonArray innerArray = result[0].toArray();

            if (!innerArray.isEmpty() && innerArray[0].isString())
            {
                setRole(innerArray[0].toString());
                setUsername(innerArray[1].toString());
                setPassLogin(true);
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
                QString firstName = (innerArray[0].toString());
                QString lastName = (innerArray[1].toString());
                int id = innerArray[2].toInt();
                int age = innerArray[3].toInt();
                double weight = innerArray[4].toDouble();
                double height = innerArray[5].toDouble();
                QString description = innerArray[6].toString();
                QString createDay = innerArray[7].toString();
                int userId = innerArray[8].toInt();
                QString name = innerArray[9].toString();
                QString lastname = innerArray[10].toString();

                if (id > 0)
                {
                    qDebug() << "First Name:" << firstName;
                    qDebug() << "Last Name:" << lastName;
                    qDebug() << "Patient ID:" << id;
                    qDebug() << "Age:" << age;
                    qDebug() << "Weight:" << weight;
                    qDebug() << "Height:" << height;
                    qDebug() << "Description:" << description;
                    qDebug() << "Create Day:" << createDay;
                    qDebug() << "User ID:" << userId;
                    qDebug() << "Name Doctor:" << name;
                    qDebug() << "Lastname Doctor:" << lastname;

                    // Store the values in appropriate member variables or emit signals
                    setIdPatient(id);
                    setPatient({{"first_name", firstName}, {"last_name", lastName}, {"id", id}, {"age", age}, {"weight", weight}, {"height", height}, {"description", description}, {"create_day", createDay}, {"id_user", userId}, {"user_name", name}, {"user_lastname", lastname}});
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
            qWarning() << "No valid data found in the response";
    }
    else
        qDebug() << "Error in query:" << response["message"].toString();
}


void Database::handleMapInfo(const QJsonObject &response)
{
    if (response["status"].toString() == "success")
    {
        QJsonArray result = response["result"].toArray();
        if (!result.isEmpty() && result[0].isArray())
        {
            QJsonArray innerArray = result[0].toArray();
            if (innerArray.size() >= 6) // Ensure all expected fields are present
            {
                QString map_name = (innerArray[0].toString());
                QString location = (innerArray[1].toString());
                QString details = (innerArray[2].toString());
                QString createDay = innerArray[3].toString();
                QString createByName = innerArray[4].toString() + " " +innerArray[5].toString() ;

                qDebug() << "Map Name:" << map_name;
                qDebug() << "Localización:" << location;
                qDebug() << "Description:" << details;
                qDebug() << "Create Day:" << createDay;
                qDebug() << "create By Name:" << createByName;
                setMapDescription({{"map_name", map_name}, {"location", location}, {"details", details}, {"create_day", createDay}, {"create_by_name", createByName}});
            }
            else
                qWarning() << "Unexpected response structure: insufficient fields";
        }
        else
            qWarning() << "No valid data found in the response";
    }
    else
        qDebug() << "Error in query:" << response["message"].toString();
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

void Database::handleAllMaps(const QJsonObject &response)
{
    if (response["status"].toString() == "success")
    {
        qDebug() << "handle all map";
        qDebug() << response;
        QJsonArray result = response["result"].toArray();
        updateMaps(result);
    }
    else
    {
        qDebug() << "Error in query:" << response["message"].toString();
    }
}

void Database::handleMapInformation(const QJsonObject &response)
{
    if (response["status"].toString() == "success")
    {
        QJsonArray result = response["result"].toArray();
        if (!result.isEmpty() && result[0].isArray())
        {
            QJsonArray innerArray = result[0].toArray();
            setMapNameTemporal(innerArray[0].toString());
        }
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
                QString fullName =  lastName  + ", " + firstName;
                patientList.append(fullName);
            }
        }
    }
    m_patients->setStringList(patientList);
    emit patientsChanged();
}

void extracted(QStringList &modelList) {
    for (const QString &item : modelList) {
        qDebug() << " - " << item;
    }
}
void Database::updateMaps(const QJsonArray &result) {
    if (!stringHandler->model()) {
        qWarning() << "Model is null!";
        return;
    }

    QStringList modelList =
        stringHandler->model()
                                ->stringList(); // Get the list of strings from the model
    QStringList mapsList;

    qDebug() << "Model List:";
    extracted(modelList);

    for (const QJsonValue &value : result) {
        if (value.isArray()) {
            QJsonArray patientArray = value.toArray();
            if (patientArray.size() == 1) {
                QString map_name = patientArray[0].toString();

                // Print the map_name being processed
                qDebug() << "Processing map_name:" << map_name;

                // Compare map_name with the model
                if (modelList.contains(map_name)) {
                    qDebug() << "map_name exists in modelList, appending:" << map_name;
                    mapsList.append(
                        map_name); // Append only if map_name exists in the model
                } else {
                    qDebug() << "map_name does not exist in modelList:" << map_name;
                }
            }
        }
    }

    m_maps->setStringList(mapsList); // Update the m_maps model
    emit mapsChanged();
}

QString Database::targetToString(Database::Target target)
{
    static const QMap<Target, QString> targetMap = {
                                                    {Target::Login, "Login"},
                                                    {Target::SignIn, "SignIn"},
                                                    {Target::Guest, "Guest"},
                                                    {Target::CheckUsername, "CheckUsername"},
                                                    {Target::AddPatient, "AddPatient"},
                                                    {Target::SelectMaps, "SelectMaps"},
                                                    {Target::SelectPatient, "SelectPatient"},
                                                    {Target::GetIdPatient, "GetIdPatient"},
                                                    {Target::GetMapInformation, "GetMapInformation"},
                                                    {Target::SetMapInformation, "SetMapInformation"},
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
                                                    {"SelectMaps", Target::SelectMaps},
                                                    {"GetIdPatient", Target::GetIdPatient},
                                                    {"GetMapInformation", Target::GetMapInformation},
                                                    {"SetMapInformation", Target::SetMapInformation},
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
    m_patients->setStringList(QStringList());
    m_idPatient = -1;
    m_patient.clear();

    m_mapNameTemporal = "";
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

QVariantMap Database::mapDescription() const
{
    return m_mapDescription;
}

void Database::setMapDescription(const QVariantMap &newMapDescription)
{
    if (m_mapDescription == newMapDescription)
        return;
    m_mapDescription = newMapDescription;
    emit mapDescriptionChanged();
}

QStringListModel *Database::maps() const
{
    return m_maps;
}

QString Database::mapNameTemporal() const
{
    return m_mapNameTemporal;
}

void Database::setMapNameTemporal(const QString &newMapNameTemporal)
{
    if (m_mapNameTemporal == newMapNameTemporal)
        return;
    m_mapNameTemporal = newMapNameTemporal;
    emit mapNameTemporalChanged();
}
