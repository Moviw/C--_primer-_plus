/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-19 13:29:58
 * @LastEditTime: 2021-09-19 13:55:15
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/9.内存模型和名称空间/EXTERN关键字/support.cpp
 * @Description: 
 ************************************************/
#include <iostream>
#include "support.h"
using namespace std;

extern double warming; //引用一个别的文件的名为warming的外部变量

void update(double x)
{
    warming += x;
    cout << "Updating warming to " << warming << " degrees" << endl;
}
void local()
{
    double warming = 0.8;
    cout << "Local warming = " << warming << " degrees" << endl;
    cout << "But global warming = " << ::warming << "degrees " << endl;
}