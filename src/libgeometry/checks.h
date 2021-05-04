#ifndef CHECKS_H
#define CHECKS_H

#include <libgeometry/calculations.h>
#include <string>
#include <vector>

void error(int code, int column);
std::vector<double> clearVec(std::vector<double>& coord);
bool odz(int condition);
bool odzBeforeAfter(int condition);
std::pair<bool, int> afterBracket(std::string& s, int i);
std::pair<bool, int> btwBrackets(std::string& s, int start, int end);
std::string figureName(std::string& s);
std::pair<bool, int> commaBeforeAfter(std::string& s, int start, int end);
std::pair<int, int> commaBtw(std::string& s, int start, int end, int k);
std::vector<double> setCircle(std::string& s);
std::vector<double> setTriangle(std::string& s);

#endif // !CHECKS_H
