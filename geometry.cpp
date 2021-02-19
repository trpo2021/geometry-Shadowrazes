#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>


using namespace std;

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
