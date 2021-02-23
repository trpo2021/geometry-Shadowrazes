#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>


using namespace std;
const int T = 8;

void triangle(string& s)
{
    double mas[T];
    string t = "";
    int k = 0;
    if (s.find("((") < s.find("))"))
    {
        for (int i = s.find("((") + 2; i <= s.find("))"); i++)
        {
            if (s[i] == 32 || s[i] == 44 || s[i] == 41) //пробел || запятая || скобка
            {
                if (t != "")
                {
                    mas[k] = stod(t);
                    k++;
                    if (k == T)
                    {
                        for (int i = 0; i < T; i++)
                            cout << mas[i] << " ";
                        cout << endl;
                        return;
                    }
                }
                t = "";
                continue;
            }
            if ((s[i] < 47 || s[i]>58) && (s[i] != 45 && s[i] != 46))
            {
                cout << "error" << endl;
                return;
            }
            t += s[i];
        }
    }
}

void error(int code, int column)
{
    for (int i = 0; i < column; i++) {
        cout << " ";
    }
    cout << "^" << endl;

    switch (code) {
    case 1:
        cout << "Error at column " << column << ": expected 'triangle'; code = " << code << endl;
        break;
    case 2:
        cout << "Error at column " << column << ": expected '<double>'; code = " << code << endl;
        break;
    case 3:
        cout << "Error at column " << column << ": expected ')'; code = " << code << endl;
        break;
    case 4:
        cout << "Error at column " << column << ": unexpected token; code = " << code << endl;
        break;
    case 5:
        cout << "Error at column " << column << ": expected '('; code = " << code << endl;
        break;
    }
}

int main()
{
    setlocale(LC_CTYPE, "RUSSIAN");
    vector<string> list;
    string s;
    int i;
    cout << "Задайте фигуры" << endl;
    while (getline(cin, s)) {
        if (s == "")
        {
            break;
        }
        list.push_back(s);
    }
    for (i = 0; i < list.size(); i++) 
    {
        cout << list[i] << endl;
    }
}
