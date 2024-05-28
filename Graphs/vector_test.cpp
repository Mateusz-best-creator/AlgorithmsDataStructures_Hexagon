#include <iostream>
#include <string>
#include "vector.h"

using namespace std;

int main()
{
    Vector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    cout << vector.at(1) << endl;
    vector.push_back(1);
    vector.push_back(-10);
    cout << vector.at(3) << endl;

    Vector<Vector<char>> vector2(3);
    cout << vector2.size() << endl;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            vector2.at(i).push_back('h');

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << vector2[i][j] << " ";
        }
        cout << endl;
    }

    cout << vector.contain(-10) << endl;
}