# 函数
要使用C++函数,必须完成如下工作:
- 提供函数定义
- 提供函数原型
- 调用函数

## I. 为什么需要函数原型

`为何编译器需要原型?难道她不能再文件中进一步查找,以了解函数是如何定义的么`

这种方法的一个问题是效率不高,编译器在搜索文件的剩余部分时将必须停止对main的编译

一个更严重的问题是:函数甚至可能不该该文件中,C++允许将一个程序放在多个文件中,单独编译这些文件,再把它们组合起来

在这种情况下,编译器在编译main()时,可能无权访问函数代码

因此唯一解决办法就是:在首次使用函数之前定义它
 
## II. 原型的语法

声明函数原型时可以不需要提供变量名,有类型列表就足够了,例如:

    int f(int);  //ok
## III.函数与数组

在用函数处理数组时,要向函数传递两个参数
- 函数名(对应的头地址指针)
- 数组长度

如:

    int sum_arr(int arr[],int n);
虽然int arr[]和int *arr是等效的

但是前者更强调传入的参数是个数组,后者强调传入的参数是个int类型指针,即可能指向一个独立的值

这对用户的可读性有很大影响

### 为什么要传递数组的地址而不是数组的拷贝

因为数组可能很大,在拷贝过程中系统开销可能会很大,会花费时间来复制大块的数据

因此直接操作数组本身是一种更便捷的方式

### 直接在数组本身上操作会有什么风险?

由于直接在数组本身上操作,可能会直接破坏数据

因此,在必要时:`可以用const修饰符修饰数组`

### 为什么要将数组长度传入函数
考虑下面代码:
```cpp
1   int sum_arr(int[], int);
2   int main()
3   {
4       int cookies[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
5       cout << sizeof cookies << endl;
6       int sum = sum_arr(cookies, 10);
7       cout << sum;
8   }
9   int sum_arr(int arr[], int n)
10  {
11      int ret = 0;
12      cout << sizeof arr << endl;
13      for (int i = 0; i < n; i++)
14      {
15          ret += arr[i];
16      }
17      return ret;
18  }

```


第十二行中的sizeof(arr)会输出什么?

1. int类型指针的大小?
1. arr数组所占的字节数

输出的是int类型指针的大小,因为arr的本质是int类型指针

`既然是指针,他就无法知道数组的长度为多少,因此需要传入数组长度来确定`

## IV. 尽量使用const
将指针参数声明为指向常量数据的指针有两条理由:
- 可以避免由于无意间修改数据而导致的编程错误
- 使用const使得函数能够处理const和非const实参,否则只能接受非const数据


## V. 函数与二维数组
加入想要在函数中传入一个3行4列的二维数组作为参数应该这么写:

    void func(int a[][4],3)
或者
    
    void func(int (*a)[4],3)

第一种很好理解,而第二种里的**int (*a)[4]**是什么?

    他声明了一个a变量,这个变量用来指向含有4个int类型数据的数组,即数组指针

## VI.函数指针

与数据项类似,函数也有地址.函数的地址是储存器机器语言代码的内存的开始地址

可以编写将另一个函数的地址作为参数的函数,这样第一个函数就能找到第二个函数,并运行他

与直接调用另一个函数相比,这种方法更笨拙,但它允许在不同而事件传递不同函数的地址,

### 函数指针的使用:
- 获取函数的地址
- 声明一个函数指针
- 使用函数指针来调用函数

`获取函数的地址`:
函数名就是函数的地址,但是要区分函数的地址与函数的返回值:

    fun(think);     将think函数地址传递给fun()
    fun(think());   将think函数返回值传递给fun()

`声明函数指针`:
声明某种数据类型的指针时,必须指定指针指向的类型

同样的,声明指向函数的指针时,必须指定函数指向的函数类型,也就是指定**函数的返回类型与函数的参数列表**

例如:

    double fun(int);    函数原型

其函数指针应该为:

    double (*pf)(int);

如果不加括号的话:

    double *pf(int);

pf也表示一个函数指针,其参数列表为一个int,但返回值是*double \**

`用指针来调用函数`:

```cpp
1    double pam(int);
2    double (*pf)(int);
3    pf=pam;
4    double x=pam(4);
5    double y=pf(4);
6    double z=(*pf)(4);
```
上面代码中,4/5行的调用形式均有效

函数指针数组练习题:

第七章练习题.10
```cc
#include <iostream>
using namespace std;
double add(double x, double y)
{
    return x + y;
}
double sub(double x, double y)
{
    return x - y;
}
double mul(double x, double y)
{
    return x * y;
}
double calculate(double x, double y, double (*pf)(double, double))
{
    return pf(x, y);
}
int main()
{
    double (*pf[3])(double, double);
    pf[0] = add;
    pf[1] = sub;
    pf[2] = mul;
    for (int i = 0; i < 3; i++)
    {
        cout<<calculate(2,5,pf[i])<<endl;
    }
}
```

