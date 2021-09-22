# 内存模型和名称空间
## 单独编译
将程序划分为2部分:
- 头文件:包含结构声明和使用这些结构的函数的原型

头文件中应该包含:
- - 函数原型
- - 使用#define和const定义的常量变量
- - 结构声明
- - 类声明
- - 模板声明
- - 内联函数
- 源代码文件:包含与结构有关的函数的代码(对函数进行定义的文件)
- 源代码文件:包含调用与结构相关的函数的代码(实现具体功能的文件,常常有main()函数)
![](image/note9/1631975610979.png)

头文件coordin.h实例:
```h
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
```
下面的三段代码:

    #ifndef __COORDIN_H_
    #define __COORDIN_H_
    #endif
`防止多个文件多次定义同一个函数或结构体被多次声明`

函数定义文件实例:
```cpp
#include <iostream> //加尖括号是在系统目录中找
#include <cmath>
#include "coordin.h" //加双引号是在当前工程目录中找

using namespace std;

polar rect_to_polar(rect xypos)
{
    polar answer;

    answer.distance = sqrt(pow(xypos.x, 2) + pow(xypos.y, 2));
    answer.angle = atan2(xypos.y, xypos.x);
    return answer;
}

void show_polar(polar dapos)
{
    const double Rad_to_deg = 57.29577951;

    cout << "Distance = " << dapos.distance << endl;
    cout << "Angle = " << dapos.angle * Rad_to_deg << " degree" << endl;
}
```

`要记得调用自己编写的头文件`

函数调用文件示例:
```cc
#include <iostream> //加尖括号是在系统目录中找
#include <cmath>
#include "coordin.h" //加双引号是在当前工程目录中找
using namespace std;
int main()
{
    rect rplace;
    polar pplace;

    cout << "Enter the x and y values ";

    while (cin >> rplace.x >> rplace.y)
    {
        pplace = rect_to_polar(rplace);
        show_polar(pplace);
        cout << "Next two number (q to quit)";
    }
}
```
如何链接并运行:

    命令行中输入g++ file1.cpp file2.cpp  //前后无所谓
    生成了a.exe文件
    输入./a.exe就可以执行了

虽然在该文件中没有定义rect_to_polar()和show_polar()但是将file1.cpp 和 file2.cpp编译过后就可以链接在一起

## II.存储持续性、作用域和链接性
### 1.存储持续性

C++使用三种(C++11中是四种)不同的方案来存储数据,这些方案的区别就在于数据保留在内存中的时间:
1. 自动存储:

在函数定义中声明的变量(包括函数参数)的存储持续性为`自动`的,它们在程序开始执行其所属的函数或代码块时被创建,`在执行完函数或代码块时,它们使用的内存被释放`。

2. 静态存储:

在`函数定义外定义的变量`(全局变量)和`使用关键字static定义的变量`的存储持续性都为静态。它们在程序`整个运行过程中都存在`。C++有3种存储持续性为静态的变量。

3. 动态存储:

用`new运算符分配的内存将一直存在`,`直到使用 delete运算符将其释放或程序结束为止`。这种内存的存储持续性为动态,有时被称为自由存储( free store)或堆(heap)。

4. 线程存储:

当前,多核处理器很常见,这些CPU可同时处理多个执行任务。这让程序能够将计算放在可并行处理的不同线程中。如果变量是使用`关键字thread local声明的`,则其`生命周期与所属的线程一样长`。本书不探讨并行编程。

### 2. 作用域
作用域(scope)描述了名称在文件的多大范围内可见

****例如,函数中定义的变量可在该函数中使用,但不能在其他函数中使用****


C++变量的作用域有多种:
- 作用域为局部的变量只在`定义它的代码块中可用`
- 作用域为全局(也叫文件作用域)的变量在定义位置到文件结尾之间都可用
- 自动变量的作用域为局部
- 静态变量的作用域是全局还是局部取决于它是如何被定义的
- 在函数原型作用域( function prototype scope)中使用的名称只在包含参数列表的括号内可用(这就是为什么这些名称是什么以及是否出现都不重要的原因)。
- 在类中声明的成员的作用域为整个类(参见第10章)。
- 在名称空间中声明的变量的作用域为整个名称空间(由于名称空间已经引入到C++语言中,因此全局作用域是名称空间作用域的特例)。
- C++函数的作用域可以是整个类或整个名称空间(包括全局的),但不能是局部的(因为不能在代码块
内定义函数,如果函数的作用域为局部,则只对它自己是可见的,因此不能被其他函数调用。这样的函数
将无法运行)。

### 3. 链接性
- 链接性为外部的名称可在文件间共享(全局变量)
- 链接性为内部的名称可在函数间共享(静态全局变量,const修饰的全局变量)
- 没有链接性的名称不能共享(局部变量，静态局部变量)
## III. extern关键字
extern关键字用来声明一个外部变量,其存储持续性是静态的,作用域是整个文件

外部变量是在函数外部定义的,因此对所有函数而言都是外部的。

例如,可以在main()前面或头文件中定义它们。可以在文件中位于外部变量定义后面的任何函数中使用它,因此外部变量也称`全局变量`(相对于局部的自动变量)。

下面的三个文件代码用于展示extern关键字的功能:

1. support.h
```cc
#ifndef __SUPPORT_H__
#define __SUPPORT_H__

void update(double);
void local(void);

#endif
```

2. support.cpp
```cc
#include <iostream>
#include "support.h"
using namespace std;

extern double warming; //引用一个别的文件的名为warming的外部变量

void update(double x)
{
    warming += x;
    cout << "Updating warming to " << warming << " degrees" << endl;
}
void local()
{
    double warming = 0.8;
    cout << "Local warming = " << warming << " degrees" << endl;
    cout << "But global warming = " << ::warming << "degrees " << endl;  //这里
}
```

3. external.cpp

```cc
#include <iostream>
#include "support.h"
using namespace std;

/*extern 可写可不写*/ double warming = 0.3; //声明一个外部变量
int main()
{
    cout << "Global warming is " << warming << " degrees" << endl;
    update(0.1);
    cout << "Global warming is " << warming << " degrees" << endl;
    local();
    cout << "Global warming is " << warming << " degrees" << endl;
    return 0;
}
```
输出结果为：

    Global warming is 0.3 degrees
    Updating warming to 0.4 degrees
    Global warming is 0.4 degrees
    Local warming = 0.8 degrees
    But global warming = 0.4degrees
    Global warming is 0.4 degrees
`注意`:

- 在external.cpp中定义了一个外部变量
    
        double warming =0.3;
所有文件只要引用他均可读写其数据

support.cpp中使用

    extern double warming;
来声明变量warming,让该文件中的函数直接使用他(即直接使用外部定义的变量warming)

- support.cpp中有对::的另一个应用:
    
    ::warming
当`::`放在变量名前面时,该运算符表示使用变量的全局版本

因此local()中的warming会显示0.8,而::warming会显示0.4

## IV. static 关键字
### static关键字的静态持续性、内部链接性
将static限定符用于作用域为整个文件的变量时,该变量的链接性将为内部的

链接性为内部的变量只能在其所属的文件中使用

但常规外部变量都具有外部链接性,即可以在其他文件中使用

可使用链接性为内部的静态变量在同一个文件中的多个函数之间共享数据(名称空间提供了另外一种共享数据的方法)

另外,如果将作用域为整个文件的变量变为静态的,就不必担心其名称与其他文件中的作用域为整个文件的变量发生冲突

程序清单file0.cpp和程序清单file1.cpp演示了C++如何处理链接性为外部和内部的变量。

file0.cpp
```cc
#include <iostream>
int tom = 3;  //定义一个tom的外部变量
int dick = 30;//定义一个dick的外部变量
static int harry = 300;    //定义一个harry的静态内部变量,只在本文件内可见

void remote_access();
using namespace std;
int main()
{

    cout << "main() reports the following addresses:\n";
    cout << "&tom = " << &tom << endl;
    cout << "&dick = " << &dick << endl;
    cout << "&harry = " << &harry << endl;
    remote_access();
}
```

file1.cpp
```cc
#include <iostream>
extern int tom;       //引用外部的tom外部变量
static int dick = 10; //定义一个dick变量,他只在该文件内部可见
int harry = 200;      //定义一个harry外部变量

using namespace std;
void remote_access()
{
    cout << "remote access() reports the following addresses: \n";
    cout << "&tom = " << &tom << endl
         << " &dick= "
         << &dick << endl;
    cout << " &harry = " << &harry << endl;
}
```

运行结果如下:

    main() reports the following addresses:
    &tom = 0x404004
    &dick = 0x404008
    &harry = 0x40400c
    remote access() reports the following addresses:
    &tom = 0x404004
    &dick= 0x404010
    &harry = 0x404014

tom的地址相同是因为file1引用了file0的tom变量

dick的地址不同是因为file1声明了属于自己的dick变量

harry的地址不同是因为file0声明了属于自己的harry变量
### static关键字的静态持续性、无链接性
将static限定符用于`代码块中定义的变量`,可以使该变量的存储持续性是静态的

这意味着该变量直到程序结束之前一直存在

如果初始化了静态局部变量,则该程序是在启动时进行一次初始化,以后再调用该函数时,将不会像自动变量那样在被初始化

其他和函数内的其他自动存储的变量一样
```cc
void qwe()
{
    static int i = 0;
    i++;
}
int main()
{
    for (int i = 0; i < 10; i++)
    {
        qwe();
        cout << "now i in qwe() is " << i << endl;
    }
}
```
结果如下:

    now i in qwe() is 0
    now i in qwe() is 1
    now i in qwe() is 2
    now i in qwe() is 3
    now i in qwe() is 4
    now i in qwe() is 5
    now i in qwe() is 6
    now i in qwe() is 7
    now i in qwe() is 8
    now i in qwe() is 9
可以发现:
i的值只被初始化了一次,这就是static关键字对函数内变量的作用
