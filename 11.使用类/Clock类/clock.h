/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-20 22:47:36
 * @LastEditTime: 2021-09-20 23:20:35
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/clock.h
 * @Description: 
 ************************************************/
#ifndef __CLOCK_H__
#define __CLOCK_H__

class Clock
{
    int hour;
    int minute;

public:
    Clock();
    Clock(int, int);
    void show();
    void AddM(int minute);
    void AddH(int hour);
    Clock operator+(const Clock c);
    Clock *Add(const Clock c);
};

#endif