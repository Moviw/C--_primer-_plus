# 对象和类
## I.创建一个类

将一个类定义在stack00.h中,代码如下:

    #ifndef __STOCK00__H__
    #define __STOCK00__H__
    
    #include <string>
    
    class Stock
    {
    	private:
    		std::string company;
    		long shares;
    		double share_val;
    		double total_val;
    		void set_tot() {total_val = shares * share_val;}
    	public:
    		void acquire(const std::string &co, long n, double pr);
    		void buy(long num, double price);
    		void sell(long num, double price);
    		void update(double price);
    		void show();
    };
    
    
    #endif

一般将类放在头文件中

private标识符可写可不写,因为`C++对数据的访问限制默认为private`

## II.实现类成员函数
1. 定义成员函数时,使用作用域解析运算符(::)来标识函数所属的类,比如:

    Stock::show(){....}
    
    同时还可以定义另一个Buffoon类的同名为show的成员函数

    Buffoon::show(){....}
1. 类方法可以访问类的private组件


下面是stock00.h中的函数在stockk00.cpp中的实现:

```cc
#include <iostream>
#include "stock00.h"

void Stock::acquire(const std::string &co, long n, double pr)
{
	company = co;
	if(n < 0)
	{
		std::cout << "Numer of shares can't be negative; " << company << " shares set to be 0." << std::endl;
		shares = 0;
	}
	else
		shares = n;

	share_val = pr;

	set_tot();
}

void Stock::buy(long num, double price)
{
	if(num < 0)
	{
		std::cout << "Numer of shares can't be negative, Transaction is aborted" << std::endl;
	}
	else
	{
		shares += num;
		share_val = price;
		set_tot();
	}
}

void Stock::sell(long num, double price)
{
	using std::cout;

	if(num < 0)
	{
		std::cout << "Numer of shares can't be negative, Transaction is aborted" << std::endl;
	}
	else if(num > shares)
	{
		cout << "You can't sell more than you have! Transaction is aborted." << std::endl;
	}
	else
	{
		shares -= num;
		share_val = price;
		set_tot();
	}
}

void Stock::update(double price)
{
	share_val = price;
	set_tot();
}

void Stock::show()
{
	std::cout << "Company: " << company << std::endl;
	std::cout << "Shares: " << shares << std::endl;
	std::cout << "Share price: " << share_val << std::endl;
	std::cout << "Total worth: " << total_val << std::endl;
}
```

### 内联方法
`规定`:

定义在类声明中的函数将自动成为内联函数,比如Stock::tot()就是一个内联函数

如果愿意,可以在类声明之外定义成员函数使其成为内联函数,比如:

    inline void Stock::show(){...}

## III.类的构造函数
- 与JAVA的构造器相似,构造函数不需要声明返回值类型
- 可使用`this->`来使用类变量
- 如何使用构造函数:

    1. 显式调用    Stock s1=Stock("Nanoss",1,1);
    1. 隐式调用    Stock s2("Nanoss",1,1);
    1. 与new运算符搭配    Stock *s3=new Stock("Nanoss",1,1);
- 默认构造函数:
    默认构造函数是在未提供显式初始值时,用来创建对象的构造函数,类似于
        
        Stock s1;

    创建默认构造函数的两种办法:

    1. 重载构造函数 
        
        Stock(){company="no name";share=0;share_val = 0.0;total_val = 0.0;} 
    2. 在构造函数中增加默认值
    
            Stock::Stock(const std::string &company="Error", long shares=0.0, double share_val=0.0)
    但这两种方法不能同时存在
## IV. 析构函数
就像new和delete成对出现一样,构造函数和析构函数也需要同时存在

析构函数定义如下:

    Stock::~Sotck(){}
- 析构函数在类名前加上波浪线
- 无返回值和声明类型
- 无参数
- 如果你没有声明一个析构函数,编译器会为你隐式的声明一个析构函数
- 类对象过期后,析构函数会被自动调用
### 类对象什么时候过期?

通常不应在代码中显式地调用析构函数
- 如果创建的是静态存储类对象,则其析构函数将在程序结束时自动被调用
- 如果创建的是自动存储类对象(就像前面的示例中那样),则其析构函数将在程序执行完代码块时(该对象是在其中定义的)自动被调用
- 如果对象是通过new创建的,则它将驻留在栈内存或自由存储区中,当使用delete来释放内存时,其析构函数将自动被调用


## V.const成员函数
考虑下面代码:

    const Stock s1={"qwe"};
    s1.show();
该代码段中,s1被声明为const类型,即s1不可修改,但在后面又调用了show方法,无法保证show方法不会对s1的数据进行修改

所以可以在函数声明和定义时后面加上const来保证不会修改:

    void show();   -->>  void show() const;

## VI.对象数组
声明对象数组的方法和声明基本数据类型数组相同
  
  Stock s[4];
写下上面的语句后,s数组里的四名成员就已经用默认构造函数生成出来,此时你就可以使用这4个对象

`当然你也可以自己输入参数逐个声明对象`
