#ifndef CLIENTE_H
#define CLIENTE_H

#include "database.h"
#include "StringHandler.h"
#include "MapInfo.h"

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTimer>

#include <QJsonDocument>
#include <QJsonObject>

#include <QImage>

class StringHandler;
class MapInfo;
class Database;

class Cliente : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ipRobot READ ipRobot WRITE setIpRobot NOTIFY ipRobotChanged FINAL)
public:
    // Constructor and Destructor
    Cliente(int port_);
    ~Cliente();
    void disconnectRobot();

    // Connection different class methods
    void setStringHandler(StringHandler *sh);
    void setMapInfo(MapInfo *sh);
    void setDatabase(Database *sh);

    // Core functionality
    void sendMessage(const QJsonDocument &jsone); // Sends a JSON message to the server
    void parseJsonToQList(const QJsonObject &jsonObj); // Parses a QJsonObject into an internal list
    void answerUdp(); // Send ACK
    void startSearchUdp(); // Initiates the UDP discovery broadcast

    // Connection properties
    QTcpSocket *socket; // TCP socket used for server communication
    QUdpSocket udpSocket; // UDP socket used for broadcasting and receiving messages
    QHostAddress servidor; // Stores the discovered server address

    QString ipRobot() const;
    void setIpRobot(const QString &newIpRobot);

    void clear();

public slots:
    void closeConnection(); // Gracefully closes the TCP connection
    void connect2host(const QString hostAddress); // Initiates a connection to the specified host

signals:
    void statusChanged(bool); // Emitted when connection status changes

    void ipRobotChanged();

private slots:
    void onReadyRead(); // Handles incoming TCP data
    void processJson(const QJsonDocument &json); // Processes received JSON messages
    void connected(); // Called when TCP connection is successfully established
    void connectionTimeout(); // Handles connection timeout scenario
    void onErrorOccurred(QAbstractSocket::SocketError error); // Handles socket errors

private:
    // JSON Handling
    QJsonDocument jsonDoc; // Holds the most recently received JSON document

    // Mapping
    bool maping; // Status flag related to mapping

    // Connection Configuration
    QString host; // Host address to connect to
    int port_udp_tcp; // TCP and UDP port
    bool status; // Connection status
    QTimer *timeoutTimer; // Timer used for connection timeout

    // External Handlers
    Database *database; // Pointer to Database handler
    StringHandler *stringHandler; // Pointer to StringHandler
    MapInfo *mapInfo; // Pointer to MapInfo
    QString m_ipRobot;
};

#endif // CLIENTE_H
