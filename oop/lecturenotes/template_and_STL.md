
# 模板与STL初步

## Abstract

- 类模板与函数模板特化
- 命名空间
- STL初步——容器与迭代器

## 函数模板特化

有时，有些类型并不合适，则需要对模板在某种情况下的具体类型进行特殊处理，称为“模板特化”

特化方式：
```cpp
// 基础模板
template <typename T> T sum(T a, T b)
```
- 在函数名后用<>括号括起具体类型
  ```cpp
  template<> char* sum<char*>(char*a, char*b)
  ```
- 由编译器推导出具体类型，函数名为普通形式
  ```cpp
  template<> char* sum(char* a, char* b)
  ```

Example
```cpp
#include <iostream>
using namespace std;

template<class T>
T div2(const T& val)
{
    cout << "using template" << endl;
    return val / 2;
}

template<>
int div2(const int& val) //函数模板特化
{
    cout << "better solution!" << endl;
    return val >> 1; //右移取代除以2
}
```

**注意**：对于**函数模板**，如果有多个模板参数，则特化时必须提供所有参数的特例类型，不能部分特化

但可以用重载来代替部分特化

```cpp
#include <iostream>
using namespace std;

template<class T, class A>
T sum(const A& val1, const A& val2)
{
    cout << "using template" << endl;
    return T(val1 + val2);
}

template<class A>
int sum(const A& val1, const A& val2)
{   //不是部分特化，而是重载函数
    cout << "overload" << endl;
    return int(val1 + val2);
}

int main()
{
    float y = sum<float, float>
                (1.4, 2.4);
    cout << y << endl;
    int x = sum(1, 2);
    cout << x << endl;
    return 0;
}
```

### 函数模板重载解析顺序：  
类型匹配的普通函数->基础函数模板->全特化函数模板
- 如果有普通函数且类型匹配，则直接选中，重载解析结束
- 如果没有类型匹配的普通函数，则选择**最合适**的基础模板
- 如果选中的基础模板有**全特化版本**且**类型匹配**，则选择全特化版本，否则使用基础模板

```cpp
template<class T> void f(T) { 
  //func1为基础模板
  cout<< “full template” <<endl;}; 
template<class T> void f(T*) {
  //func2为func1的重载，仍是基础模板
  cout<< “full template -> overload template” <<endl;};
template<> void f(char*) {
  //func3为func2的特化版本(T特化为char)
  cout<< “overload template -> specialized” <<endl;}; 
int main() { 
    char *p; 
    f(p);       //最终调用了func3
    return 0;
}
// 优先匹配特化版本，前提是被特化的对应**基础函数模板**被匹配到
```
进一步的例子见课件

## 类模板特化

```cpp
// 通用模板
template<typename T1, typename T2> class A {};

// 全部特化
template<> class A<int,int> {};

// 部分特化
template<typename T1> class A<T1,int> {};
```

## Summary on Template Specifying

**类模板**可以**部分特化**或者**全部特化**，编译器会根据调用时的类型参数自动选择合适的模板类

**函数模板**只能**全部特化**，但可以通过**重载**代替部分特化的实现。编译器在编译阶段决定使用特化函数或者标准模板函数

函数模板的全特化版本的匹配优先级**可能低于**重载的非特化基础函数模板，因此最好不要使用全特化函数模板而直接使用重载函数

## 命名空间

```cpp
// 定义命名空间：
namespace A {
  int x,y;
}
// 使用命名空间：
A::x = 3;
A::y = 6;

// 使用using声明简化命名空间使用

// 使用整个命名空间
using namespace A;
x=3; y=6;

// 使用部分成员：所选成员可直接使用
using A::x;
x = 3; A::y = 6;
```

## STL初步

> Standard Template Library

包含4个组件：
- 算法
- 容器
- 函数
- 迭代器

基于模板编写

关键理念：将“在数据上执行的操作” 与 “要执行操作的数据” 分离

命名空间：std （不推荐在大型工程中使用using namespace std;容易污染命名空间）

### STL容器

- Simple container
- Sequence container
- Associative container

#### pair
```cpp
std::pair<int,int> t;
t.first = 1, t.second = 2;
auto t = std::make_pair("abc", 7.8); // Automatically induce the type

// 支持<,>,==等，先比较first再比较second
```

#### tuple

```cpp
v0 = std::get<0>(tuple1);
v1 = std::get<1>(tuple2);

auto t = std::make_tuple("abc",7.8,123,'3');

std::string x; double y; int z;
std::tie(x, y, z) = std::make_tuple("abc", 7.8, 123);
// tie返回左值引用的元组
```

#### vector

```cpp
std::vector<int> x;

x.size();

x.clear();

x.push_back(1); 
x.pop_back();

x.insert(x.begin()+1, 5);
x.erase(x.begin()+1);
```

#### list

```cpp
std::list<int> l;

l.push_front(1);
l.push_back(2);

std::find(l.begin(),l.end(),2); // 返回迭代器

l.insert(iter,4);

```

#### set

```cpp
std::set<int> s;

s.insert(1);

iter = s.find(1); // find返回迭代器！容器内部排列顺序按照大小顺序

s.erase(s.find(1));

s.count(1); // Returns 0 or 1;
```

#### map
> 值类型为 pair<Key,T>


```cpp

std::map<std::string, int> s;
s["oop"] = 1;
s.insert(std::make_pair(std::string("oop"),1));

iter = s.find(key);
cnt = s.count(key);
s.erase(iter);
```

### 迭代器

```cpp

vector<int>::iterator iter;

vector<int> x;
iter = x.begin();
iter = x.end();

++iter;
iter += n;
*iter = 5;  // 解引用运算符返回左值引用

int dist = iter1 - iter2;

for(vector<int>::iterator it = vec.begin();
    it != vec.end(); ++it) continue;

for(auto it = vec.begin(); it != vec.end(); ++it) continue;

for(auto x: vec) continue;
//等价于上上面那一行
```


