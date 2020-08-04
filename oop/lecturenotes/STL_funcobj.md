# STL: 函数对象

## Abstract
- 函数对象

## 函数对象

> 函数名 = 指向函数的指针

- 函数指针的声明：
```cpp
    void (*func)(int&);  // <-
// 返回值 | 声明的变量名    参数列表
//     指针符号
```

- 利用auto自动推断函数类型：
```cpp
auto func = flag==1?increase:decrease;
for(int &x : arr) { func(x);}
```

### 应用举例：**std::sort()**

`std::sort(arr, arr + n, comp);`

```cpp
template <class Iterator, class Compare>
void sort(Iterator first, Iterator last, Compare comp);
```

Compare就是comp的类型：函数指针

bool (*)(int,int)

STL提供了预定义的比较函数 (#include \<functional\>)
```cpp
sort(arr, arr+5, less<int>())  
sort(arr, arr+5, greater<int>())
// 为何有括号？
```

### greater\<int\>() 是一个对象

- greater是一个模板类
- greater\<int\> 是用int实例化的类
- greater\<int\> 该类的一个对象

同时，它表现得像一个函数
```cpp
auto func = greater<int>();
cout << func(2,1) << endl;
```
因此这种对象被称为函数对象

### 如何实现函数对象

```cpp
template<class T>
class Greater {
puclic:
    bool operator()(const T &a, const T &b) const {
        return a > b;
    }
};
```
注意三个const:
- 排序时comp不能修改数据
- 一般情况下comp也不应该修改自身

### 函数对象的要求
- 重载operator()运算符
- 需要是public访问权限

> 如果一个物体，叫声像鸭子，走路像鸭子，那么它就是鸭子
> —— Duck Typing

### 例子：一个简单计算器
见课件

### std::function类

std::function类，来自\<functional\>头文件

为**函数指针与对象**提供了**统一的接口**

```cpp
//  function<返回值(参数列表)>   arr[] = { some func_ptr/obj }, 
//                              var = func_ptr/obj;

function<string()> readArr[] = {readFromScreen, ReadFromFile()};
function<string(string)> calculateArr[] = {calculateAdd, CalculateMul()};
function<void(string)> writeArr[] = {writeToScreen, WriteToFile()};
```

### 对比几种实现方式

#### 使用虚函数实现
- 需要构造基类和子类
- 晚绑定

#### 使用模板实现
- 可以支持函数指针和函数对象（通过模板，自动重载实现）
- 早绑定（编译器绑定）

#### 使用std::function实现
- 也可以支持函数指针和函数对象（通过function的多态）
- 晚绑定（运行时绑定）

![avatar](pics/func_obj_excercise.png)
