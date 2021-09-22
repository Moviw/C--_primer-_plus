/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-19 13:28:28
 * @LastEditTime: 2021-09-19 14:40:58
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/9.内存模型和名称空间/EXTERN关键字/external.cpp
 * @Description: 
 ************************************************/
#include <iostream>
#include "support.h"
using namespace std;

/*extern 可写可不写*/ double warming = 0.3; //声明一个外部变量
int main()
{
    cout << "Global warming is " << warming << " degrees" << endl;
    update(0.1);
    cout << "Global warming is " << warming << " degrees" << endl;
    local();
    cout << "Global warming is " << warming << " degrees" << endl;
    return 0;
}