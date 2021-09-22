/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-20 22:56:44
 * @LastEditTime: 2021-09-21 00:20:58
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/11.使用类/Clock类/main.cpp
 * @Description: 
 ************************************************/
#include <iostream>
#include "clock.h"
using namespace std;
int main()
{
    Clock c1(20, 10);
    Clock c2 = Clock(2, 55);
    // c1.show();
    // c2.show();
    cout << "address of c1 is " << &c1 << endl;
    cout << "address of c2 is " << &c2 << endl;

    c1.AddM(30);
    Clock c3 = c1 + c2;
    // c3.show();
    cout << "address of c3 is " << &c3 << endl;

    Clock *c4 = c1.Add(c2);
    // c4.show();
    cout << "address of c4 is " << c4 << endl;

    // hour = 20 minutes = 10
    // hour = 2 minutes = 55
    // hour = 23 minutes = 35
    // hour = 23 minutes = 35
}