/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-18 22:41:37
 * @LastEditTime: 2021-09-18 22:49:42
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/file1.cpp
 * @Description: 
 ************************************************/
#include <iostream> //加尖括号是在系统目录中找
#include <cmath>
#include "coordin.h" //加双引号是在当前工程目录中找
using namespace std;
int main()
{
    rect rplace;
    polar pplace;

    cout << "Enter the x and y values ";

    while (cin >> rplace.x >> rplace.y)
    {
        pplace = rect_to_polar(rplace);
        show_polar(pplace);
        cout << "Next two number (q to quit)";
    }
}