#include <cmath>
#include <cstdlib>
#include <iostream>
#include <libgeometry/calculations.h>
#include <libgeometry/checks.h>
#include <string>
#include <vector>

using namespace std;

int main()
{
    setlocale(LC_CTYPE, "RUSSIAN");
    vector<pair<string, vector<double>>> flist;
    vector<string> str;
    string s;

    pair<double, double> start;
    pair<double, double> close;
    vector<double> leng;

    int i, j;
    cout << "Задайте фигуры" << endl;
    while (getline(cin, s)) {
        if (s == "") {
            break;
        }

        vector<double> coord;
        string name = figureName(s);
        if (name == "error")
            continue;
        pair<string, vector<double>> figure;

        if (name == "triangle") {
            coord = setTriangle(s);
        } else if (name == "circle") {
            coord = setCircle(s);
        } else {
            error(1, 0);
        }

        if (coord.size() > 0) {
            str.push_back(s);
            figure.first = name;
            figure.second = coord;
            flist.push_back(figure);
        }
    }

    vector<vector<int>> inter;
    inter.resize(flist.size());

    int z = flist.size();
    inter = intersects(flist, inter);
    for (i = 0; i < z; i++) {
        leng.clear();
        double perimeter = 0, square = 0;
        if (flist[i].first == "triangle") {
            for (j = 0; j < 6; j += 2) {
                start.first = flist[i].second[j];
                start.second = flist[i].second[j + 1];
                close.first = flist[i].second[j + 2];
                close.second = flist[i].second[j + 3];
                leng.push_back(lenLine(start, close));
            }
            for (j = 0; j < 3; j++)
                perimeter += leng[j];
            square = sqrTriangle(perimeter / 2, leng);
        } else if (flist[i].first == "circle") {
            perimeter = lenCircle(flist[i].second[2]);
            square = sqrCircle(flist[i].second[2]);
        }
        cout << i + 1 << ". " << str[i] << endl;
        cout << "    perimeter = " << perimeter << endl;
        cout << "    area = " << square << endl;
        cout << "    intersects:" << endl;
        int m = inter[i].size();
        if (m > 0) {
            for (j = 0; j < m; j++) {
                cout << "      " << inter[i][j] + 1 << ". "
                     << flist[inter[i][j]].first << endl;
            }
            cout << endl;
        } else
            cout << "       none" << endl << endl;
    }
    system("pause");
}
