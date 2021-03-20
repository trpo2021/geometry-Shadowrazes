#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <string>
#include <vector>

using namespace std;

vector <double> sqrSum(double a, double b);
vector <double> sqrEq(vector <double> coef);
double lenCircle(double r);
double sqrCircle(double r);
double sqrTriangle(double p, vector<double> lines);
pair <double, double> vectCoord(pair <double, double> start, pair <double, double> close);
double lenLine(pair <double, double> start, pair <double, double> close);
bool cirTOcir(vector <double> cirf, vector <double> cirs);
bool trTOcir(vector <double> tr, vector <double> cir);
bool trTOtr(vector <double> trf, vector <double> trs);
vector <vector<int>> intersects(vector<pair<string, vector<double>>> flist, vector <vector<int>> inter);

#endif