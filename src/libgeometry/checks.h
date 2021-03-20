#ifndef CHECKS_H
#define CHECKS_H

#include <string>
#include <vector>
#include "calculations.h"

using namespace std;

void error(int code, int column);
vector<double> clearVec(vector<double>& coord);
bool odz(int condition);
bool odzBeforeAfter(int condition);
pair<bool, int> afterBracket(string& s, int i);
pair<bool, int> btwBrackets(string& s, int start, int end);
string figureName(string& s);
pair<bool, int> commaBeforeAfter(string& s, int start, int end);
pair<int, int> commaBtw(string& s, int start, int end, int k);
vector<double> setCircle(string& s);
vector<double> setTriangle(string& s);

#endif // !CHECKS_H