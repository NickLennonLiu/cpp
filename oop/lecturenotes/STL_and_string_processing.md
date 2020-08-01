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

> #include \<iomanip\>  
> input \ output manipulation

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
