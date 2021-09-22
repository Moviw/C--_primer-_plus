/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-19 14:06:47
 * @LastEditTime: 2021-09-19 14:09:42
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/9.内存模型和名称空间/static关键字/file1.cpp
 * @Description: 
 ************************************************/
// twofile2 cpp -- variables with internal and external linkage
#include <iostream>
extern int tom;       //引用外部的tom外部变量
static int dick = 10; //自定义一个dick变量,他只在该文件内部可见
int harry = 200;      //定义一个harry外部变量

using namespace std;
void remote_access()
{
    cout << "remote access() reports the following addresses: \n";
    cout << "&tom = " << &tom << endl
         << " &dick= "
         << &dick << endl;
    cout << " &harry = " << &harry << endl;
}