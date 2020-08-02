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

To be continue...



