#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;
//for rebase
void error(int code, int column)
{
    for (int i = 0; i < column; i++)
    {
        cout << " ";
    }
    cout << "^" << endl;

    switch (code)
    {
    case 1:
        cout << "Error at column " << column << ": 'circle', 'triangle' or 'polygon'; code = " << code << endl;
        break;
    case 2:
        cout << "Error at column " << column << ": expected '<double>'; code = " << code << endl;
        break;
    case 3:
        cout << "Error at column " << column << ": expected ')' or '))'; code = " << code << endl;
        break;
    case 4:
        cout << "Error at column " << column << ": unexpected token; code = " << code << endl;
        break;
    case 5:
        cout << "Error at column " << column << ": expected '(('; code = " << code << endl;
        break;
    case 6:
        cout << "Error at column " << column << ": expected ','; code = " << code << endl;
        break;
    case 7:
        cout << "Error at column " << column << ": too many tokens; code = " << code << endl;
        break;
    case 8:
        cout << "Error at column " << column << ": expected '(' or '(('; code = " << code << endl;
        break;
    case 9:
        cout << "Error: this triangle is degenerate" << endl;          
        break;
    case 10:
        cout << "Error: the radius cannot be less than or equal to zero" << endl; 
        break;
    case 11:
        cout << "Error: too few tokens" << endl;
        break;
    }
}

vector <double> clearVec(vector <double>& coord)
{
    coord.clear();
    return(coord);
}

bool odz(int condition)  // общее ОДЗ
{
    return ((condition < 48) || (condition > 57)) && (condition != 32) && (condition != 44) && (condition != 46) && (condition != 45);
}

bool odzBeforeAfter(int condition)   // ОДЗ для функции поиска лишних запятых перед 1м и после последнего токена
{
    return ((condition < 48) || (condition > 57)) && (condition != 32) && (condition != 46) && (condition != 45);
}

pair <bool, int> afterBracket(string& s, int i)  // проверка лишних токенов после закр. скобки/удаление пробелов за ней
{
    int leng = s.length(), start = i;
    pair <bool, int> br (0, 0);
    if (i == leng) 
        return br;
    for (i = i; i < leng; i++)
    {
        if (s[i] != 32)
        {
            br.first = 1;
            br.second = i;
            return br;
        }
    }
    s.erase(start);
    return br;
}

pair <bool, int> btwBrackets(string& s, int start, int end)   // проверка ОДЗ между скобками
{
    pair <bool, int> btw(0, 0);
    int i;
    for (i = start; i < end; i++)
    {
        if (odz(s[i]))
        {
            btw.first = 1;
            btw.second = i;
            return btw;
        }
    }
    return btw;
}

string figureName(string& s)        // определение названия фигуры
{
    int bracket = s.find("(");
    string name = "";
    int z = s.length();
    if (bracket == -1)
    {
        for (int i = 0; i < z; i++)
        {
            if ((s[i] > 47) && (s[i] < 58))
            {
                error(8, i - 1);
                return name = "error";
            }
        }
    }

    for (int i = 0; i < z; i++)
    {
        s[i] = tolower(s[i]);               
    }
    name = s.substr(0, bracket);
    return name;
}

pair <bool, int> commaBeforeAfter(string& s, int start, int end)  // проверка лишних запятых до 1го и после последнего токена
{
    int i, j = start;
    pair <bool, int> data(0, 0);
    while (odzBeforeAfter(s[j]) || s[j] == ' ')
        j++;
    for (i = start; i < j; i++)
    {
        if (odzBeforeAfter(s[i]))
        {
            data.first = 1;
            data.second = i;
            return data;
        }
    }
    j = end;
    while (odzBeforeAfter(s[j]) || s[j] == ' ')  
        j--;
    for (i = end; i > j; i--)
    {
        if (odzBeforeAfter(s[i]))
        {
            data.first = 1;
            data.second = i;
            return data;
        }
    }
    return data;
}

pair <int, int> commaBtw(string& s, int start, int end, int k)  // проверка лишних запятых между токенами
{
    int i, tmp = start, j;
    pair <int, int> data(0, 0);
    for (j = 0; j < 2; j++)
    {
        for (i = tmp; i < end; i++)
            if (s[i] != ' ')
                break;
        switch (k % 2)
        {
        case 0:
            if ((s[i] == ',' || (s[i] == ')' && i == end)) && j == 0)
                break;
            else if (s[i] != ',' && j == 1)
                return data;
            else if (j == 1)
            {
                data.first = 2;
                data.second = i;
                return data;
            }
            else
            {
                data.first = 1;
                data.second = i;
                return data;
            }
        case 1:
            if (s[i] != ',')
                return data;
            else break;
        }
        if (k % 2 == 1) break;
        if (s[i] == ')' && i == end) return data;
        tmp = i + 1;
    }
    data.first = 1;
    data.second = i;
    return data;
}

vector <double> sqrSum(double a, double b)
{
    vector <double> sq;
    sq.push_back(a*a);
    sq.push_back(2*a*b);
    sq.push_back(b*b);
    return sq;
}

vector <double> sqrEq(vector <double> coef)
{
    vector <double> radical(0);
    struct abc
    {
        double a;
        double b;
        double c;
    };
    abc arg = {coef[0], coef[1], coef[2]};
    double d = arg.b * arg.b - 4 * arg.a * arg.c;
    if (d < 0) return radical;
    else if (d > 0)
    {
        radical.push_back((-arg.b + sqrt(d)) / (2 * arg.a));
        radical.push_back((-arg.b - sqrt(d)) / (2 * arg.a));
        return radical;
    }
    else if (d == 0)
    {
        radical.push_back(-arg.b / (2 * arg.a));
        return radical;
    }
    else return radical;
}

double lenCircle(double r) 
{
    return 2 * PI * r;
}

double sqrCircle(double r) 
{
    return PI * pow(r, 2);
}

double sqrTriangle(double p, vector<double> lines) 
{
    double half = p;
    for (int i = 0; i < 3; i++)
    {
        half *= p - lines[i];
    }
    return sqrt(half);
}

pair <double, double> vectCoord(pair <double, double> start, pair <double, double> close)
{
    pair <double, double> vect;
    vect.first = close.first - start.first;
    vect.second = close.second - start.second;
    return vect;
}

vector <double> setCircle(string& s)
{
    vector<double> coord;
    string item;
    int bracket = s.find("(");
    int endBracket = s.find(")");
    int k = 0;
    pair <bool, int> uni;

    if (endBracket == -1)
    {
        error(3, s.length());
        return clearVec(coord);
    }

    uni = afterBracket(s, endBracket + 1);
    if (uni.first)
    {
        error(4, uni.second);
        return clearVec(coord);
    }

    uni = btwBrackets(s, bracket + 1, endBracket);
    if (uni.first)
    {
        error(2, uni.second);
        return clearVec(coord);
    }

    uni = commaBeforeAfter(s, bracket + 1, endBracket - 1);
    if (uni.first)
    {
        error(4, uni.second);
        return clearVec(coord);
    }

    int i;
    for (i = bracket + 1; i <= endBracket; i++)
    {
        if ((s[i] == ' ' || s[i] == ')' || s[i] == ',') && item != "")
        {
            coord.push_back(stod(item));
            k++;
            if (k > 3)
            {
                error(7, i - item.length());
                return clearVec(coord);
            }
            item = "";
            if (k < 3)
            {
                uni = commaBtw(s, i, endBracket, k);
                switch (k % 2)
                {
                case 0:
                    if (uni.first == 1)
                    {
                        error(6, i);
                        return clearVec(coord);
                    }
                    break;
                case 1:
                    if (uni.first == 1)
                    {
                        error(4, uni.second);
                        return clearVec(coord);
                    }
                    break;
                }
            }
        }
        if (s[i] != ' ' && s[i] != ',')
        {
            item += s[i];
        }
    }
    return coord;
}

vector<double> setTriangle(string& s)   // выделение координат треугольника
{
    vector<double> coord;
    string item;
    int bracket = s.find("((");
    int endBracket = s.find("))");
    int k = 0;
    pair <int, int> uni;

    if (bracket == -1)
    {
        error(5, 8);
        return clearVec(coord);
    }

    if (endBracket == -1)
    {
        error(3, s.length());
        return clearVec(coord);
    }

    uni = afterBracket(s, endBracket + 2);
    if (uni.first)
    {
        error(4, uni.second);
        return clearVec(coord);
    }

    uni = btwBrackets(s, bracket + 2, endBracket);
    if (uni.first)
    {
        error(2, uni.second);
        return clearVec(coord);
    }

    uni = commaBeforeAfter(s, bracket + 2, endBracket - 1);
    if (uni.first)
    {
        error(4, uni.second);
        return clearVec(coord);
    }

    int i;
    for (i = bracket + 2; i <= endBracket; i++)
    {
        if ((s[i] == ' ' || s[i] == ')' || s[i] == ',') && item != "")
        {
            coord.push_back(stod(item));
            k++;
            if (k > 8)
            {
                error(7, i - item.length());
                return clearVec(coord);
            }
            item = "";
            if (k < 8)
            {
                uni = commaBtw(s, i, endBracket, k);
                switch (k % 2)
                {
                case 0:
                    if (uni.first == 1)
                    {
                        error(6, i);
                        return clearVec(coord);
                    }
                    else if (uni.first == 2)
                    {
                        error(4, uni.second);
                        return clearVec(coord);
                    }
                    break;
                case 1:
                    if (uni.first == 1)
                    {
                        error(4, uni.second);
                        return clearVec(coord);
                    }
                    break;
                }
            }
        }
        if (s[i] != ' ' && s[i] != ',')
        {
            item += s[i];
        }
    }
    return coord;
}

int main()
{
    setlocale(LC_CTYPE, "RUSSIAN");
    vector<pair<string, vector<double>>> flist;
    string s;
    int i, j;
    cout << "Задайте фигуры" << endl;
    while (getline(cin, s))
    {
        if (s == "")
        {
            break;
        }

        vector<double> coord;
        string name = figureName(s);
        if (name == "error") continue;
        pair<string, vector<double>> figure;

        if (name == "triangle")
        {
            coord = setTriangle(s);
        }
        else if(name == "circle")
            {
                coord = setCircle(s);
            }
            else
            {
                error(1, 0);
            }

        if (coord.size() > 0)
        {
            figure.first = name;
            figure.second = coord;
            flist.push_back(figure);
        }
    }
    int z = flist.size();
    for (i = 0; i < z; i++)
    {
        cout << i + 1 << ". " << flist[i].first << ": ";
        int x = flist[i].second.size();
        for (j = 0; j < x; j++)
        {
            cout << flist[i].second[j] << " ";
        }
        cout << endl;
    }
}