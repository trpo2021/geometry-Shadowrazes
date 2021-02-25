#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>


using namespace std;

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
        cout << "Error at column " << column << ": expected '))'; code = " << code << endl;
        break;
    case 4:
        cout << "Error at column " << column << ": unexpected token; code = " << code << endl;
        break;
    case 5:
        cout << "Error at column " << column << ": expected '(('; code = " << code << endl;
        break;
    }
}

bool odz(int condition)
{
    return ((condition < 48) || (condition > 57)) && (condition != 32) && (condition != 44) && (condition != 46) && (condition != 45);
}

pair<int, int> afterBracket(string& s, int i)
{
    int leng = s.length(), start = i;
    pair<int, int> br(0, 0);
    if (i == leng)
        return br;
    for (i; i < leng; i++) 
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

string figureName(string& s)
{
    int bracket = s.find("((");
    string name = "";
    int z = s.length();
    
    for (int i = 0; i < z; i++)
    {
        s[i] = tolower(s[i]);               //приводим к одному регистру(строчный)
    }
    name = s.substr(0, bracket);
    return name;
}

vector<double> setTriangle(string& s)
{
    vector<double> coord;
    string temp = s, tempCoord = "", item;
    int bracket = temp.find("((");
    int endBracket = temp.find("))");
    int k = 0, column = 10;

    if (endBracket == -1)
    {
        error(3, temp.length() - 1);
        coord.clear();
        return coord;
    }
    
    tempCoord = temp.substr(bracket);
    if ((tempCoord[0] == '(') && (tempCoord[1] == '('))
    {
        tempCoord.erase(0, 2);
    }
    else
    {
        error(5, 8);
        coord.clear();
        return coord;
    }
    int z = tempCoord.length();
    for (int i = 0; i < z; i++)
    {

        item = "";
        if (k < 7)
        {
            if (((tempCoord[i] < 48) || (tempCoord[i] > 57)) && (tempCoord[i] != 32) && (tempCoord[i] != 44) && (tempCoord[i] != 46)) //ОДЗ
            {
                error(2, column);
                coord.clear();
                return coord;
            }
            if (tempCoord[i] == ' ')
            {
                item += tempCoord.substr(0, i);
                coord.push_back(stod(item));
                tempCoord.erase(0, i + 1);
                z = tempCoord.length();
                i = 0;
                k++;
                column++;
            }
            if (tempCoord[i] == ',')
            {
                item += tempCoord.substr(0, i);
                coord.push_back(stod(item));
                tempCoord.erase(0, i + 2);      //удаляем запятую и пробел за ней
                z = tempCoord.length();
                i = 0;
                k++;
                column += 2;
            }
        }
        else 
        {
            item = tempCoord.substr(0, tempCoord.find("))"));
            coord.push_back(stod(item));
            column += tempCoord.find("))") + 2;
            tempCoord.erase(0, tempCoord.find("))") + 2);
            z = tempCoord.length();
            for (int j = 0; j < z; j++)
            {
                if (tempCoord[j] != 32 )
                {
                    error(4, s.find("))") + (j+1));
                    coord.clear();
                    return coord;
                }
            }
        }
        column++;
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
        pair<string, vector<double>> figure;

        if (name == "triangle")
        {
            coord = setTriangle(s);
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