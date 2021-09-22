/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-20 22:49:55
 * @LastEditTime: 2021-09-20 23:24:08
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/clock.cpp
 * @Description: 
 ************************************************/
#include <iostream>
#include "clock.h"
using namespace std;
Clock::Clock()
{
    this->hour = 0;
    this->minute = 0;
}
Clock::Clock(int h, int m)
{
    hour = h;
    minute = m;
}
void Clock::show()
{
    cout << "hour = " << hour << " minutes = " << minute << endl;
}
void Clock::AddM(int minute)
{
    this->minute += minute;
    hour += (this->minute >= 60);
    this->minute %= 60;
}
void Clock::AddH(int hour)
{
    this->hour += hour;
}
Clock Clock::operator+(const Clock c)
{
    Clock temp;
    temp.minute = this->minute + c.minute;
    temp.hour = c.hour + this->hour + (temp.minute >= 60);
    temp.minute %= 60;
    return temp;
}
Clock *Clock::Add(const Clock c)
{
    this->minute += c.minute;
    this->hour += (this->minute >= 60) + c.hour;
    this->minute %= 60;
    return this;
}