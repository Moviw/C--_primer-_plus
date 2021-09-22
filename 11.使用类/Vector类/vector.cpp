/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-21 01:32:52
 * @LastEditTime: 2021-09-21 14:13:32
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/11.使用类/Vector类/vector.cpp
 * @Description: 
 ************************************************/
#include <iostream>
#include <cmath>
#include "vector.h"
using namespace std;
Vector::Vector()
{
    x = y = mag = ang = 0;
    mode = RECT;
}
Vector::Vector(double x, double y, MODE mode)
{
    if (mode == RECT)
    {
        this->x = x;
        this->y = y;
        set_ang();
        set_mag();
        this->mode = mode;
    }
    else if (mode == POL)
    {
        this->ang = y / 57.2957795130823;
        this->mag = x;
        set_x();
        set_y();
        this->mode = mode;
    }
    else
    {
        cout << "Incorrect 3rd argument to Vector()" << endl;
        cout << "vector set to (0,0)" << endl;
        reset();
    }
}
void Vector::set_mag()
{
    mag = sqrt(x * x + y * y);
}
void Vector::set_ang()
{
    if (x == 0.0 && y == 0.0)
    {
        ang = 0;
    }
    else
    {
        ang = atan2(y, x);
    }
}
void Vector::set_x()
{
    x = mag * cos(ang);
}
void Vector::set_y()
{
    y = mag * sin(ang);
}

void Vector::reset(double n1, double n2, MODE mode)
{ //reset是在该对象上直接修改  而使用构造函数是重新创建一个对象
    this->mode = mode;
    if (this->mode == RECT)
    {
        this->x = n1;
        this->y = n2;
        set_ang();
        set_mag();
    }
    else if (this->mode == POL)
    {
        this->mag = n1;
        this->ang = n2 / 57.2957795130823;
        set_x();
        set_y();
    }
    else
    {
        cout << "Incorrect 3rd argument to Vector()" << endl;
        cout << "vector set to (0,0)" << endl;
        x = y = mag = ang = 0;
        this->mode = RECT;
    }
}
void Vector::pol_mode()
{
    this->mode = POL;
}
void Vector::rect_mode()
{
    this->mode = RECT;
}
//运算符重载
Vector Vector::operator+(const Vector &v)
{
    //这里直接用构造器并返回这个对象
    return Vector(this->x + v.x, this->y + v.y);
    /* 提示:
     如果方法通过计算得到一个新的类对象, 则应考虑是否可以使用类构造函数来完成这种工作 这样做不仅可以避免麻烦, 而且可以确保新的对象是按照正确的方式创建的。*/
}
Vector Vector::operator-(const Vector &v)
{
    //这里直接用构造器并返回这个对象
    return Vector(this->x - v.x, this->y - v.y);
    /* 提示:
     如果方法通过计算得到一个新的类对象, 则应考虑是否可以使用类构造函数来完成这种工作 这样做不仅可以避免麻烦, 而且可以确保新的对象是按照正确的方式创建的。*/
}
Vector Vector::operator*(const double n)
{
    //这里直接用构造器并返回这个对象
    return Vector(this->x * n, this->y * n);
    /* 提示:
     如果方法通过计算得到一个新的类对象, 则应考虑是否可以使用类构造函数来完成这种工作 这样做不仅可以避免麻烦, 而且可以确保新的对象是按照正确的方式创建的。*/
}
//友元函数
Vector operator*(const Vector &v, double n)
{ //这里不能再operator*前加Vector::  因为其不是成员函数
    return v * n;
    /* 提示:
     如果方法通过计算得到一个新的类对象, 则应考虑是否可以使用类构造函数来完成这种工作 这样做不仅可以避免麻烦, 而且可以确保新的对象是按照正确的方式创建的。*/
}
ostream &operator<<(ostream &cout, const Vector &v)
{
    //这里不能再operator<<前加Vector::  因为其不是成员函数
    if (v.mode == Vector::POL) //这里要写Vector::POL  因为该函数不是Vector的成员函数
    {
        cout << "(m,a) = (" << v.mag << ", " << v.ang * 57.2957795130823 << ")" << endl;
    }
    else if (v.mode == Vector::RECT) //这里要写Vector::RECT  因为该函数不是Vector的成员函数
    {
        cout << "(x,y) = (" << v.x << ", " << v.y << ")" << endl;
    }
    else
    {
        cout << "Vector object mode is invalid" << endl;
    }
    return cout;
}