#include "../include/StringHandler.h"
#include <iostream>
#include <vector>
#include <sstream>

StringHandler::StringHandler(QObject *parent)
    : QObject(parent)
{
}

QString StringHandler::inputString() const
{
    return m_inputString;
}

void StringHandler::setInputString(const QString &newString)
{
    if (m_inputString != newString) {
        m_inputString = newString;
        emit inputStringChanged();
    }
}

QString StringHandler::resultString() const
{
    return m_resultString;
}

void StringHandler::compareWith(const QString &compareString)
{
    if (m_inputString == compareString) {
        m_resultString = "Strings are equal!";
    } else {
        m_resultString = "Strings are different.";
    }
    emit resultStringChanged();
}

void StringHandler::sendFromTerminal(const QString &text)
{
    m_resultString = "From terminal: " + text;
    emit resultStringChanged();
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
    return true;
}
