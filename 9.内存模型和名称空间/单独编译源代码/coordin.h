/************************************************ 
 * @Author: Movix
 * @Date: 2021-09-18 22:35:56
 * @LastEditTime: 2021-09-18 22:39:13
 * @Github: https://github.com/Moviw
 * @FilePath: /C--_primer-_plus/coordin.h
 * @Description: 
 ************************************************/

#ifndef __COORDIN_H_
#define __COORDIN_H_
struct polar
{
    double distance;
    double angle;
};
struct rect
{
    double x;
    double y;
};

polar rect_to_polar(rect xypos);
void show_polar(polar dapos);

#endif