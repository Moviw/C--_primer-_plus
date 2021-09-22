/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-21 01:27:33
 * @LastEditTime: 2021-09-21 14:12:44
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/11.使用类/Vector类/vector.h
 * @Description: 
 ************************************************/
#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <iostream>
#include <cmath>
using namespace std;
class Vector
{
public:
    enum MODE
    {
        POL,
        RECT
    };

private:
    double x;
    double y;
    double mag;
    double ang;
    MODE mode;
    void set_mag();
    void set_ang();
    void set_x();
    void set_y();

public:
    Vector();
    Vector(double, double, MODE mode = RECT);
    void reset(double n1 = 0, double n2 = 0, MODE mode = RECT);
    double xval() { return this->x; };
    double yval() { return this->y; };
    double magval() { return this->mag; };
    double angval() { return this->ang; };

    void pol_mode();
    void rect_mode();
    //运算符重载
    Vector operator+(const Vector &v);
    Vector operator-(const Vector &v);
    Vector operator*(const double n);
    //友元函数
    friend Vector operator*(const Vector &v, double n);
    friend ostream &operator<<(ostream &cout, const Vector &v);
};

#endif