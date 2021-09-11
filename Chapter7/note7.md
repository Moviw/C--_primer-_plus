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