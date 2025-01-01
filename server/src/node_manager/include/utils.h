#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <memory>
#include <stdexcept>

#include "header.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string headerToString(Header header);
Header stringToHeader(const std::string &str);

std::string targetToString(Target target);
Target stringToTarget(const std::string &str);

// void getValuePositionJoystick(const std::string& input, float &linear, float &angular);

void pri1(std::string const &msg);

std::vector<std::string> executeCommand(const std::string &command);

std::vector<std::string> splitJson(const std::string &input);

json qtJsonToNlohmannJson(const QJsonObject& qt_json_obj);

std::string toHex(const char *data, std::size_t length);

// std::string toBase64(const char* data, size_t length);


#endif // UTILS_H