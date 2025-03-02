#ifndef UTILS_DATABASE_H
#define UTILS_DATABASE_H

#include <string>

std::string quote(const std::string &value);
std::string quote(int value);
std::string quote(double value);

#endif // UTILS_DATABASE_H
