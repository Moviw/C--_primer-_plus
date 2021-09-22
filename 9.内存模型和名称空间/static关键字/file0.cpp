/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-19 14:10:29
 * @LastEditTime: 2021-09-19 14:13:47
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/9.内存模型和名称空间/static关键字/file0.cpp
 * @Description: 
 ************************************************/
#include <iostream>
int tom = 3;
int dick = 30;
static int harry = 300;

void remote_access();
using namespace std;
int main()
{

    cout << "main() reports the following addresses:\n";
    cout << "&tom = " << &tom << endl;
    cout << "&dick = " << &dick << endl;
    cout << "&harry = " << &harry << endl;
    remote_access();
}