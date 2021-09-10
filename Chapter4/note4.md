# 复合类型
## I. 数组
### 数组的初始化
- 只有在定义数组时才能使用初始化,之后就不能使用了
- 不能把一个数组赋给另一个数组,程序如下:

        int a[] = {1,2,3,4};
        int b[4] ;
        b = a;
    错误:表达式必须是可修改的左值
- 初始化数组时,提供的值可以少于数组的元素数目

        int a[5]={1,2,3};  //OK
- 若只对数组的一部分初始化,则编译器把其他元素全部置为0  
  
        int a[4]={1};
    
    此时a数组中第一个元素为1,其他都为0
- 想要置零还有另一种办法:不再大括号内包含任何东西:

        int a[3]={};
- 初始化数组时方括号内为空,C++编译器会自动计算元素个数:

        int a[]={1,2,3};
    编译器使a数组包含3个元素
- 初始化时禁止缩窄操作:
    缩窄操作即由高精度的数据存储为低精度的数据

            long a[]={123,3,3.0};   //not allowed
            char b[]={'a','\n',12345};  //not allowed
            char c[]={'a','\n',12};     //allowed

## II.字符串
### 字符串与字符数组

    char a[8]={'a','b','c','d'};
    char b[8]={'a','b','c','d','\0'};
字符串与字符数组最大的区别就是最后有没有'\0'终止符,其ASCII码为0

程序只有遇到'\0'才会终止,而在内存中有很多值为0的内存空间,所以即时一个字符数组最后没有加'\0'也会很快停止.

### 字符串常量

    char a[11]="hfhf";
上面就是一句声明字符串常量的语句  他会在结尾隐式的加上空字符

此外应确保数组要足够大  能够存储字符串中的所有字符,`包括空字符`

### 拼接字符串常量

当一个字符串太长,无法放到一行中时,C++允许拼接字符串常量值,它可以将两个用引号括起的字符串合并成一个

事实上,任何两个有空白(空格、制表符和换行符)分割的的字符串常量都将自动拼接成一个

下面的三条语句是等效的:

    cout << "asdzxc""qwe\n";

    cout<<"asdzxcqwe\n";

    cout<<"asdzxc"
    "qwe\n";
均输出asdzxcqwe

### 在数组中使用字符串

将字符串存储到数组中 有两种方法:
- 将数组初始化为字符串常量
- 将键盘或文件输入读入到数组中

        char n1[15];
        char n2[15] = "C++owboy";
        cin >> n1;
        cout << strlen(n2) << " " << sizeof(n2); //8 15
#### sizeof 与 strlen
strlen只会计算可见的字符,即\0之前的字符个数,所以空字符不会计算在内

sizeof会计算整个数组的长度

### 每次读取一行字符串

若用cin读取"New York"时,读取到的字符只会是New

所以使用cin中的类函数getline() 和 get()可以解决这个问题

二者都会读取一行输入,直到到达换行符

而随后getline会丢弃换行符,get将换行符保留在输入缓冲区中

- cin.getline()
  
该函数有两个参数:
- - 第一个参数用来存储输入行的数组的名称
- - 第二个参数是要读取的字符数 
  
如果该参数是20,则只能读取最多19个字符,余下的空间用于`存储自动添加的空字符`

假如要使用getline()将姓名读取到一个包含20个元素的name数组中:

    cin.getline(name,20);


- cin.get()

get()不会读取和丢弃换行符,而是将其保存在缓冲区中

比如:

    cin.get(name,15);
    cin.get(dessert,15);
第一次调用后,换行符将留在输入队列中,因此第二次到用时看到的第一个字符便是换行符.

因此get()认为已到达行尾,而没有发现任何可读取的内容

**如何解决cin.get()无法丢弃换行符的问题:**

可以使用不带参cin.get()读取下一个字符(即使是换行符):

    cin.get(name,15);
    cin.get()  //读取换行符
    cin.get(dessert,15);

还可以使用:

    cin.get(name,15).get();
之所以可以这么做,是因为cin.get(name,15)返回一个cin对象

同理cin.getline()也会返回cin对象

### 混合输入数字和字符串

考虑下面代码:
```cc
    cout << "What year was your house built?\n";
    int year;
    cin >> year;
    // cin.get();
    cout << "What is its street address?\n";
    char address[80];
    cin.getline(address, 80);
    cout << "Year built: " << year << endl;
    cout << "Address: " << address << endl;
```
为year赋值时,假如输入1222(回车)

只会将1222存储到year中  回车键还在缓冲区中  

这时就需要cin.get()来读取换行符,或者使用下面代码:

    (cin>>year).get()
## III. string类
string对象与字符数组几乎相同
    
    string s1;         创建一个空字符串
    string s2="abcd";  初始化一个字符串,并赋值为"abcd"

### string的赋值
```cpp
    char ch1[20];
    char ch2[20]="jaguar";
    ch1=ch2;  //非法,数组不能赋值

    string s1;
    string s2="panther";
    s1=s2;    //合法
```

### string的拼接
```cc
    string s1="asd",s2="qwe",s3;
    s3=s1+s2;
    s3+=s2;
    cout << s1 << " " << s2 << " " << s3; //asd qwe asdqweqwe
```

### string的求长度
```cpp
    string s1="asd";
    int a=s1.size();
    cout<<a;   //3
```

注意：

string类获取字符串长度的方法是`string对象名.size()`
     
而char数组类型获取字符串长度的方法是`strlen(数组名)`

### string的I/O

可以用cin>>来将输入存储到string对象中,cout<<来显示string对象

但当每次都一行而不是一个单词时,应该使用如下语法:
```cpp
string s1;
getline(cin,s1);
cout<<s1;
```
此时直接使用getline函数,且cin为参数,不需要长度限定值
## IV.原始字符串
在原始字符串中,字符表示他们自己

例如:

\n不表示换行符而表示\ 和 n

### 原始字符串的使用

使用"(和)"作为定界符

例如:

    string a=R"(jim "King" uses "\n| instead of endl.)";

### 原始字符串的拓展

由上面知道,原始字符串会将"(  )"之间的内容当成字符串

那么如果想要在字符串中包含)"  时该怎么办?

`可以在" 和 ( 之间加上任意其他字符  这表示字符串结尾的 " 和 ) 也必须包括这个被添加的字符` 

例如,可以在" 和 ( 之间添加! 作为添加字符:

```cc
    string a = R"!(jim "King" uses "\n)" instead of endl.)!";
    cout<<a;     //jim "King" uses "\n)" instead of endl.
```

这里的!可以换成任意字符  逗号,句号,问号,加号等等均可以

**但空格 左括号 右括号 斜杠 控制字符除外**

## V. 联合(union)

联合是一种数据格式,他能存储不同的数据类型,但只能同时存储器中的一种类型

```cpp
union one4all{
    int int_val;
    long long_val;
    double double_val;
};

    one4all pail;  
    pail.long_val = 15;       //pail内存储了一个long值
    cout << pail.long_val << endl;
    pail.double_val = 1.2F;    //pail内存储了一个double值  并且原来的long值丢失
    printf("%f", pail.double_val);
```

由于联合一次只能存储一个值,因此它必须有足够的空间来存储最大的成员，即`联合的长度为其最大成员的长度`


联合的用途之一:
- 当数据项使用两种或多种格式(且不同时使用)时,可以节省空间,比如管理一个小商品目录,有一些商品的ID为整数 有的ID是字符串  这种情况下可以这么做:

```cc
    struct widget
    {
        char brand;
        int type;
        union id
        {
            long id_num;
            char id_char[20];
        } id_val;          //这里要给一个变量名
    };

    widget item;
    if (item.id_val.id_num == 1)
    {
        printf("%d", item.id_val.id_num);
    }
    else
    {
        printf("%s", item.id_val.id_char);
    }
```

### 匿名联合

即联合可以没有名称,其成员将成为位于相同地址处的变量,将上述代码中的联合转为匿名联合后可如下使用:

```cc
    struct widget
    {
        char brand;
        int type;
        union
        {
            long id_num;
            char id_char[20];
        };
    };

    widget item;
    if (item.id_num == 1)
    {
        printf("%d", item.id_num);
    }
    else
    {
        printf("%s", item.id_char);
    }
```

由于联合是匿名的,因此id_num 和 id_char 被视为widget的两个成员,他们的地址相同,所以不需要中间标识符id_val

`联合还常用于节省内存`,尤其是在嵌入式系统编程时,内存是十分宝贵的,使用联合可以有效降低内存占用


## VI.指针

- 一种类型的指针只能指向一种指定的类型,考虑下面代码
```cc
    int a=1;
    double *p=&a;
```
上面代码会报错:

"int *" 类型的值不能用于初始化 "double *" 类型的实体

- 虽然每种类型的指针指向不同长度的数据类型,但是指针的长度都是相同的,即地址长度相同
- 创建指针时,计算机将分配用来存储地址的内存,但不会分配用来存储指针所指向的数据的内存

考虑下面代码:
```cc
    int *a;
    *a = 2233;
```
创建a指针时,只为其开辟一段内存空间,却没有储存地址,因此2233可能被储存在任何位置

`在对指针取值(*)之前,一定要将指针初始化为一个确定的、适当的地址`

### new操作符

    数据类型 * 指针名 = new 数据类型;

```cpp
    int *a = new int;
    *a = 1;
```
`new分配的内存块通常在堆中`

`由常规变量声明的值储存在栈中`

###  delete操作符
为了防止内存被耗尽,需要将不用的内存空间释放掉,可以使用delete操作符实现

    delete 指针名;
```cpp
int *ps=new int;
delete ps;
```
这将释放ps指向的内存,但不会删除指针ps本身 

这意味着你还可以将ps重新指向另一个新分配的内存块

`注意`:
- 一定要成对使用new delete操作符
- 不要尝试释放已经释放的操作符
- delete只能释放通过new分配的内存
```cc
int *ps =new int;
delete ps;
delete ps;      //不需要
int a=5;
int * p=&a;
delete p;      //不要用delete释放由变量分配的内存
```

### 用new 创建动态数组
    int *p=new int [10];
同样的用delete释放数组时:
    delete [] p;

### 指针 数组

分析下面两个语句:
    
    short *p [20];
    short  (*p)[20];

第一个是一个有20个short类型指针组成的数组

第二个指的数组指针 他是指针 指向一个含有10个元素的数组


代码如下:
```cpp
1    int **p = new int* [20];
2    int i_p[20];
3    int (*p1)[20] =&i_p;
4    for (int i = 0; i < 20; i++)
5    { 
6		p[i] = (int *)i;
7       cout << "(p+i) = " << (p + i) << " *(p+i) = " << *(p + i) << endl;
8    }
```

`注意:`在第6行必须使用(int *)将i转换成地址值,因为p[i]储存的是int类型的地址


运行结果如下:
```cpp
// (p+i) = 0x151a30 *(p+i) = 0
// (p+i) = 0x151a38 *(p+i) = 0x1
// (p+i) = 0x151a40 *(p+i) = 0x2
// (p+i) = 0x151a48 *(p+i) = 0x3
// (p+i) = 0x151a50 *(p+i) = 0x4
// (p+i) = 0x151a58 *(p+i) = 0x5
// (p+i) = 0x151a60 *(p+i) = 0x6
// (p+i) = 0x151a68 *(p+i) = 0x7
// (p+i) = 0x151a70 *(p+i) = 0x8
// (p+i) = 0x151a78 *(p+i) = 0x9
// (p+i) = 0x151a80 *(p+i) = 0xa
// (p+i) = 0x151a88 *(p+i) = 0xb
// (p+i) = 0x151a90 *(p+i) = 0xc
// (p+i) = 0x151a98 *(p+i) = 0xd
// (p+i) = 0x151aa0 *(p+i) = 0xe
// (p+i) = 0x151aa8 *(p+i) = 0xf
// (p+i) = 0x151ab0 *(p+i) = 0x10
// (p+i) = 0x151ab8 *(p+i) = 0x11
// (p+i) = 0x151ac0 *(p+i) = 0x12
// (p+i) = 0x151ac8 *(p+i) = 0x13
```

### char数组和string类在输入上的区别

```cpp
    char word[8];
    string a;
	cin.getline(word,8);
	getline(cin,a);
```
**char类型用cin.getline(数组名,限定长度)来为char数组赋值**

**string类用getline(cin,string变量名)来为string变量赋值**
