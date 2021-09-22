/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-21 13:16:17
 * @LastEditTime: 2021-09-22 12:31:12
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/11.使用类/Complex类/main.cpp
 * @Description: 
 ************************************************/
#include <iostream>
#include "complex0.h"
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
    Complex operator+(const Complex &c)
    {
        return Complex(this->x + c.x, this->y + c.y);
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
int main()
{
    Complex a(3, 4);
    Complex c;
    cout << "enter a complex number (q to quit) : ";
    while (cin >> c)
    {
        cout << "c is " << c << endl;
        cout << "conjugate of c is " << (~c) << endl;
        // cout << "(a+c) is " << a + c << endl;
        // cout << "(a-c) is " << a - c << endl;
        // cout << "(a*c) is " << a * c << endl;
        // cout << "(2*c) is " << c * 2 << endl;
        cout << "enter a complex number (q to quit) : ";
    }
    cout << "Done\n";
    return 0;
}