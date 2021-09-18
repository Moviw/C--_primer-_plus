/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-18 22:41:52
 * @LastEditTime: 2021-09-18 22:57:18
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/file2.cpp
 * @Description: 
 ************************************************/
#include <iostream> //加尖括号是在系统目录中找
#include <cmath>
#include "coordin.h" //加双引号是在当前工程目录中找

using namespace std;

polar rect_to_polar(rect xypos)
{
    polar answer;

    answer.distance = sqrt(pow(xypos.x, 2) + pow(xypos.y, 2));
    answer.angle = atan2(xypos.y, xypos.x);
    return answer;
}

void show_polar(polar dapos)
{
    const double Rad_to_deg = 57.29577951;

    cout << "Distance = " << dapos.distance << endl;
    cout << "Angle = " << dapos.angle * Rad_to_deg << " degree" << endl;
}