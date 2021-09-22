/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-21 01:53:45
 * @LastEditTime: 2021-09-21 13:06:10
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/11.使用类/Vector类/main.cpp
 * @Description: 
 ************************************************/
#include <iostream>
#include "vector.h"
#include <ctime>
#include <cstdlib>

#include <fstream>
using namespace std;
int main()
{
    double target;
    double length;
    int step = 0;
    Vector v(0, 0);

    cout << "Enter target distance (q to quit): ";
    while (cin >> target)
    {
        srand(time(NULL));
        cout << "Enter step length: ";
        if (!(cin >> length))
        {
            cout << "error! terminating ....";
            break;
        }
        else
        {
            cout << "begin to compute.." << endl;
            while (v.magval() < target)
            {
                double direction = rand() % 360;
                v = Vector(length, direction, Vector::POL) + v;
                //v = v + Vector(length, direction, Vector::POL);  这种不行
                step++;
            }
        }
        cout << "After " << step << " steps the subject has the following loaction:\n";
        cout << v;
        v.pol_mode();
        cout << "or\n"
             << v;
        cout << "Average outward distance per step = " << v.magval() / step << endl;
        step = 0;
        v.reset(0, 0);
        cout << endl;
        cout << "Enter target distance (q to quit): ";
    }
    cout << "Bye\n";
}