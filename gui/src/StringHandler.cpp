#include "../include/StringHandler.h"
#include "include/utils.h"
#include <iostream>
#include <vector>
#include <sstream>

StringHandler::StringHandler(QObject *parent) : QObject(parent)
{
    m_currentMove = Stop;
}


bool StringHandler::isInSameNetwork(const QString &ip1, const std::string& subnetMask) {
    if (ip1.isEmpty() || ip1 == "")
    {
        return 0;
    }
    std::string ip1_ = ip1.toStdString();
    for (char ch : ip1_) {
        if (!(std::isdigit(ch) || ch == '.')) {
            return false;
        }
    }

    std::string ip2 = obtenerIP();
    std::cout << ip2 << std::endl;
    auto ipToInt = [](const std::string& ip) -> std::vector<int> {
        std::vector<int> parts;
        std::stringstream ss(ip);
        std::string segment;
        while (std::getline(ss, segment, '.')) {
            parts.push_back(std::stoi(segment));
        }
        return parts;
    };

    std::vector<int> ip1Parts = ipToInt(ip1_);
    std::vector<int> ip2Parts = ipToInt(ip2);
    std::vector<int> maskParts = ipToInt(subnetMask);

    for (int i = 0; i < 4; ++i) {
        if ((ip1Parts[i] & maskParts[i]) != (ip2Parts[i] & maskParts[i])) {
            return false;
        }
    }
    // ip a la que nos conectamos
    // cliente.connectToServer(ip1, 8080);
    // cliente.connectToServer("127.0.0.1", 8080);
    cliente.setIp(ip1);
    //--------------
    return true;
}

void StringHandler::setCurrentMove(StringHandler::Move newCurrentMove)
{
    if (m_currentMove == newCurrentMove)
        return;
    m_currentMove = newCurrentMove;
    emit currentMoveChanged();
    qDebug() << "Movimiento seleccionado:" << moveToString(newCurrentMove);
    //--------enviar mensaje-------------//
    cliente.sendMessage(moveToString(newCurrentMove));
}


QString StringHandler::moveToString(StringHandler::Move move) const {
    switch (move) {
    case Recto: return "Recto";
    case Atras: return "Atras";
    case Giro_Izquierda: return "Giro_Izquierda";
    case Giro_Derecha: return "Giro_Derecha";
    case Mas_Rapido: return "Mas_Rapido";
    case Mas_Lento: return "Mas_Lento";
    case Stop: return "Stop";
    default: return "Desconocido";
    }
}

StringHandler::Move StringHandler::stringToMove(const QString &move) const {
    if (move == "Recto") return Recto;
    if (move == "Atras") return Atras;
    if (move == "Giro_Izquierda") return Giro_Izquierda;
    if (move == "Giro_Derecha") return Giro_Derecha;
    if (move == "Mas_Rapido") return Mas_Rapido;
    if (move == "Mas_Lento") return Mas_Lento;
    if (move == "Stop") return Stop;
    return Stop; // Valor predeterminado
}

