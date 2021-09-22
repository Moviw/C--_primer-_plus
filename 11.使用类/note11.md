# 使用类
本章将介绍类的一些实用技巧包括:
- 运算符重载
- 友元函数
- 重载<<运算符,以使用与输出
- 状态成员
- 使用rand()生成随机值
- 类的自动转换和强制类型转换
- 类转换函数
## I. 运算符重载
可以对运算符如(+ * & %)继续重新定义以满足使用需求

比如想重载加法运算符

    operator+();

下面是加法运算符重载的示例:

`clock.h`
```cc
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
    Clock operator+(const Clock c);   //重载+运算符
    Clock Add(const Clock c) const;   //传统方法:用函数相加 
};

#endif
```

`clock.cpp`
```cc
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
Clock Clock::operator+(const Clock c)    //重载+运算符
{
    Clock temp;
    temp.minute = this->minute + c.minute;
    temp.hour = c.hour + this->hour + (temp.minute >= 60);
    temp.minute %= 60;
    return temp;
}
Clock Clock::Add(const Clock c) const    //传统方法:用函数相加 
{
    Clock temp;
    temp.minute = this->minute + c.minute;
    temp.hour = c.hour + this->hour + (temp.minute >= 60);
    temp.minute %= 60;
    return temp;
}
```
`main.cpp`
```cc
#include <iostream>
#include "clock.h"
using namespace std;
int main()
{
    Clock c1(20, 10);
    Clock c2 = Clock(2, 55);
    c1.show();
    c2.show();

    c1.AddM(30);
    Clock c3 = c1 + c2;
    c3.show();

    Clock c4 = c1 + c2;
    c4.show();

    // hour = 20 minutes = 10
    // hour = 2 minutes = 55
    // hour = 23 minutes = 35
    // hour = 23 minutes = 35
}
```
可以看出用加法运算符与函数的最终结果一致

况且加法运算符更符合人们直觉

所以可以在必要时运用重载运算符

### 运算符重载的一些限制
1. 重载后的运算符必须至少有一个操作数是用户定义的类型,这将防止用户为标准类型重载运算符比如不能将减法运算符(-)重载为计算两个double值的和,而不是它们的差

2. 使用运算符时不能违反运算符原来的句法规则。例如,不能将求模运算符(%)重载成使用一个操
  
        int x;
        Time shiva;
        % x;        //invalid for modulus operator
        % shiva;    //invalid for overloaded operator

同样,不能修改运算符的优先级。因此,如果将加号运算符重载成将两个类相加,则新的运算符与原
来的加号具有相同的优先级。

3. 不能创建新运算符。例如,不能定义 operator**()函数来表示求幂。
4. 不能重载下面的运算符。
- sizeof运算符
- .成员运算符。
- ->成员指针运算符。
- ∷作用域解析运算符。
- ?:条件运算符
## II. 友元函数
C++控制对类对象私有部分的访问,通常只能使用公有类访问,但是有时这种限制过于严格,友元函数可以突破这种限制

让函数成为类的友元,可以赋予该函数与类的成员函数相同的访问权限

考虑下面代码,你就能体会友元函数的必要性:
```cc
#include <iostream>
using namespace std;
class Clock
{
    int hour;
    int minute;

public:
    Clock(int hour = 0, int minute = 0)
    {
        this->hour = hour;
        this->minute = minute;
    }

    void show() { cout << "hour = " << hour << " minutes = " << minute << endl; }
    Clock operator*(double n)
    {
        Clock tmp;
        long totalminute = this->hour * 60 * n + this->minute * n;
        tmp.hour = totalminute / 60;
        tmp.minute = totalminute % 60;
        return tmp;
    }
};
int main()
{
    Clock c1(20, 40);
    c1.show();
    c1 = c1 * 2;
    c1.show();
    c1 = 2 * c1;    !!error
}
```

为什么`c1=2*c1`会报错:

    2*c1相当于是这样调用函数:
    2.operator*(c1);
这样当然会报错

你可能会说完全可以定义一个非成员函数,使其对*运算符重载以完成该功能,但是不要忘了非成员函数没有访问类对象内数据的权限

或者你选择这么编写一个非成员函数:

    Clock operator*(double m,const Clock &c)
    {
         return c*m;   
    }
诚然这种反转操作数顺序的做法很巧妙,但这还是没有从根本上解决问题,即:`直接访问类的数据`

因此友元函数,其本质是一个非成员函数却能以成员函数的身份去访问数据全拜`friend`关键字所赐

其代码如下:

        friend Clock operator*(double n, Clock &c)
    {
        Clock tmp;
        long totalminute = c.hour * 60 * n + c.minute * n;
        tmp.hour = totalminute / 60;
        tmp.minute = totalminute % 60;
        return tmp;
    }

### 常用的友元<<运算符

经常要使用show()函数来显示对象信息

可不可以直接把对象数据cout出去呢?

1. `1.0版本`

可以通过重载<<来实现

一种能最直接想到的方法即:

    void operator<<(ostream &cout){...}

cout属于ostream类的对象,所以要传入其作为参数

但是不要忘记,如此重载后,想要调用<<的话,只能是这样:

    temp<<cout;
这不是我们想要的

因此需要使用`2.0版本`

2. `2.0版本`
通过友元函数,这样重载<<运算符:

    friend void operator<<(ostream & cout,Clock c){....};

不错!我们可以如往常一样输出信息了!

但是还有个缺点:当我们需要连续输出信息时,就会出现错误,因为cout的输出原理类似下面的代码:

    int x=1;
    int y=2;
    cout<<x<<y;        -->>(cout<<x)<<y;

即(cout<<x)会返回一个cout对象

因此我们的友元函数也需要修改为最终版本

3. `final版本`

        friend ostream& operator<<(ostream & cout,Clock c){....};
Yes,indeed..

这才是我们需要的最终版本,一个与常规cout完全相同且能输出我们特定类的信息的cout   :)

此时我们调用下面代码是没问题的:

    Clock c;
    cout<<"this is a test"<<c<<endl;

## III.友元函数,运算符重载的实例练习
Vector类文件夹创建了一个小程序,它使用了修订后的 Vector类

该程序模拟了著名的醉鬼走路问题(Drunkard Walk problem)

其意思是,将一个人领到街灯柱下。这个人开始走动,但每一步的方向都是随机的(与前一步不同),这个问题的一种表述是,这个人走到离灯柱50英尺处需要多少步

从矢量的角度看,这相当于不断将方向随机的矢量相加,直到长度超过50英尺。

程序清单main.cpp允许用户选择行走距离和步长。该程序用一个变量来表示位置(一个矢量),并报告到
达指定距离处(用两种格式表示)所需的步数

可以看到,行走者前进得相当慢  虽然走了1000步,每步的距离为2英尺,但离起点可能只有50英尺。这个程序将行走者所走的净距离(这里为50英尺)除以步数,来指出这种行走方式的低效性。随机改变方向使得该平均值远远小于步长

为了随机选择方向,该程序使用了标准库函数rand(srand()和time()(参见程序说明)

由于程序代码过长,不再粘贴到此处

## IV. explicit关键字与类强制转换
考虑下面代码:
```cc
class num
{
    int n;

public:
    num() { n = 0; }
    num(int n) { this->n = n; }
    void show() { cout << "n = " << n << endl; }
};
int main()
{
    num n1 = 9;
    n1.show();
}
```
`num n1=9;`为什么这句代码能被正常执行?

因为在这里进行了隐式的类型转换,即

    num n1=9;    -->>     num n1=num(9);
有时这种不是我们想要的,如何避免?

    使用explicit关键字
    
将你想避免的函数前面加上explicit,如:
    
    num(int n) { this->n = n; }  -->>    explicit num(int n) { this->n = n; }

这样`num n1 = 9;`就会报错
    

## V. 转换函数
既然可以将数字转换为类对象,可不可以将类对象转换为数字呢?

可以.只需要重载对应数据类型的名字即可,如下面所示:

    operator typeName(){...}

但是需要注意以下几点:
- 转换函数必须是类方法
- 转换函数不能指定返回类型
- 转换函数不能有参数

比如在类中定义了这样一个转换函数:

    operator int(){return n;}

在main.cpp中定义了一个num类,并将它赋值给一个int 变量

    num n1=9;
    int x=n1;
此时,x的值即n1对象中的n的值

同样的,你可以使用explicit关键字使其只能在被显式调用时才有效