#ifndef COSC_1337_USERINPUT_H
#define COSC_1337_USERINPUT_H

#include "helperfunctions.h"

#include <utility>
#include <vector>
#include <string>

double  promptNum(const char* reprompt, const double& defaultValue, const int& rangeMax=100, const int& rangeMin=0);
bool promptYN(const std::string& prompt);
auto findFiles() -> std::pair<std::vector<std::string>, int>;

#endif // COSC_1337_USERINPUT_H
