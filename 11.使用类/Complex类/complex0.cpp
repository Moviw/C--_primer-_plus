/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-21 13:10:45
 * @LastEditTime: 2021-09-22 02:36:28
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/11.使用类/Complex类/complex0.cpp
 * @Description: 
 ************************************************/
#include <iostream>
#include <cmath>
#include "complex0.h"
using namespace std;
Complex::Complex()
{
    x = 0;
    y = 0;
}
Complex::Complex(double n1, double n2)
{
    this->x = n1;
    this->y = n2;
}

//运算符重载

// Complex Complex::operator+(const Complex &c) const
// {
//     return Complex(this->x + c.x, this->y + c.y);
// }
// Complex Complex::operator-(const Complex &c) const
// {
//     return Complex(this->x - c.x, this->y - c.y);
// }
// Complex Complex::operator*(const double n) const
// {
//     return Complex(this->x * n, this->y * n);
// }
// Complex Complex::operator*(const Complex &c) const
// {
//     return Complex(this->x * c.x - this->y * c.y, this->x * c.y + this->y * c.x);
// }
// Complex Complex::operator~() const
// {
//     return Complex(this->x, -this->y);
// }

// // //友元函数
// Complex operator*(const Complex &c, const double n)
// {
//     return c * n;
// }
// ostream &operator<<(ostream &cout, Complex &c) //TODO
// {
//     cout << "(" << c.x << "," << c.y << "i)";
//     return cout;
// }
// istream &operator>>(istream &cin, Complex &c)
// {
//     cin >> c.x >> c.y;
//     return cin;
// }