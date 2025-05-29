## 结构体与向量
定义一个结构体：

```c
struct s{
    int a;
    int b;
};
```
创建一个向量：
```c
vector<s> v;
```

可以直接使用`emplace_back`向这个结构体向量中添加新的项
```c
v.emplace_back({1,2});
//如果要使用下面的这种方法需要先在结构体中写一个构造函数
v.emplace_back(1,2);
```

关于构造函数，有两种常用写法：
- 写法一：
```c
bl(int _a, int _b, int _g, int _k)
	  : a(_a)    // 用参数 _a “直接初始化”成员 a
	  , b(_b)
	  , g(_g)
	  , k(_k)
	{
	  // 这里已经完成了成员的初始化，函数体里通常留空或写额外逻辑
	}
```
- 写法二：
```c
	bl(int a,int b,int g,int k){
		this->a=a;
		this->b=b;
		this->g=g;
		this->k=k;
	}
```

`q.size()` 返回的类型为size_t（无符号），如果容器特别大，这里会发生截断或溢出，可以改成下面的形式：
```c
size_t temp = q.size();
// 或者
auto   temp = q.size();
```

## 结构体作为参数传递给函数
```c
bool check(bl q, int x, int y) { … }
```
比如这个函数，其中bl为一个结构体，这样写会把整个 bl 结构体拷贝一份进去，更常写的结构是下面这种，即使用引用
```c
bool check(const bl& item, int x, int y) { … }
```
关于两种写法的进一步分析比较：
```c
// 按值
bool check(bl q, int x, int y) {
    // 可以放心地修改 q，但改的是局部副本
    int sumA = q.a + q.g;
    q.a = 0;  // 只影响副本，不影响外面的 vector 元素
    return sumA >= x && (q.b + q.k) >= y;
}

// 按 const 引用
bool check(const bl& item, int x, int y) {
    // 只读访问：不能写 item.a = ...（编译报错）
    int sumA = item.a + item.g;
    // item.a = 0; // ❌ 错误：不能修改 const 引用
    return sumA >= x && (item.b + item.k) >= y;
}
```

而且使用了const引用后就可以使用下面的方式进行赋值，const bl& 可以接受右值或匿名临时对象

```c
// 按值版不能直接这样写（因为按值要有个变量）：
check(bl{1,2,3,4}, x, y); // 需要先造个临时再拷贝

// 按 const 引用就可以直接：
check({1,2,3,4}, x, y);
```

