#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <string>
#include <vector>

std::vector<double> sqrSum(double a, double b);
std::vector<double> sqrEq(std::vector<double> coef);
double lenCircle(double r);
double sqrCircle(double r);
double sqrTriangle(double p, std::vector<double> lines);
std::pair <double, double> vectCoord(std::pair <double, double> start, std::pair <double, double> close);
double lenLine(std::pair<double, double> start, std::pair<double, double> close);
bool cirTOcir(std::vector<double> cirf, std::vector<double> cirs);
bool trTOcir(std::vector<double> tr, std::vector<double> cir);
bool trTOtr(std::vector<double> trf, std::vector<double> trs);
std::vector <std::vector<int>> intersects(std::vector<std::pair<string, std::vector<double>>> flist, std::vector <std::vector<int>> inter);

#endif