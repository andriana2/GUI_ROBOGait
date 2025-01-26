#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <memory>
#include <stdexcept>
#include <filesystem>
#include <fstream>

#include "header.h"

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

std::string toBase64(const char *data, size_t length);

std::string replaceSpaces(const std::string &name);

std::string restoreSpaces(const std::string &name);

std::vector<std::string> getMapName(std::string const &path);

void getImageSize(std::string const &path, int &width_output, int &height_output);

std::vector<std::string> splitCommand(const std::string& command);

#endif // UTILS_H