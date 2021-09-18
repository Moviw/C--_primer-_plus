# C++函数新特性
## I. 内联函数
### 内联函数定义与优缺点
内联函数是C++为提高程序运行速度所做的一项改进

常规函数和内联函数之间的主要区别不在于编写方式，而在于C++编译器如何将它们组合到程序中。

要了内联函数与常规函数之间的区别，必须深入到程序内部编译过程的最终产品是可执行程序——由机器语言指令组成。运行程序时，操作系统将这些指令载入到计算机内存中，因此每条指令都有特定的内存地址。计算机随后将逐步执行这些指令。

有时将跳过一些指令，向前或向后跳到特定地址

常规函数用也使程序跳到另一个地址(函数的地址)，并在函数结束时返回

來回跳跃并记录跳跃位置意味着以前使用函数时，需要一定的开销

C++内联函数提供了另一种选择。内联函数的编译代码与其他程序代码“内联”起来了。也就是,编译器将使用`相应的函数代码替换函数`调用

对于内联代码，程序无需跳到另一个位置处执行代码，再跳回来

`内联函数比常规函数稍快`

`但代价是使用更多内存`

执行函数代码的时间比处理函数凋用机制的时间长 则节省的时间将只占整个过程的很小一部分

如果代码执行时间很短，则内联调用 可以节省非内联调用使用的大部分时间。

另一方面，由于这个过程相当快，因此尽管节省 该过程的大部分时间，但节省的时间绝对值并不大,

### 内联函数的使用
要使用这项特性，必须采取一下措施之一：
- 在函数声明前加上关键字inline;
- 參在函数定义前加上关键字inline

通常的做法是省略原型，将整个定义(函数头和所有函数代码)放在本应提供原型的地方。
```cpp
#include<iostream>
using namespace std;
inline double max(double x,double y)
{
	return ((x>y?x:y));
}

int main()
{
        const int a = 10;  
        int *p = (int *)&a;  
        *p = 100;  
        printf("%d\t%d\n", a, *p); 
		printf("%x            %x",&a,p); 
        return 0;  
}
```

### #define 与内联

如果有一个用来计算平方的宏

    #define s(x)  x*x
这并不是通过传递参數实现的，而是通过文本替换来实现的

比如:

    printf("%d",s(10+10)); 
就会打印120,`因为是10+10*10+10`


## II.引用变量
引用是已定义的`变量的别名`

引用变量的主要用途是用于函数的形参,通过将引用变量用作参数,`函数将使用原始数据而不是副本`

引用变量为处理大型结构，设计类提供了一种非常方便的捷径

### 创建引用变量

    int rat;
    int & redonts=rat;

此时rodents 和rat指向同一处内存单元

**注意**：这里的&不是取地址运算符,而是类型标识符的一部分

```cc
    int a = 10;
    int &c = a;
    cout << a << endl           //10      
         << &a << endl;         //0x61fe0c
    cout << c << endl           //10      
         << &c << endl;         //0x61fe0c
```
此时a和c的值,对应的地址都是相同的

### 引用变量与指针的区别

看上去,引用很像是伪装表示的指针

实际上,引用与指针还是不同的:
- 必须在声明引用时将其初始化,而不像指针那样先声明再赋值
  
        int rat;
        int & rodent;
        rodent=rat;


    这是不可以的
- 引用更接近const指针,一旦与某个变量关联起来,就一直效忠于他,也就是说:
  
        int & rodents=rat;
        等效于
        int *const rodents=&rat;

考虑下面代码
```cc
    int a = 10;
    int b = 20;
    int &c = a;
    cout << &a << endl                  //0x61fe14
         << &b << endl                  //0x61fe10
         << &c << endl;                      //0x61fe14
    c = b;             
    cout << a << endl                        //20
         << b << endl                        //20
         << c << endl;                       //20
    cout << &a << endl                       //0x61fe14
         << &b << endl                       //0x61fe10
         << &c << endl;                      //0x61fe14
```
可以看出来
    
    c=b;
这条语句不是让引用变量c引用b,而是将a(或别名为c)的变量的值改为20(即b的值)

这才导致了a,b,c的值均为20

而a,c的地址仍然相同

### 引用的属性和特别之处

考虑下面代码:
```cc
double cube(double a)
{
    a *= a * a;
    return a;
}
double recube(double &a)
{
    a *= a * a;
    return a;
}
int main()
{
    double a = 5;
    cout << cube(a) << "   " << a << endl;      //125   5
    cout << recube(a) << "   " << a << endl;        //125   125
    cout << recube(5) << "   " << 5 << endl;        //报错
}

```
发现recube改变了main()中x的值,因为recube传入的参数是引用变量,他会修改传入的参数

同时发现向recube()中传入常量也会报错,是因为`如果a是一个变量的别名,那么实参应该是变量`

### 引用变量与const

上面的代码中`无法向recube()中传入常量或者表达式`,而在int &a前加入const之后:
```cc
double recube(const double &a)
{
    
    return a*a*a;
    cout << recube(5) << "   " << 5 << endl; //125   5
    cout << recube(5 + a) << "   " << 5 << endl;
}
```
不会报错而且输出正确

因为`仅当参数为const引用时`,如果`实参与引用参数不匹配`,`C++会生成临时变量`

### 将函数参数声明为引用类型的三个理由:
1. 使用const可以避免无意中修改数据的编程错误
2. 使用const使函数能够处理const和非const实参,否则只能接受非const数据
3. 使用const引用时函数能够正确生成并使用临时变量

### 为什么函数需要返回引用

返回引用最重要的一点是:应避免返回函数终止时不再存在的内存单元引用,比如应避免:

    int &fun(int &a)
    {
        int b;
        b=a;
        return b;
    }

该函数返回一个临时变量的引用,而函数运行完毕后他将不再存在了

#### 如何避免
- 最简单的方法:返回一个作为参数传递给函数的引用
- 用new来分配新的存储空间


### 何时使用引用参数
使用引用参数的主要原因有两个:
- 程序员能够修改调用函数中的数据对象
- 通过传递引用而不是整个数据对象,可以提高程序的运行速度

当数据对象较大时(比如结构和类对象),第二个原因更重要,这也是使用指针的原因

因为引用参数实际上是基于指针的代码的另一个接口

什么时候使用引用,什么时候使用指针,什么时候按值传递?下面是一些指导原则:

1. 对于`使用传递的值而不作修改`的函数
   
   - 如果数据对象很小,如基本数据类型或小型结构,则按值传递
   -  如果数据对象是数组,则使用指针,且将指针声明为const指针
   -  如果数据对象是较大的结构,则使用const指针或const引用,以提高程序的效率,可以节省复制结构所需的时间空间
    - 如果数据对象是类对象,则使用const引用,因为类设计的语义常常要求使用引用
2. 对于`修改调用函数中数据`的函数
   
    - 如果是基本数据类型,则使用指针
    - 如果是数组,则只能使用指针
    - 如果是结构,则使用引用或指针
    - 如果是类对象,则使用引用

## III.默认参数
默认参数指的是当函数调用中省略了实参时自动使用的一个值
    
    int fun(int n=1);
当用户没有为n传入参数时,将n参数初始化为1

传入参数的话就以用户传入数据为准

`注意:`

默认参数只能在声明中写出,不能在函数定义中写出
### 默认参数的规范
对于带参数列表的函数,必须从右向左添加默认值,即:`要为某个参数设置默认值,必须为他右面所有参数提供默认值`
```cc
    int fun1(int n,int m=4,int j=6);    //可行
    int fun2(int n,int m=4,int j);      //不行
    int fun3(int n=1,int m=4,int j=6);  //可行
```
实参从左到右赋给相应的形参,且不跳过任何参数,考虑如下代码:
```cc
void fun1(int n, int m = 4, int j = 6)
{
    cout << "n: " << n << endl;
    cout << "m: " << m << endl;
    cout << "j: " << j << endl;
}
int main()
{

    fun1(1);
    n: 1
    m: 4
    j: 6

    fun1(1,2);
    n: 1
    m: 2
    j: 6

    fun1(1,2,3);
    n: 1
    m: 2
    j: 3
}

```

## IV.模板
关于模板函数的优先级:
- 对于给定的函数名,可以有`非模板函数`,`模板函数`,和`显式具体化模板函数`以及他们的重载版本
- 显式具体化的原型和定义,均以`template<>`打头,并通过名称来指出类型
- `具体化优先于常规模板`,而`非模板函数优先于具体化和常规模板`

```cc
template <class T>
void Swap(T &a, T &b);
int main()
{
    int i = 10, j = 20;
    cout << i << endl
         << j << endl;
    Swap(i, j);
    cout << i << endl
         << j << endl;

    double x = 20.1, y = 2.2323;
    cout << x << endl
         << y << endl;
    Swap(x, y);
    cout << x << endl
         << y << endl;
}
template <class T>
void Swap(T &a, T &b)
{
    T temp=a;
    a=b;
    b=temp;
}
```
`注意`:
- 要在定义和声明处都写上**template \<class T>**
- 原本我想用按位运算来实现交换的,但是由于double无法按位运算,所以选用传统方式,这也是模板的缺陷--要选用通用的方式

### 模板的显式具体化
在代码中包含函数模板本身并不会生成函数定义,它只是一个用于生成函数定义的方案

考虑下面代码:
```cc
struct job
{
    char name[40];
    double salary;
    int floor;
};

template <class T>
void Swap(T &a, T &b);

template <>
void Swap<job>(job &a, job &b);

void show(const job &a)
{
    cout << a.name << ": $" << a.salary << " on floor " << a.floor << endl;
}
int main()
{
    int i = 10, j = 20;
    cout << i << endl
         << j << endl;
    Swap(i, j);
    cout << i << endl
         << j << endl;

    double x = 20.1, y = 2.2323;
    cout << x << endl
         << y << endl;
    Swap(x, y);
    cout << x << endl
         << y << endl;

    job sue = {"Susan Yaffrr", 73000.60, 7};
    job sidney = {"sidney Taffee", 92767.2, 23};
    show(sue);
    show(sidney);
    swap(sue, sidney);
    show(sue);
    show(sidney);
}
template <class T>
void Swap(T &a, T &b)
{
    cout << "using template" << endl;
    T temp = a;
    a = b;
    b = temp;
}
template <>
void Swap<job>(job &a, job &b)
{
    cout << "using untemplate" << endl;
    double t1;
    int t2;
    t2 = a.floor;
    a.floor = b.floor;
    b.floor = t2;

    t1 = a.salary;
    a.salary = b.salary;
    b.salary = t1;
}

output:

10
20
using template
20
10
20.1
2.2323
using template
2.2323
20.1
Susan Yaffrr: $73000.6 on floor 7
sidney Taffee: $92767.2 on floor 23
using untemplate
Susan Yaffrr: $92767.2 on floor 23
sidney Taffee: $73000.6 on floor 7
```

`注意`:模板显式化需要在函数名右侧加上`<类型名>`

### 编译器选择使用哪个函数版本

C++如何选择与参数匹配的函数？

考虑以下代码:
```cc
    may('B');
有如下函数:
1    void may(int);
2    float may(float,float=3);
3    void may(char);
4    char *may(const char *);
5    char may(const char &);
6    template<class T>void may(const T &);
7    template<class T>void may(T *);
```
- 由于4,7的参数为指针,而整数类型不能被强制转换成指针类型,所以4,7肯定被排除
- C++在选择函数时还会遵循(完全匹配和最佳匹配原则),即会选择`转换最简单的函数使用`
