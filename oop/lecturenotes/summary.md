
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


# STL与字符串处理

## Abstract
- string字符串类
- iostream输入输出流
- 字符串处理与正则表达式

## string 字符串类

```cpp
// Construct
string s0("Initital string");
string s1;
string s2(s0, 8, 3);    // src_str, start_idx, len
string s3("Another character sequence", 12);    // intercept first 12 chars
string s4(10, 'x');
string s5(s0.begin(), s0.begin()+7);

// convert to C style string(const char*)
const char* s = str.c_str();

// common funcs
cout << str[1];

int len = str.size();
int len = str.length();

str.clear();
if(!str.empty());

for(char c: str);

str.push_back('a');
str += 'a';

str.append(s2);
str += s2;

// input
cin >> firstname;   // read chars that can be seen until whitespace
getline(cin, fullname);
getline(cin, fullnames, '#');   // read until separator

// merge
string fullname = firstname + " " + lastname;   
// notice the time complexity will be the length of the generated string
// BEST USE operator+= or stringstream

// comparison
a == b;
a < b;

// num to string
to_string(1) == "1";
to_string(3.14) == "3.14";
to_string(3.1415926) == "3.141593"; // notice the precision lose
to_string(1+2+3) == "6";

// string to num
int a = stoi("2001");
std::string::size_type sz;
int b = stoi("50 cats", &sz);   // b=50, sz=2, the length of the num is read into var sz
int c = stoi("40c3", nullptr, 16);   // c = 0x40c3  hex
int d = stoi("0x7f", nullptr, 0);    // d = 0x7f  automatically induce the base
double e = stod("34.5");

```

## iostream 输入输出流

> What the hell is ostream?

![avatar](pics/stl_iostream.png)

### 从 ostream 和 cout 开始

#### ostream
ostream是stl库中所有**输出流**的**基类**  
它重载了针对基础类型的输出流运算符 <<

#### cout
cout 是STL中内建的一个ostream对象

它会将数据送到**标准输出流**(usually the screen)

### Make your own ostream

> 哪个男孩不想拥有自己的ostream呢？

```cpp
class ostream
{
public:
    ostream& operator<<(char c)
    {
        printf("%c", c);
        return *this;
    }
    ostream& operator<<(const char* str)
    {
        printf("%s", str);
        return *this;
    }
}cout;

int main(){
    cout << "hello" << ' ' << "world";
    return 0;
}
```

实现原理：<<运算符为**左结合**

### 格式化输出

\#include \<iomanip\>  // input \ output manipulation

cout << **fixed** << 2018.0 << " " << 0.0001 << endl;  
				//浮点数 -> 2018.000000 0.000100  
cout << **scientific** << 2018.0 << " " << 0.0001 << endl;  
				//科学计数法 -> 2.018000e+03 1.000000e-04  
cout << **defaultfloat**;  //还原默认输出格式  
cout << **setprecision(2)** << 3.1415926 << endl;  
				//输出精度设置为2 -> 3.2  
cout << **oct** << 12 << " " << **hex** << 12 << endl;   
				//八进制输出 -> 14  十六进制输出 -> c  
cout << **dec**;	//还原十进制  
cout << **setw(3)** << **setfill('*')** << 5 << endl;  
				//设置对齐长度为3，对齐字符为* -> **5  

**fixed scientific setprecision** 等都是 **流操纵算子**，大致分为两种：不带参数（规范有定义）、带参数（规范无定义）

### 流操纵算子 stream manipulator

借助辅助类设置成员变量

setprecision(2)是一个类的对象

一种实现方式的示例：
```cpp
class setprecision
{
private:
    int precision;
public:
    setprecision(int p) : precision(p) {}
    friend class ostream;
};

class ostream
{
private:
    int precision;
public:
    ostream& operator<<(const setprecision &m){
        precision = m.precision;
        return *this;
    }
} cout;
```

#### endl

> C++标准中endl的声明：ostream& endl(ostream& os);

endl 是一个函数，可以调用endl(cout);
```cpp
ostream& endl(ostream& os) {
    os.put('\n');
    os.flush();
    return os;
}
```
它同时又是一个流操纵算子 cout << endl;
```cpp
//实现方式示例
ostream& operator<< (ostream& (*fn)(ostream&)) {    // 流运算符重载，函数指针作为参数
    return (*fn)(*this);
}
```

#### cout

> 不能复制

重载流运算符需要返回**引用**，避免复制

```cpp
ostream(const ostream&) = delete;
ostream(ostream&& x);
```
**禁止复制，只允许移动**

仅使用cout一个全局对象
- 避免复制开销
- 一个对象对应一个标准输出，符合oop思想
- 多个对象之间**无法同步输出状态**

## 文件输入输出流

> 以文件输入流为例子

ifstream是istream的子类，功能是从文件中读入数据

```cpp
ifstream ifs("input.txt");
ifstream ifs("binary.txt", ifstream::binary);

ifstream ifs;
ifs.open("file");
// do something
ifs.close();
```

Example

```cpp
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

int main() {
    ifstream ifs("input.txt");
    while(ifs) {			//判断文件是否到末尾 利用了重载的bool运算符
        ifs >> ws;  		//除去前导空格 ws也是流操纵算子
        int c = ifs.peek();		//检查下一个字符，但不读取
        if (c == EOF) break;
        if (isdigit(c))			//<cctype>库函数
        {
            int n;
            ifs >> n;
            cout << "Read a number: " << n << endl;
        } else {
            string str;
            ifs >> str;
            cout << "Read a word: " << str << endl;
        }
    }
}
```

其他操作
```cpp
getline(ifs, str);

char c = ifs.get();
ifs.ignore(int n=1, int delim=EOF); // omit n chars, or until delim separator
char c = ifs.peek();
ifs.putback(c);
ifs.unget();
```

## 字符串输入输出流

> 以输入输出流为例子

**stringstream**是**iostream**的子类  
**iostream**继承于**istream**和**ostream**  
// 多重继承！  
**stringstream**实现了输入输出流双方的接口

### stringstream

- 在对象内部维护了一个buffer
- 使用流输出函数可以将数据写入buffer
- 使用流输入函数可以从buffer中读入数据
- **一般用于程序内部的字符串操作**

```cpp
stringstream ss;
stringstream ss(str);
```

#### What can it do?

- 连接字符串
- 将字符串转换为其他类型的数据
- 配合流操作算子达到格式化输出效果

#### 获取stringstream的buffer

![avatar](pics/stringstream_buffer.png)

#### 实现一个类型转换函数

```cpp
template<class outtype, class intype>
outtype convert(intype val)
{
	static stringstream ss;
						//使用静态变量避免重复初始化
	ss.str(""); 	//清空缓冲区
	ss.clear(); 	//清空状态位（不是清空内容）
	ss << val;
	outtype res;
	ss >> res;
	return res;
}
```

# 正则表达式

## 三种模式

- 匹配
- 搜索
- 替换

## 匹配

- **字符代表其本身**  
  > The car parked in **the** garage.
- **转义字符**  
  > \n、\t etc
- **特殊匹配字符** 
  > ^字符串开头  
  $字符串结尾  

### 字符簇 [ ]

- **匹配的*****单个*****字符在某个范围中**
- - [aeiou]
- - [a-z]
- - [0-9]
- **范围取反**
- - [^a-z] 匹配所有非小写字母的单个字符
- - [^c]ar: The car **par**ked in the **gar**age.
- **连用**
- - [a-z][0-9] : **a1**、**b9** ...
- - ^[^0-9][0-9]$ : **?2**、**g5**、**-1** ...
- - [Tt]he : **The** car parked in **the** garage.
- **特殊字符**
- - |字符|匹配|
    |----|----|
    |.|除换行以外任意字符|
    |[.]或\\.|匹配句号|
    |\d|等价[0-9]|
    |\D|[^0-9]|
    |\s|所有空白字符如\t\n|
    |\S|所有非空白字符|
    |\w|字母、数字、下划线（[a-zA-Z0-9_]）|
    |\W|[^a-zA-Z0-9_]|

### 重复模式

- **x{n,m} 重复n~m次**
- - a{4} : aaaa
- - a{2,4} : aa aaa aaaa
- - a{2,} : 长度大于等于2的a
- **拓展到字符簇**
- **特殊字符**
- - |特殊字符|等价|
    |----|----|
    |?|{0,1}|
    |+|{1,}|
    |*|{0,}|

### 或连接符

#### 匹配模式可以使用 **|** 进行连接

Examples:
- (Chapter|Section) [1-9][0-9]?
- - > **Chapter 1**    **Section 10**
- 0\d{2}-\d{8}|0\d{3}-\d{7}
- - > **010-12345678**   **0376-2233445**
- (c|g|p)ar

#### 使用()改变优先级

- m|food    -----    m或food
- (m|f)ood  -----   mood或food
- (T|t)he|car   ----- The、the、car

## 正则表达式库 \<regex\>
```cpp
regex re("^[1-9][0-9]{10}$");  // 11位数
```
Notice that "\\" is also a 转义字符 in Cpp string.
```cpp
regex re("\\d+");   \\ "\d+"
```

### 原生字符串

取消转义，保留字面值

Syntax:   **R"(str)"**

"\\d+" = R"(\d+)" = \d+

原生字符串支持换行

### 匹配

regex_match(s, re) : 询问字符串s能否完全匹配正则表达式re

### 捕获和分组

使用()进行标识，每个标识的内容被称作**分组**

- 正则表达式匹配后，每个分组的内容将被捕获
- 用于提取关键信息
 
`regex_match(s, result, re)`：  
询问字符串s是否能完全匹配正则表达式re，并将捕获结果储存到result中

result需要是smatch类型的对象

```cpp
#include <iostream>
#include <string>
#include <regex>
using namespace std;
int main () {
    string s("version10");
    regex e(R"(version(\d+))"); smatch sm;
    if(regex_match(s,sm,e)) {
        cout << sm.size() << " matches\n";
        cout << "the matches were:" << endl;
        for (unsigned i=0; i<sm.size(); ++i) {
            cout << sm[i] << endl;
        }
    }
    return 0;
}
```
> Output:  
2 matches  
the matches were:  
version10  
10  

#### 分组会按顺序标号
- 0号永远是被匹配的字符串本身
- 如果需要括号，又不想捕获该分组，可以使用 **(?:pattern)**

### 搜索

`regex_search(s, result, re)` : 搜索字符串s中能匹配正则表达式re的**第一个**子串，并将结果储存在一个smatch对象result中

Example:

```cpp
#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main() {
  string s("this subject has a submarine");
  regex e(R"((sub)([\S]*))");
  smatch sm;
  //每次搜索时当仅保存第一个匹配到的子串
  while(regex_search(s,sm,e)){
    for (unsigned i=0; i<sm.size(); ++i)
      cout << "[" << sm[i] << "] ";
    cout << endl;
    s = sm.suffix().str();  // suffix得到匹配部分的后面部分
  }
}
```

### 替换

`regex_replace(s, re, s1)` 替换s中**所有**匹配正则表达式re的子串，并替换成s1

- s1可以是一个普通文本
- 也可以使用一些**特殊符号**，代表捕获的分组  
  **\$\&** 代表re所有匹配成功的**子串**  
  **\$1, \$2** 代表re匹配的**子串中的**第1/2个**分组**

**Example**

```cpp
#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main() {
  string s("this subject has a submarine");
  regex e(R"((sub)([\S]*))");
  //regex_replace返回值即为替换后的字符串 
  cout << regex_replace(s,e,"SUBJECT") << "\n";
  //$&表示所有匹配成功的部分，[$&]表示将其用[]括起来
  cout << regex_replace(s,e,"[$&]") << "\n";
  //$i输出e中第i个括号匹配到的值
  cout << regex_replace(s,e,"$1") << "\n";
  cout << regex_replace(s,e,"$1 and [$2]") << "\n";
}
/*
输出：
this SUBJECT has a SUBJECT
this [subject] has a [submarine]
this sub has a sub
this sub and [ject] has a sub and [marine]
*/
```

## More on re...

### 预查

- **正向预查**  
  >现在，我们假设需要仅匹配 Windows，不匹配后面的版本号，并且要求 Windows 后面的版本号只能是 数字类型，换言之，XP 和 Vista 不能被匹配，  
  在正则表达式中，可以使用 正向预查 来解决这个问题。本例中，写法是：“Windows(?= [\d.]+\b)”。  
  它的语法是**在 子模式内部 前面加“?=”**，表示的意思是：首先，要匹配的文本**必须满足此子模式前面的表达式**(本例，“Windows ”)；其次，**此子模式不参与匹配**。  
  你也可以这样理解上面的匹配过程:  
  >1. 先进行普通匹配：Windows ([\d.]+\b)
  >2. 然后从匹配文本中**将 子模式 内的文本排除掉**。
  
  子模式内的文本由于不参与匹配，所以可以参与到后面的匹配中！
- **反向预查**
  就是子模式在表达式的前面

||正向|反向|
|----|----|----|
|**肯定**|xxx(?=pattern)|(?<=pattern)xxx|
|**否定**|xxx(?!pattern)|(?<!pattern)xxx|


### 后向引用

\b(\w+)\b\s+\1\b 匹配重复两遍的单词

比如go go 或 kitty kitty

![avatar](pics/re_back_reference.png)

### 贪婪与懒惰

默认多次重复为贪婪匹配，即匹配次数最多

在重复模式后加？可以变为懒惰匹配，即匹配次数最少

|贪婪型|懒惰型|
|----|----|
|\*|\*?|
|+|+?|
|{n,}|{n,}?|# STL: 函数对象

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
# 智能指针与引用计数

> A、B对象共享一个C对象，C不想交由外部销毁  
> 应当在A、B都销毁时C才能销毁  
> 如何自动处理？

## 智能指针

**shared_ptr**  \<memory\>库
```cpp
#include <memory>
shared_ptr<int> p1(new int(1));
shared_ptr<MyClass> p2 = make_shared<MyClass>(2);
shared_ptr<MyClass> p3 = p2;
shared_ptr<int> p4;

int x = *p1;
int y = p2->val;

// p2和p3指向同一对象，当两者均出作用域才会被销毁！

```

## 引用计数

智能指针依靠**引用计数**来判断何时销毁对象

```cpp
#include <memory>
#include <iostream>
using namespace std;
int main()
{
	shared_ptr<int> p1(new int(4));
	cout << p1.use_count() << ' '; // 1
	{
		shared_ptr<int> p2 = p1;
		cout << p1.use_count() << ' '; // 2
		cout << p2.use_count() << ' '; // 2
	}	//p2出作用域
	cout << p1.use_count() << ' '; // 1
}
```

### 实现自己的引用计数
> 哪个男孩不想拥有属于自己的引用计数呢？

```cpp
template <typename T>
class SmartPtr;

template <typename T>
class U_Ptr {
private:
    friend class SmartPtr<T>;
    U_Ptr(T *ptr) : p(ptr), count(1) {}
    ~Uptr() { delete p;}

    int count;  // 引用计数
    T *p;   // 实际数据存放
};

class SmartPtr {
    U_Ptr *rp;
public:
    // 构造函数：初始化成员辅助指针rp，将类型T的数据存放给rp
    SmartPtr(T *ptr) :rp(new U_Ptr<T>(ptr)) {}
    // 拷贝构造函数：先初始化rp为来源rp，并将rp的计数+1
    SmartPtr(const SmartPtr<T> &sp) :rp(sp.rp) {
        ++rp->count;
    }
    // 赋值运算符：将原先的引用计数-1，如果为0则删除；再换新的rp
    SmartPtr& operator=(const SmartPtr<T>& rhs) {
        ++rhs.rp->count;
        if(--rp->count == 0)
            delete rp;
        rp = rhs.rp;
        return *this;
    }
    // 析构
    ~SmartPtr() {
        if (--rp->count == 0)
            delete rp;
    }
    T& operator *() {return *(rp->p); }
    T* operator ->() {return rp->p;}
};

int main(int argc, char *argv[]) {
    int *pi = new int(2);
    SmartPtr<int> ptr1(pi);
    SmartPtr<int> ptr2(ptr1);
    SmartPtr<int> ptr3(new int(3));
    ptr3 = ptr2;
    cout << *ptr1 << endl;  // 2
    *ptr1 = 20;
    cout << *ptr2 << endl;  // 20

    return 0; 
}

```

## shared_ptr的其他用法

```cpp
p.get() //获取裸指针
p.reset() // 清除指针并减少引用次数
static_pointer_cast<int>(p)
dynamic_pointer_cast<Base>(p)
```

注意！
- 不能使用同一个裸指针初始化多个智能指针，会产生多个辅助指针！
- 不能直接使用智能指针维护**对象数组**  
  因为删除数组需要delete[], 而智能指针所有的实现都是delete p;

## 智能指针并不总是智能的

当出现环状结构（如两个对象互相用智能指针指向对方）时，对象不能够正确地销毁

### How to fix this?

- 弱引用 **weak_ptr**     **指向对象但不计数**
  ```cpp
  shared_ptr<int> sp(new int(3));
  weak_ptr<int> wp1 = sp;

  //Usage:
  wp.use_count()
  wp.reset()    // 释放指针
  wp.expired()  // 检查对象是否无效
  sp = wp.lock()    // 从弱引用获得一个智能指针
  ```
- 独占所有权 **unique_ptr 保证对象只被一个指针引用**
  ```cpp
  auto up1 = std::make_unique<int>(20);
  unique_ptr<int> up2 = std::move(up1); // 可以移动unique指针(移交控制权)
  int *p = up2.release();               // 放弃指针控制权，返回裸指针
  delete p;
  ```

## 智能指针总结

### 优点
- 可以帮助管理内存，避免内存泄漏
- 区分unique_ptr和shared_ptr能够明确语义
- 在手动维护指针不可行，复制对象开销太大时，智能指针是唯一选择

### 缺点
- 引用计数会影响性能
- 智能指针不总是智能，需要了解内部原理
- 需要小心环状结构和数组指针# 并发编程与并发设计模式

## Abstract
- 并发编程
- thread与主从模式
- mutex与互斥锁模式
- async,future,promise与异步

## 并发编程

### “并发”与“并行”
- **一个时间段内**几个程序都处于启动到完成之间：**宏观上***同时*
- “并发”：任意时刻**只有一个程序**在计算单元上运行：**微观上***顺序执行*
- “并行”：任意时刻**可以有多个程序**运行：**微观上**也可以是*同时*

并发、并行都是**多任务**环境下的系统

### “进程”与“线程”

**进程 process**  
- 已运行的程序
  
**线程 thread**  
- 是操作系统能够进行**运算调度**的**最小单位**
- 它被包含在进程之中，是进程中的实际运作单位
- **一个进程**可以**并发多个线程**，设备允许的情况下，数个线程可以并行执行不同的任务
- 同一进程的多条线程**共享**该进程的全部**系统资源**，如虚拟地址空间，文件描述符和信息处理等

## thread与主从模式

### thread 类
示例：code/thread.cpp
- **默认构造函数**   
  定义：  
  `thread() noexcept;`  
  创建一个空线程对象，不代表任何可执行的线程  
  例：`thread s1;`
- **初始化构造函数**  
  定义：  
  ```
  template <class Fn, class ... Args> 
  explicit thread (Fn&&, Args&& ... args);
  ```
  注意：线程一旦创建，线程就开始执行
  - 可以与可调用对象（Callable Objects）一起使用
  - 如 Lambda 表达式
  - ```cpp
    thread t(
      [] (int a,int b) {
        cout << a + b << endl;
      }.
      1, 2);
      t.join();
    ```
- **拷贝构造函数**  
  **被禁用**，因为thread不可被拷贝构造（线程涉及系统底层）
- **移动构造函数**  
  定义：  
  `thread (thread&& x) noexcept;`
  有默认的移动构造函数，调用成功后x不指向任何具体执行线程

### join detach
thread提供了两种接口来处理当前线程与目标线程

- **thread::join()**  
  调用该接口时，当前线程会一直阻塞，直到目标线程执行完成
- **thread::detach()**
  - 调用此接口时，目标线程成为守护线程（daemon threads），将完全独立执行
  - 即使目标线程对应的thread对象被销毁也不影响线程的执行

### joinable
thread::joinable() 可以判断 thread实例指向的线程是否可以 join 或者 detach

三种情况下thread实例不是joinable：
- 默认构造函数创建的实例（不指向任何具体的执行线程）
- 被移动构造函数操作过的实例
- 已经调用过join()或者detach()的实例

启动目标线程后，必须决定当前线程是要等待目标线程结束（join），还是让目标线程独立（detach），**必须二选一**

如果目标线程的thread对象销毁时依然没有调用join或者detach，thread对象在析构时将导致程序进程异常退出

即thread**析构时必须是非joinable的状态**

### 相关功能性接口

- `this_thread::get_id`
- `this_thread::sleep_for`
- `this_thread::sleep_until`
- `this_thread::yield`

### 主从模式

示例：code/thread_prime.cpp

![avatar](pics/master_worker.png)

适用场景
- 整体任务可以被划分为诸多子任务
- 子任务间关联较弱，可以并发执行
- 计算设备支持多任务同时执行

## mutex与互斥锁模式

示例二：修改示例一：让每个子线程直接修改全局变量total

出错！

### 竞争条件与临界区

- 竞争条件  
  - 多个线程同时访问共享数据时，只要有一个任务修改数据，那么就可能会发生问题——多个线程同时争相修改数据，导致部分修改没有成功。这种场景称为**竞争条件（race condition）**
- 临界区  
  - 访问共享数据的代码片段称为**临界区（critical section）**，如示例中的total++;
- 避免竞争条件需要对临界区进行数据保护  
  - 一次只能让一个线程访问共享数据
  - 访问完了再让其他线程接着访问

### 互斥量mutex与锁lock()

互斥量mutex本身是一个类对象，一般也成为“锁”

- 各个线程可以**尝试用mutex的lock()接口**对临界区数据进行加锁
  - 每次只有一个线程能够锁定成功，标志是lock()成功返回
  - 如果没锁成功，则线程会阻塞在那里
  - 临界区**就像一间只能反锁的房间**
- mutex的unlock()接口可以解锁互斥量

实现方法（示例二）：
```cpp
// 全局变量
static mutex exclusive;

// 方法一：直接在total++;周围上锁
if(check_num(i)) {
  exclusive.lock();
  total++;
  exclusive.unlock();
}

// 方法二： 每个线程各自统计完之后再加入total
for (...) if(check_num(i)) tmp_total++;
exclusive.lock();
total+=tmp_total;
exclusive.unlock();

// 方法二效率更高，因为锁的开关需要时间，方法二的锁的调用次数更少
```

#### 互斥锁模式的弊端

- 低效——共享资源的读操作往往并不需要互斥
- 解决方案——采用**读写锁模式**，读是共享，写是互斥

### 其他互斥量

- timed_mutex
- recursive_mutex
- recursive_timed_mutex
- shared_mutex

## async、future、promise 与 异步

**案例三：** 需求：不断输入整数n,判断n是否为素数 async_prime.cpp

能否让输入不受判断方法的阻塞？

### 同步和异步

- **同步（Synchronous）**  
  同步调用一旦开始，调用者必须等到调用返回结果后才能继续后续的行为
  
  ![avatar](pics/synchronous.png)
- **异步（Asynchronous）**  
  异步调用一旦开始，被调用方法就会立即返回，调用者可以无阻塞继续后续的操作

  被调用方法通常会在另外一个线程中默默运行，整个过程，不会阻碍调用者的工作

  被调用方法完成后可以通过特殊机制传递信息给调用者

  ![avatar](pics/asynchronous.png)

### async

```cpp
future async (Fn&& fn, Args&&...args);
future async (launch policy, Fn&& fn, Args&&...args);
```

async会返回一个future对象，用来存储异步任务的执行状态和结果

policy有三种选择
- launch::async 保证异步行为，执行后，系统创建一个线程，执行对应的函数
- launch::deffered 表示延迟调用，在调用future中的wait()或者get()函数时，才执行入口函数
- launch::async||launch::deffered 默认策略，由系统自行决定怎么调用

### future

future类提供访问异步操作结果的接口
- **wait()** 接口，阻塞当前线程，等待异步线程结束
- **get()** 接口，获取异步线程执行结果
  - 需要注意的是，**future对象只能被一个线程获取值**，并且在调用get()之后就没有可以获取的值了
  - 如果多个线程调用同一个future实例的get()会出现数据竞争，其结果是未定义的
  - 调用get()如果异步线程没有结束会一直等待，类似wait()
- **wait_for(timeout_duration)** 如果在制定超时间间隔后仍然没有结束异步线程，则**返回目标线程当前状态**，并**取消wait_for的阻塞**
  - future_status::deferred 仍未启动
  - future_status::ready 结果就绪
  - future_status::timeout 已超时限，异步线程仍在执行

### 使用async和future完成案例三

构建运算不阻塞输入的程序：
- 使用异步线程进行运算
- 使用主线程进行状态管理
- 主线程**不断检查**输入状态和异步线程的执行状态：有输入立刻创建新的异步线程进行处理；某一个异步线程完成后，立刻输出处理结果

这种不断消耗极短时间进行检测的方式就是**轮询**

### 轮询

![avatar](pics/polling.png)

### promise

一般流程
- 在当前线程中创建promise对象，并从该promise对象中获得对应的future对象
- 将promise对象传递给目标线程，目标线程通过promise的接口设置特定值，**然后可以继续执行目标线程自身的工作**
- 在特定时间，当前线程按需求通过promise对应的future取值
# �����̳� Composition and Inheritance

## Abstract

1. ���
2. �̳�
3. ��Ա����Ȩ��
4. ��д����������
5. ���ؼ̳�

## ���

***����-����*** ��ϵΪ ***���*** �� *has-a* ��ϵ

### Example
```cpp
class Wheel{
    int _num;
public:
    void set(int n){_num=n;}
    Wheel(int n):_num(n){}
};

class Engine{
public:
    int _num;
    void set(int n){_num = n;}
    Engine(int n):_num(n){}
};

class Car{
private:
    Wheel w;
public:
    Engine e;       // public member-->access its interface directly
    void setWheel(int n){w.set(n);} // provide the interface of private member
    Car(int w_n,int e_n) : w(w_n),e(e_n){} // if the sub-object needs parameters,
                            // it should be initialized at the initialization list
};

int main(){
    Car c(4,1);
    //c.e.set(1);
    //c.setWheel(4);
    return 0;
}
```

���󿽱��븳ֵ���㣺 ��

## �̳�

"is-a"��"һ��-����" �ṹ

base class ����/����  
--> derived class ������/����/��չ��

### Way of Inheritance  
```cpp
class <Derived_Class_Name> : [private] <Base_Name> { .. }; // Default way of succession:private
class <Derived_Class_Name> : public <Base_Name> { .. };
class <Derived_Class_Name> : protected <Base_Name> { .. }; // Rarely used
```

### What **cannot** be Inherited
- ���캯��
- ��������
- ��ֵ�����    Includes the parameter which is of its class
- ��Ԫ����      Not member of the class  

### Example
```cpp
class Base{
public:
    k = 0;
    void f(){cout <<"Base::f()"<<endl;}
    Base& operator= (const Base& right){
        if(this != &right){
            k = right.k;
            cout << "operator=(const Base &right)" << endl;
        }
        return *this;
    }
};
class Derive:public Base();

int main(){
    Derive d;
    cout << d.k << endl;
    d.f();
    
    Base e;
    // d = e; // Compile Error: Base's operator= cannot be inherited
    return 0;
}
```

### ���������Ĺ���������

#### ���죺��Ҫ���û��๹�캯��
- û����ʽ���ã��Զ����ɶԻ����Ĭ�Ϲ��캯���ĵ���
- �ڹ��캯���ĳ�ʼ����Ա�б��н�����ʽ����
- - ���û����в���������Ĭ�Ϲ��캯��
- - ���ú��ʵĴ��������������캯��

```cpp
class Base{
    int data;
public:
    Base() : data(0) {cout << "Base::Base("<<data<<")\n";}
    Base(int i): data(i) {cout << "Base::Base("<<data<<")\n";}
};
class Derive : public Base{
public:
    // ע�⣺���´���ÿһ��Ϊ��ͬ�Ĺ��캯������ͬһ������ֻ��������һ��
    // 1.����ʽ���û��๹�캯�������û���Ĭ�Ϲ��캯��
    Derive() { cout << "Derive::Derive()"<< endl;}  
    // 2.��ʽ���û��๹�캯��
    Derive(int i) : Base(i) { cout << "Derive::Derive()"<< endl;}
    // 3.�̳л��๹�캯��
    using Base::Base; ///�൱�� Derive(int i):Base(i){}
    // ��������ڶ�����캯��ʱ,
    // ʹ��using����������Զ���������Ӧ�Ĺ��캯��
};
int main(){
    Derive obj1, obj2(356), obj3(356);
}
```
> Output:  
> 1:   
> Base::Base(0)  
> Derive::Derive()  
> 2:   
> Base::Base(356)  
> Derive::Derive()  
> 3:   
> Base::Base(356)  

#### ע��
- ��������ĳ�����캯��������Ϊ˽�У����������в��������̳иù��캯��
- ���������ʹ���˼̳й��캯�����������Ͳ�����Ϊ����������Ĭ�Ϲ��캯��

### How to choose way of inheritance

#### public Inherit
�����й��г�Ա���������б��ֹ��У�ԭ�ӿڿ�����  
is-a: ���������ʹ�õĵط������������Ҳ��ʹ��  
#### private Inherit
is-implementing-in-terms-of(�մ�ʵ��)���û���ӿ�ʵ�������๦�ܣ��Ƴ�is-a��ϵ  
ͨ����ʹ�ã�**��������**������������/��������Ĳ��ֽӿڡ�  
���������� �� public ���� ʹ�� using �ؼ���  
// ���๫�г�Ա���ӿڣ� �� ������˽�г�Ա�����ܣ�

## ��Ա����Ȩ��

|�̳б�||�̳з���|||
|----|----|----|----|----|
|||public|private|protected|
|�����|public|OK(pub/yes)|OK(prv/no)|OK(pro/no)|
|��Ա��|private|NO(prv/no)|NO(prv/no)|NO(prv/no)|
|����|protected|OK(pro/no)|OK(prv/no)|OK(pro/no)|

OK/NO : **�������Ա����**�ܷ���ʻ����Ա  
pub/pro/prv/ : �����Ա���������еĳ�Ա����  
yes/no : **���������**�ܷ���ʻ����Ա(//���ܷ���ú������ܶ�д����)

#### Some Notes  
- ������˽�г�Ա������ζ����ܱ������ࣨ����/��Ա���������ʡ���˽�е�����ʲôʱ����˽�еģ�  
- ������**����**���ɷ��ʻ����б�����Ա����**��Ա����**����

## �����̳� �Ա���ʵ��

�ԣ����μ�

## ��д����������

����Overload-->��̬��̬���������벻ͬ����������ͬ  
��д����Redefining-->�������Բ�ͬ

### ��д����

���λ����иó�Ա��������һ���غ���

����ͨ��`using ClassName::MemberName;`���������лָ�ָ���Ļ����Ա����

Example ��д����

```cpp
class T{};
class Base{
public:
    void f(){}
    void f(int i){}
    void f(double d){}
    void f(T){}
};
class Derive : public Base {
public:
    void f(int i) {}    //��д����
};
int main(){
    Derive d;
    d.f(10);
    d.f(4.9); // ����> d.f(4);
    // d.f();       // compiling error
    // d.f(T());    // compiling error
    return 0;
}
```
Example �ָ������Ա

```cpp
class T{};
class Base{
public:
    void f(){}
    void f(int i){}
    void f(double d){}
    void f(T){}
};
class Derive : public Base {
public:
    using Base::f;      // <------
    void f(int i) {}    //��д����
};
int main(){
    Derive d;
    d.f(10);            // From Derive           
    d.f(4.9);           // From Base
    d.f();              // From Base
    d.f(T());           // From Base
    return 0;
}
```

### using �ؼ���

- �̳л��๹�캯��
- �ָ������εĻ����Ա����
- ָʾ�����ռ� `using namespace std;`
- ����һ�������ռ�ĳ�Ա���뵱ǰ�����ռ� `using std::cout; cout<<endl;`
- �������ͱ���`using a = int;` 

## ���ؼ̳�

������ͬʱ�̳ж������
```cpp
class File{};
class InputFile: public File{};
class OutputFile: public File{};
class IOFile: public InputFile, public OutputFile{};
```
### ���ڵ�����

- ���ݴ洢  
  �̳еĶ����������ͬһ����ļ̳У������Ըû�������ݳ�Ա���ж�����������ܴ�����������
- ������  
  ͬ����Ա����--->�������



# �麯��

## Abstract

- ��������ת��
- ������Ƭ
- ������������
- �麯�����麯����
- �麯���͹��캯������������
- ��д���ǡ�overload��final

## ��������ת��

������ ����/����/ָ��  ������> ���� ����/����/ָ��

Only available to **public** inherit

Can be automatically done by compiler

Derive obj/ref/ptr can be used whenever a Base obj/ref/ptr is required.

Example

```cpp
class Base {
public:
    void print(){ cout << "Base" << endl;}
};

class Derive:public Base{
public:
    void print(){ cout << "Derive" << endl;}
};

void fun(Base obj){obj.print();}

int main(){
    Derive d;
    d.print();
    fun(d);     //upper convert of obj -> slice the obj
    return 0;
}
```

> Output:  
> Derive
> Base

## ������Ƭ

When a Derived ***obj*** is cast into a Base obj, the non-base part is sliced off
and the data will be ommited.

### Example �����������ݶ�ʧ

```cpp
class Pet{
    public: int i;
    Pet(int x = 0):i(x){}
};
class Dog:public Pet{
    public: int j;
    Dog(int x=0,int y=0): Pet(x), j(y){}
};

void getSize(Pet p){
    cout << "Pet size:" << sizeof(p) << endl;
}
int main(){
    Pet p;
    cout << "Pet size: "<< sizeof(p) << endl; // Pet size: 4
    Dog g;
   cout << "Dog size:" << sizeof(g) << endl; // Dog size: 8
    getSize(g);         // Pet size: 4  // ������Ƭ�����Σ�
    p = g;        
    cout << "Pet size:" << sizeof(p) << endl; // Pet size: 4 // ������Ƭ����ֵ��
    return 0;
}
```
### Example �������·�����ʧ

```cpp
class Pet{
public:
    void name(){}
};
class Dog:public Pet{
public: 
    void name(){}
};

void getSize(Pet p){
    p.name();
}
int main(){
    Dog g;
   g.name();  // Dog
    getName(g);  // Pet
    Pet p = g;
    p.name();  // Pet
    return 0;
}
```

### ָ��/���� ������ת��

���������ָ�루���ã���ת��Ϊ����ָ�루���ã�ʱ�����ᴴ���µĶ��󣬵�ֻ��������Ľӿڡ�

#### Example ���õ���������ת��

```cpp
class Pet { 
public:  int i;
 Pet(int x=0): i(x) {}
};
class Dog: public Pet { 
public:  int j;
 Dog(int x=0, int y=0): Pet(x), j(y) {}
};
int main() {
  Dog g(2,3);
  cout << g.i << " " << g.j << endl;    // 2 3
  Pet& p = g;               /// ��������ת��
  cout << p.i << endl;                  // 2
  p.i = 1;                  /// �޸Ļ�����ڵ�����
  cout << p.i << endl;                  // 1
  cout << g.i << " " << g.j << endl; /// Ӱ��������     // 1 3
  return 0;
}

```
```cpp
class Instrument{
public:
    void play(){ cout << "Instrument::play" << endl;}
};
class Wind:public Instrument{
public:
    void play{ cout << "Wind::play" << endl;}
};
void tune(Instrument& i){
    i.play();
}
int main(){
    Wind flute;
    tune(flute);                // Instrument::play
    Instrument &inst = flute;
    inst.play();                // Instrument::play
    return 0;
}
```

### ˽�м̳С��մ�ʵ�֡�

```cpp
class B {
private:
    int data{0};
public:
    int getData(){ return data;}
    void setData(int i){ data=i;}
};
class D1: private B {
public:
    using B::getData;
};
int main(){
    D1 d1;
    cout << d1.getData();
    // d1.setData(10);  ///�����˻����setData���������ɷ���
    // B& b = d1;       ///������˽�м̳е�����ת��
    // b.setData(10);   ///��������ƹ�D1�����û����setData����
}
```
## ������������

����(binding): �������뺯����������ϵ  
- ������(early binding): �ڳ�������֮ǰ���
- ������(late binding): ���ݶ����ʵ�����ͣ������ڳ�������ʱ���ֳ� ��̬����/����ʱ����
- - ֻ��**�麯��**�����ã�ʹ��**virtual**�ؼ�������

## �麯��

����**�����������¶���ĳ�Ա����**�������ڻ����б�����Ϊ**�麯��**����ͨ��**����ָ�������**���øó�Ա����ʱ����������������ָ�������ã������ʵ�����;����ǵ��û����еĺ��������ǵ�����������д�ĺ���

```cpp
class Base {
public:
    virtual ReturnType FuncName (argument);
};
```

����**��д����**ʱ�������Ƿ��������ó�Ա��������Ȼ���麯��

```cpp
class Instrument {
public:
  virtual void play() { cout << "Instrument::play" << endl; }
};

class Wind : public Instrument {
public:
  void play() { cout << "Wind::play" << endl; }
     /// ��д����(�Ժ���д���غ���д���ǵ�����
};

void tune(Instrument& ins) {
  ins.play(); /// ���� Instrument::play ���麯��������ʱ����ֱ�Ӱ󶨣�����ʱ���� ins ��ʵ�����͵��á�
}

int main() {
  Wind flute;
  tune(flute); /// ��������ת��
}

```
���ֻ��ָ���������Ч�����ԣ�

### �麯���ķ���ֵ

һ����˵�������麯���ķ���ֵӦ���������ͬ

������Covariant�ģ�����Base& <-> Derive&, Base\* <-> Derive\*��

- ����ָ�루�����Ƕ༶ָ�룩��������ֵ���û�����ֵ���ã�����Derive::f����ʱ��Derive::f�ķ������ͱ�����Derive�������Ѿ��������������
- ReturnTypeBase�б����û�ָ�������ReturnYpeDerive�б����û�ָ������������
- Base::f�ķ����������Derive::f�ķ�������ͬ�Ȼ����cv-qualified

### �麯����

������ʾ����ʵ��������Ϣ

ÿ�������麯����������У����������ܵط�һ��ָ�룬��Ϊ�麯��ָ��(vpointer/VPTR)��ָ��������VTABLE��

��ͨ������ָ�����麯������ʱ����������̬�ز�����ȡ�����VPTR����VTABLE���в��Һ�����ַ�Ĵ��룬�������ܵ�����ȷ�ĺ���������������ķ�����
- �����ڼ䣺�����麯����VTABLE����¼ÿ��������Ļ������������������麯����ڵ�ַ��
- �����ڼ䣺�����麯��ָ��VPTR���ڹ��캯���з�����ָ����Ӧ��VTABLE��

![avatar](pics/virtual_table_example.png)

�ڰ������麯������Ķ����У�����Ĵ�С������ָ���麯�����ָ��Ĵ�С��һ��voidָ��Ĵ�С��

### �麯���͹��캯������������

#### ���캯��

����VPTR�Ĺ����ɹ��캯����ɣ�������**���ܵ�**�ڹ��캯����ͷ�����ʼ������

���캯��**����Ҳ����**���麯��

Example
```cpp
class Base {
public:
  virtual void foo(){cout<<"Base::foo"<<endl;}
  Base(){foo();} ///�ڹ��캯���е����麯��foo  
  void bar(){foo();};///����ͨ�����е����麯��foo
};

class Derived : public Base {
public:
  int i;
  void foo(){cout<<"Derived::foo"<<i<<endl;}
    Derived(int j):Base(),i(j){}
};
int main() {
    Derived d(0);
    Base &b = d;
    b.bar();
    b.foo();
    return 0;
    }
```

>Output:  
Base::foo   //���캯�����õ���foo�ı��ذ汾  
Derived::foo()  //����ͨ�����е���
Derived::foo()  //ֱ�ӵ���

##### Explanation
�麯�������ڹ��캯���в�����  

ԭ�򣺻���Ĺ��캯������������ִ�У����û��๹�캯��ʱ�������е����ݳ�Ա��û�г�ʼ����������i��������������ʵ�ʶ�����麯��������ܻ��õ�δ��ʼ�����������Ա��

��ʼ��˳�򣺣�*�빹�캯����ʼ���б�˳���޹�!*)
- �����ʼ��
- �����Ա��ʼ��
- ���캯����

#### ��������

��������������ģ��ҳ�������ġ��������������趨�庯���塣

��������������;����ɾ���������ָ��ʱ��������������ָ����ָ�����ʵ�����ͣ�������Ӧ������������

���������������麯������ɾ������ָ����ָ���������ʱ�����������Զ����û�������������������ῼ��ʵ�ʶ����ǲ��ǻ���Ķ�������ܻᵼ���ڴ�й©��

�����������е���һ���麯���������õ�ֻ����������ı��ذ汾��������������������в�������**��Ϊ�˱������һ���Ѿ���ɾ���Ķ���ĺ�����������������˳�򣩣�**

Example

```cpp
class Base1 {
public:
  ~Base1() { cout << "~Base1()\n"; }
};

class Derived1 : public Base1 {
public:
  ~Derived1() { cout << "~Derived1()\n"; }
};

class Base2 {
public:
  virtual ~Base2() { cout << "~Base2()\n"; }
};

class Derived2 : public Base2 {
public:
  ~Derived2() { cout << "~Derived2()\n"; }
};
int main() {
  Base1* bp = new Derived1;
  delete bp; /// ֻ�����˻��������������
  Base2* b2p = new Derived2;
  delete b2p; /// �������������������������û��������������
}
```

>Output:  
>~Base()         //ֻ�����˻������������  
>
>~Dervied2()     //�����������������������  
>~Base2()        //�ٵ��û�����鹹����         

**��Ҫԭ��**:**���ǽ������������������Ϊ����������**

## ���ء���д��������д����

### ���� overload

������������ͬ�� �����������벻ͬ�� ������**��ͬ**

### ��д���� override

���������¶�������е�**�麯��**��������**������ͬ**����������**������ͬ**������ֵһ����ͬ

��������麯������ԭ������麯��ָ��ᱻ�����������¶�����麯��ָ�븲�ǵ�

### ��д���� redefining

���������¶�������еĺ�������������ͬ������ **������ͬ** *��* **����ĺ��������麯��**��

�麯����**���ᷢ������**

---

||����overload|��д����redefining|��д����override|
|----|----|----|----|
|������|��ͬ��ͬһ�����У�|��ͬ��������ͻ��ࣩ|��ͬ��������ͻ��ࣩ|
|������|��ͬ|��ͬ|��ͬ|
|��������|��ͬ|��ͬ/��ͬ|��ͬ|
|����Ҫ��||�������������ͬ������ຯ������Ϊ�麯��|���ຯ��Ϊ�麯��|

---

### Example
```cpp
class Base{
public:    
  	virtual void foo(){cout<<"Base::foo()"<<endl;}
  	virtual void foo(int ){cout<<"Base::foo(int )"<<endl;} ///���� 
  	void bar(){};
};
class Derived1 : public Base {
public:
    void foo(int ) {cout<<"Derived1::foo(int )"<<endl;} 
    /// ����д����
};
class Derived2 : public Base {
public:
    void foo(float ) {cout<<"Derived2::foo(float )"<<endl;}
    /// ��Ѳ���д���ˣ�������д���ǣ�����д����
};
int main() {    
    Derived1 d1;
    Derived2 d2;
    Base* p1 = &d1;
  	Base* p2 = &d2;
  	//d1.foo(); 	///���������඼�����˴�������foo������foo()��ʵ�����ɼ�
  	//d2.foo();
  	p1->foo();  	///�����麯�������м̳��Ի����foo()�麯��
  	p2->foo();
  	d1.foo(3); 		///��д����
  	d2.foo(3.0);   	///���õ���������foo(float )
	p1->foo(3);  	///��д���ǣ��麯��������������� foo(int )    
	p2->foo(3.0);   ///��д���أ��麯�������Ǽ̳��Ի��� foo(int )
}

```

>Output:  
Base::foo()  
Base::foo()  
Derived1::foo(int )  
Derived2::foo(float )  
Derived1::foo(int )  
Base::foo(int )

## override �� final �ؼ���

### override

���� **override** �ؼ�����ȷ���߱���������һ�������ǶԻ�����һ��**�麯��**����д���ǡ������������Դ˽��м�飬ֻ����������ʱ����ͨ������

### final

���麯�������������У�
���� **final** �ؼ���ȷ������Ϊ���Ҳ��ɱ���������д

���ඨ���У�
**final** ָ�����಻�ɱ��̳�

--- 
�����κ���ʱ��override��final��ֻ������**�麯��**

## OOP����˼��

- ���ݳ������**�ӿ�**��**ʵ��**����
- �̳У�����������͵�**��ι�ϵ**
- ��̬�󶨣�**ͳһʹ�û���ָ��**��ʵ�ֶ�̬��Ϊ
# 多态与模板

## Abstract

- 纯虚函数与抽象类
- 向下类型转换
- 多重继承的虚函数表，多重继承的利弊
- 多态
- 函数模板与类模板

## 纯虚函数

虚函数 可进一步声明为 纯虚函数， 包含纯虚函数的类叫做“抽象类”

`virtual ReturnType FuncName(Parameters) = 0;`

可在类外定义函数体提供默认实现，派生类通过Base::f() 调用

抽象类不允许定义对象，定义基类为抽象类的主要目的是为派生类规定共性“接口”

## 抽象类

Definition: Have at least one pure virtual function.

Features:
- Defining objects is not allowed.
- Can only provide IO for derived class.
- Can avoid object slicing: Ensuring only pointers and references can be converted into upper type.

Example:  
- Shape
- - Shape2D
- - - Circle
- - - Triangle
- - - Rectangle
- - Shape3D
- - - Sphere
- - - Cube
- - - Tetrahedron

Code Example:
```cpp
class Pet { 
public:  
  virtual void motion()=0;
};
void Pet::motion(){ cout << "Pet motion: " << endl; } 
class Dog: public Pet { 
public: 
  void motion() override {Pet::motion(); cout << "dog run" << endl; } 
};
class Bird: public Pet {
public: 
  void motion() override {Pet::motion(); cout << "bird fly" << endl; } 
};
int main() {
  Pet* p = new Dog; /// 向上类型转换
  p->motion();
  p = new Bird; /// 向上类型转换
  p->motion();
  //p = new Pet; /// 不允许定义抽象类对象
  return 0;
}
```
>Output:  
Pet motion:  
dog run  
Pet motion:  
bird fly  

- 基类纯虚函数被派生类重写覆盖之前仍是纯虚函数。因此当继承一个抽象类时，必须**实现** **所有** 纯虚函数，否则继承出来的类仍然是抽象类
- 纯虚析构函数除外

### 纯虚析构函数

>回顾：  
析构函数可以且常常是虚的，仍需定义函数体，用途是：当删除基类对象指针时，编译器将根据指针所指对象的**实际类型**，调用相应的析构函数

析构函数也可以是纯虚构函数

- 仍然需要函数体
- 目的：使基类成为抽象类，不能创建基类的对象。如果有其他函数是纯虚函数，则析构函数不必是纯虚的。

*// Comment: 我想纯虚函数/抽象类的目的在于**强迫对派生类进行各自的实现**，而不依赖基类（抽象）的实现*

**对于纯虚析构函数而言**，即便派生类中不显式实现，**编译器也会自动合成默认析构函数**。因此即便派生类不覆盖纯虚析构函数，它也可以不是抽象类，可以定义派生类对象。


## 向下类型转换

基类指针/引用  --->  派生类指针/引用

### Why 向下类型转换？

- 向上转换：**保留共性**；向下转换：**表现特性**

- 比如可以使用基类指针数组对各种派生类对象进行管理，当具体处理时可以将其转换为实际的派生类指针，进而调用派生类专有的接口

### 如何保证转换的正确性？

借助虚函数表进行**动态类型检查**

### dynamic_cast 安全类型的向下显式类型转换

使用dynamic_cast的对象**必须有虚函数**

#### Usage
```cpp
// T1* obj_p;
// T1& obj_r;
T2* pObj = dynamic_cast<T2*>(obj_p);
// 失败时返回nullptr
T2& refObj = dynamic_cast<T2&>(obj_r);
// 失败时抛出bad_cast异常
```

T1必须是多态类型（声明或继承了至少一个虚函数的类），T2不必。

若两者没有继承关系，也能通过编译，但运行时会转换失败。

### static_cast 用于避免 确认类型 带来的开销

编译时静态浏览类层次，只检查继承关系。没有继承关系的类之间必须有转换途径（略）。运行时无法确认是否正确转换

```cpp
T2* pObj = static_cast<T2*>(obj_p);
T2& refObj = static_cast<T2&>(obj_P);
// 不安全！
```
### dynamic与static比较
相同：都可以完成向下类型转换  
不同：
- static_cast是在**编译时静态**执行向下类型转换
- dynamic_cast会在**运行时**检查被转换的对象**是否确实是正确的派生类**。额外的检查需要RTTI（Run-Time Type Information），因此要比static_cast慢一些，但是更安全。

**一般使用dynamic_cast进行向下类型转换**

---

### 重要原则（清楚指针所指向的真正对象）：
1. 指针或引用的向上转换总是安全的
2. 向下转换时用dynamic_cast，安全检查
3. 避免**对象之间**的转换

### 向上向下类型转换与虚函数表

对于基类中有虚函数的情况：

- 向上类型转换  
  转换为基类**指针或引用**，则对应虚函数表仍然为派生类的虚函数表（晚绑定）  
  转换为基类**对象**，则对应虚函数表是基类的虚函数表（早绑定）  
- 向下类型转换  
  dynamic_cast通过虚函数表来判断是否能进行向下类型转换

---
Example
```cpp
class Pet { public:  virtual ~Pet() {} };
class Dog : public Pet { 
public: 	void run() { cout << "dog run" << endl; }
};
class Bird : public Pet {
public: 	void fly() { cout << "bird fly" << endl; }
};

void action(Pet* p) {
	auto d = dynamic_cast<Dog*>(p);	/// 向下类型转换
	auto b = dynamic_cast<Bird*>(p);	/// 向下类型转换
	if (d) /// 运行时根据实际类型表现特性
		d->run();
	else if(b)
		b->fly();
}

int main() {
	Pet* p[2];
	p[0] = new Dog; /// 向上类型转换
	p[1] = new Bird; /// 向上类型转换
	for (int i = 0; i < 2; ++i) {
		action(p[i]);
	}
	return 0;
}
```

## 多重继承

### 多重继承的虚函数表

多重继承会有多个虚函数表，几重继承，就会有几个虚函数表。这些表按照派生的顺序依次排列。

如果子类改写了父类的虚函数，那么就会用子类自己的虚函数覆盖虚函数表的相应位置，**如果子类有新的虚函数，那么就添加到第一个虚函数表的末尾。**

![avatar](pics/multi-inherit_vtable.png)


### 利弊

略，见前课件

Best Practice:
- 最多继承一个非抽象类（is-a)
- 可以继承多个抽象类（接口）

Why?
- 避免 多重继承的二义性
- 利用 一个对象实现多个接口

---
Example
```cpp
class WhatCanSpeak {
public:
	virtual ~WhatCanSpeak() {}
	virtual void speak() = 0;  };
class WhatCanMotion {
public:
	virtual ~WhatCanMotion() {}
	virtual void motion() = 0;   };
class Human : public WhatCanSpeak, public WhatCanMotion
{
	void speak() { cout << "say" << endl; }
	void motion() { cout << "walk" << endl; }
};

void doSpeak(WhatCanSpeak* obj) { obj->speak(); }
void doMotion(WhatCanMotion* obj) { obj->motion(); }
int main()
{
	Human human;
	doSpeak(&human); doMotion(&human);
	return 0;
}
```

### 虚拟继承
自行了解

## 多态(Polymorphism)

产生多态效果的条件： 继承 && 虚函数 && （引用 || 指针）

好处：
- 通过基类定好接口后，不必对每一个派生类特殊处理，只需要调用抽象基类的接口即可。大大提高程序的**可复用性**
- 不同派生类对同一接口的实现不同，能达到不同的效果，提高了程序**可拓展性和可维护性**

示例见课件

### 应用：TEMPLATE METHOD设计模式

- 在接口的一个方法中定义算法的骨架
- 将一些步骤的实现延迟到子类中
- 使得子类可以在不改变算法结构的情况下，重新定义算法中的某些步骤

```cpp
class Base{
public:
    void action() {
        step1();
        step2();
        step3();
    }
    virtual void step1() { 
        cout << "Base::step1" << endl; 
    }
    virtual void step2() { 
        cout << "Base::step2" << endl; 
    }
    virtual void step3() { 
        cout << "Base::step3" << endl; 
    }
};

class Derived1 : public Base{
    void step1() { 
        cout << "Derived1::step1" << endl; 
    }
};
class Derived2 : public Base{
    void step2() { cout << "Derived2::step2" << endl; }
};

int main(){
    Base* ba[] = {new Base, new Derived1, new Derived2};
    for (int i = 0; i < 3; ++i) {
        ba[i]->action();
        cout<<"==="<<endl;
    }
    return 0;
}
```

> Output:  
Base::step1  
Base::step2  
Base::step3  
===  
Derived1::step1  
Base::step2  
Base::step3  
===  
Base::step1  
Derived2::step2  
Base::step3  
===  

## 函数模板与类模板

模板
- 函数模板
- 类模板
- 成员函数模板

### 函数模板

`template <typename T> ReturnType Func(Args);`

`template <class T> ReturnType Func(Args);`

在调用时编译器自动推导出实际参数的类型

```cpp
template <typename T>
T sum(T a,T b){return a+b;}

cout << sum(9,2.1);   //编译错误，参数类型不一致，无法推导
cout<< sum<int>(9,2.1); //手工指定类型
```

### 类模板

```cpp
template <typename T> class A{
  T data;
public:
  void print1(){cout << data << endl;}
  void print2();      // 类外定义
};

template<typename T>    // 类外定义
void A<T>::print2() {cout << data << endl;}

int main(){
  A<int> a;
  a.print1();
}

```

“模板参数”
- 类型参数： typename或class
- 非类型参数： 整数，枚举，指针（指向对象或函数），引用（引用对象或函数）。
  ```cpp
  template<typename T, unsigned size>
  class array{
    T elems[size];
    ...
  };
  
  array<char, 10> array0;
  ```
### 成员函数模板

普通类
```cpp
class normal_class {
public:
  int value;
  template<typename T> void set(T const& v) {
    value = int(v);
  }   /// 在类内定义
  template<typename T> T get();
};

template<typename T>    /// 在类外定义
T normal_class::get() {
  return T(value);
}
```
模板类
```cpp
template<typename T0> class A{
  T0 value;
public:
  template<typename T1> void set(T1 const& v){
    value = T0(v);
  }     /// 类内定义
  template<typename T1> T1 get();
};
template<typename T0> template<typename T1>
T1 A<T0>::get(){ return T1(value);}   // 类外定义

/*注意不能写成
template<typename T0, typename T1>
T1 A<T0>::get(){ return T1(value);}   // 类外定义
*/
```

模板使用中通常可以自动推导类型，必要时也可以指定，方法是在调用的东西的名称后加上 <类型名>

### 模板原理

在编译期进行对模板的处理，这意味着所有模板参数必须在编译期确定，不能使用变量

这意味着

模板库必须在头文件中实现，不可以分开编译

### 模板与多态

模板也是多态，只不过是**静**多态（编译时）

# OOP�μ�Ԥϰ�ʼ�

��������L1-L6�ıʼǵģ�Ūvscode���gitʱ�ֻ��Ѷ���ȫɾ�ˣ�����  
����ֻ�ܴ�L7��ʼ��  
