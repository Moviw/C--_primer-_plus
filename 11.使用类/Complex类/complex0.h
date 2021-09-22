/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-21 01:27:33
 * @LastEditTime: 2021-09-22 02:35:41
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/11.使用类/Complex类/complex0.h
 * @Description: 
 ************************************************/
#ifndef __COMPLEX0_H__
#define __COMPLEX0_H__
#include <iostream>
using namespace std;
class Complex
{

private:
    double x;
    double y;

public:
    Complex();
    Complex(double n1, double n2);

    //运算符重载
    friend Complex operator+(const Complex &c,const Complex &v) 
    {
        return Complex(v.x + c.x, v.y + c.y);
    }
    Complex operator-(const Complex &c) const;
    Complex operator*(const double n) const;
    Complex operator*(const Complex &c) const;
    Complex operator~() const;

    //友元函数
    friend Complex operator*(const Complex &c, const double n);
    friend ostream &operator<<(ostream &cout, Complex &); //TODO
    friend istream &operator>>(istream &cin, Complex &);
};

#endif