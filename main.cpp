/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-20 23:45:14
 * @LastEditTime: 2021-09-21 13:52:00
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/main.cpp
 * @Description: 
 ************************************************/
#include <iostream>
using namespace std;
class num
{
    int n;

public:
    num() { n = 0; }
    num(int n) { this->n = n; }
    void show() { cout << "n = " << n << endl; }
    operator int() { return n; }
};
int main()
{
    int *p = new int[10];
    for (int i = 0; i < 10; i++)
    {
        p[i] = i;
    }
    // cout << p << endl;
    // int *fp = p;
    // cout << fp << endl;
    // cout << *fp << endl;
    // delete[] p;
    // cout << fp << endl;
    // cout << *fp << endl;
    cout << p << endl;
    int *fp = p;
    cout << fp << endl;
    p = p + 1;
    cout << p << endl;
    delete[] p;
    cout << *fp << endl;
    cout << *(fp + 1) << endl;
    cout << p << endl;
    cout << *(p + 1) << endl;
}