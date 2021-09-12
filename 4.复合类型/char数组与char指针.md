考虑如下代码:

```cpp
char animal[20];
char *ps;
cin>>animal;
cout<<animal;
cin>>ps;
cout<<ps;
```

结果是animal里的内容可以正确打印

而ps里的内容不可打印

`原因:`
- char数组意味着在内存中开辟一段内存空间,因此我有权限在内存里进行读写操作
- 但是char指针只是指向一块内存区域,相当于空头支票,没有分配实际的内存空间,所以虽然不会报错,但是运行使会出问题

**更多信息可参考char指针与char数组.cpp**