#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include "header.h"
#include <sstream>

std::string get_info_message(Info_Message const &info);
Info_Message get_info_message_enum(std::string const &info);

void getValuePositionJoystick(const std::string& input, float &linear, float &angular);

void pri1(std::string const &msg);

#endif // UTILS_H