﻿#include <iostream>
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
    case 6:
        cout << "Error at column " << column << ": expected ','; code = " << code << endl;
        break;
    case 7:
        cout << "Error at column " << column << ": too many tokens; code = " << code << endl;
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

pair<int, int> btwBrackets(string& s, int start, int end)
{
    pair<int, int> btw(0, 0);
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
    string item;
    int bracket = s.find("((");
    int endBracket = s.find("))");
    int k = 0;
    pair<int, int> uni;
    pair<bool, int> t;

    if (bracket == -1) 
    {
        error(5, 8);
        coord.clear();
        return coord;
    }

    if (endBracket == -1) 
    {
        error(3, s.length());
        coord.clear();
        return coord;
    }

    uni = afterBracket(s, endBracket + 2);
    if (uni.first) 
    {
        error(4, uni.second);
        coord.clear();
        return coord;
    }

    uni = btwBrackets(s, bracket + 2, endBracket);
    if (uni.first) 
    {
        error(2, uni.second);
        coord.clear();
        return coord;
    }

    int i;
    for (i = bracket + 2; i <= endBracket; i++) 
    {
        if ((s[i] == ' ' || s[i] == ')' || s[i] == ',') && item != "") 
        {
            coord.push_back(stod(item));
            k++;
            item = "";
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
    system("pause");
}