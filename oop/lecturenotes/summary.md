
# æ¨¡æ¿ä¸STLåˆæ­¥

## Abstract

- ç±»æ¨¡æ¿ä¸å‡½æ•°æ¨¡æ¿ç‰¹åŒ–
- å‘½åç©ºé—´
- STLåˆæ­¥â€”â€”å®¹å™¨ä¸è¿­ä»£å™¨

## å‡½æ•°æ¨¡æ¿ç‰¹åŒ–

æœ‰æ—¶ï¼Œæœ‰äº›ç±»å‹å¹¶ä¸åˆé€‚ï¼Œåˆ™éœ€è¦å¯¹æ¨¡æ¿åœ¨æŸç§æƒ…å†µä¸‹çš„å…·ä½“ç±»å‹è¿›è¡Œç‰¹æ®Šå¤„ç†ï¼Œç§°ä¸ºâ€œæ¨¡æ¿ç‰¹åŒ–â€

ç‰¹åŒ–æ–¹å¼ï¼š
```cpp
// åŸºç¡€æ¨¡æ¿
template <typename T> T sum(T a, T b)
```
- åœ¨å‡½æ•°ååç”¨<>æ‹¬å·æ‹¬èµ·å…·ä½“ç±»å‹
  ```cpp
  template<> char* sum<char*>(char*a, char*b)
  ```
- ç”±ç¼–è¯‘å™¨æ¨å¯¼å‡ºå…·ä½“ç±»å‹ï¼Œå‡½æ•°åä¸ºæ™®é€šå½¢å¼
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
int div2(const int& val) //å‡½æ•°æ¨¡æ¿ç‰¹åŒ–
{
    cout << "better solution!" << endl;
    return val >> 1; //å³ç§»å–ä»£é™¤ä»¥2
}
```

**æ³¨æ„**ï¼šå¯¹äº**å‡½æ•°æ¨¡æ¿**ï¼Œå¦‚æœæœ‰å¤šä¸ªæ¨¡æ¿å‚æ•°ï¼Œåˆ™ç‰¹åŒ–æ—¶å¿…é¡»æä¾›æ‰€æœ‰å‚æ•°çš„ç‰¹ä¾‹ç±»å‹ï¼Œä¸èƒ½éƒ¨åˆ†ç‰¹åŒ–

ä½†å¯ä»¥ç”¨é‡è½½æ¥ä»£æ›¿éƒ¨åˆ†ç‰¹åŒ–

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
{   //ä¸æ˜¯éƒ¨åˆ†ç‰¹åŒ–ï¼Œè€Œæ˜¯é‡è½½å‡½æ•°
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

### å‡½æ•°æ¨¡æ¿é‡è½½è§£æé¡ºåºï¼š  
ç±»å‹åŒ¹é…çš„æ™®é€šå‡½æ•°->åŸºç¡€å‡½æ•°æ¨¡æ¿->å…¨ç‰¹åŒ–å‡½æ•°æ¨¡æ¿
- å¦‚æœæœ‰æ™®é€šå‡½æ•°ä¸”ç±»å‹åŒ¹é…ï¼Œåˆ™ç›´æ¥é€‰ä¸­ï¼Œé‡è½½è§£æç»“æŸ
- å¦‚æœæ²¡æœ‰ç±»å‹åŒ¹é…çš„æ™®é€šå‡½æ•°ï¼Œåˆ™é€‰æ‹©**æœ€åˆé€‚**çš„åŸºç¡€æ¨¡æ¿
- å¦‚æœé€‰ä¸­çš„åŸºç¡€æ¨¡æ¿æœ‰**å…¨ç‰¹åŒ–ç‰ˆæœ¬**ä¸”**ç±»å‹åŒ¹é…**ï¼Œåˆ™é€‰æ‹©å…¨ç‰¹åŒ–ç‰ˆæœ¬ï¼Œå¦åˆ™ä½¿ç”¨åŸºç¡€æ¨¡æ¿

```cpp
template<class T> void f(T) { 
  //func1ä¸ºåŸºç¡€æ¨¡æ¿
  cout<< â€œfull templateâ€ <<endl;}; 
template<class T> void f(T*) {
  //func2ä¸ºfunc1çš„é‡è½½ï¼Œä»æ˜¯åŸºç¡€æ¨¡æ¿
  cout<< â€œfull template -> overload templateâ€ <<endl;};
template<> void f(char*) {
  //func3ä¸ºfunc2çš„ç‰¹åŒ–ç‰ˆæœ¬(Tç‰¹åŒ–ä¸ºchar)
  cout<< â€œoverload template -> specializedâ€ <<endl;}; 
int main() { 
    char *p; 
    f(p);       //æœ€ç»ˆè°ƒç”¨äº†func3
    return 0;
}
// ä¼˜å…ˆåŒ¹é…ç‰¹åŒ–ç‰ˆæœ¬ï¼Œå‰ææ˜¯è¢«ç‰¹åŒ–çš„å¯¹åº”**åŸºç¡€å‡½æ•°æ¨¡æ¿**è¢«åŒ¹é…åˆ°
```
è¿›ä¸€æ­¥çš„ä¾‹å­è§è¯¾ä»¶

## ç±»æ¨¡æ¿ç‰¹åŒ–

```cpp
// é€šç”¨æ¨¡æ¿
template<typename T1, typename T2> class A {};

// å…¨éƒ¨ç‰¹åŒ–
template<> class A<int,int> {};

// éƒ¨åˆ†ç‰¹åŒ–
template<typename T1> class A<T1,int> {};
```

## Summary on Template Specifying

**ç±»æ¨¡æ¿**å¯ä»¥**éƒ¨åˆ†ç‰¹åŒ–**æˆ–è€…**å…¨éƒ¨ç‰¹åŒ–**ï¼Œç¼–è¯‘å™¨ä¼šæ ¹æ®è°ƒç”¨æ—¶çš„ç±»å‹å‚æ•°è‡ªåŠ¨é€‰æ‹©åˆé€‚çš„æ¨¡æ¿ç±»

**å‡½æ•°æ¨¡æ¿**åªèƒ½**å…¨éƒ¨ç‰¹åŒ–**ï¼Œä½†å¯ä»¥é€šè¿‡**é‡è½½**ä»£æ›¿éƒ¨åˆ†ç‰¹åŒ–çš„å®ç°ã€‚ç¼–è¯‘å™¨åœ¨ç¼–è¯‘é˜¶æ®µå†³å®šä½¿ç”¨ç‰¹åŒ–å‡½æ•°æˆ–è€…æ ‡å‡†æ¨¡æ¿å‡½æ•°

å‡½æ•°æ¨¡æ¿çš„å…¨ç‰¹åŒ–ç‰ˆæœ¬çš„åŒ¹é…ä¼˜å…ˆçº§**å¯èƒ½ä½äº**é‡è½½çš„éç‰¹åŒ–åŸºç¡€å‡½æ•°æ¨¡æ¿ï¼Œå› æ­¤æœ€å¥½ä¸è¦ä½¿ç”¨å…¨ç‰¹åŒ–å‡½æ•°æ¨¡æ¿è€Œç›´æ¥ä½¿ç”¨é‡è½½å‡½æ•°

## å‘½åç©ºé—´

```cpp
// å®šä¹‰å‘½åç©ºé—´ï¼š
namespace A {
  int x,y;
}
// ä½¿ç”¨å‘½åç©ºé—´ï¼š
A::x = 3;
A::y = 6;

// ä½¿ç”¨usingå£°æ˜ç®€åŒ–å‘½åç©ºé—´ä½¿ç”¨

// ä½¿ç”¨æ•´ä¸ªå‘½åç©ºé—´
using namespace A;
x=3; y=6;

// ä½¿ç”¨éƒ¨åˆ†æˆå‘˜ï¼šæ‰€é€‰æˆå‘˜å¯ç›´æ¥ä½¿ç”¨
using A::x;
x = 3; A::y = 6;
```

## STLåˆæ­¥

> Standard Template Library

åŒ…å«4ä¸ªç»„ä»¶ï¼š
- ç®—æ³•
- å®¹å™¨
- å‡½æ•°
- è¿­ä»£å™¨

åŸºäºæ¨¡æ¿ç¼–å†™

å…³é”®ç†å¿µï¼šå°†â€œåœ¨æ•°æ®ä¸Šæ‰§è¡Œçš„æ“ä½œâ€ ä¸ â€œè¦æ‰§è¡Œæ“ä½œçš„æ•°æ®â€ åˆ†ç¦»

å‘½åç©ºé—´ï¼šstd ï¼ˆä¸æ¨èåœ¨å¤§å‹å·¥ç¨‹ä¸­ä½¿ç”¨using namespace std;å®¹æ˜“æ±¡æŸ“å‘½åç©ºé—´ï¼‰

### STLå®¹å™¨

- Simple container
- Sequence container
- Associative container

#### pair
```cpp
std::pair<int,int> t;
t.first = 1, t.second = 2;
auto t = std::make_pair("abc", 7.8); // Automatically induce the type

// æ”¯æŒ<,>,==ç­‰ï¼Œå…ˆæ¯”è¾ƒfirstå†æ¯”è¾ƒsecond
```

#### tuple

```cpp
v0 = std::get<0>(tuple1);
v1 = std::get<1>(tuple2);

auto t = std::make_tuple("abc",7.8,123,'3');

std::string x; double y; int z;
std::tie(x, y, z) = std::make_tuple("abc", 7.8, 123);
// tieè¿”å›å·¦å€¼å¼•ç”¨çš„å…ƒç»„
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

std::find(l.begin(),l.end(),2); // è¿”å›è¿­ä»£å™¨

l.insert(iter,4);

```

#### set

```cpp
std::set<int> s;

s.insert(1);

iter = s.find(1); // findè¿”å›è¿­ä»£å™¨ï¼å®¹å™¨å†…éƒ¨æ’åˆ—é¡ºåºæŒ‰ç…§å¤§å°é¡ºåº

s.erase(s.find(1));

s.count(1); // Returns 0 or 1;
```

#### map
> å€¼ç±»å‹ä¸º pair<Key,T>


```cpp

std::map<std::string, int> s;
s["oop"] = 1;
s.insert(std::make_pair(std::string("oop"),1));

iter = s.find(key);
cnt = s.count(key);
s.erase(iter);
```

### è¿­ä»£å™¨

```cpp

vector<int>::iterator iter;

vector<int> x;
iter = x.begin();
iter = x.end();

++iter;
iter += n;
*iter = 5;  // è§£å¼•ç”¨è¿ç®—ç¬¦è¿”å›å·¦å€¼å¼•ç”¨

int dist = iter1 - iter2;

for(vector<int>::iterator it = vec.begin();
    it != vec.end(); ++it) continue;

for(auto it = vec.begin(); it != vec.end(); ++it) continue;

for(auto x: vec) continue;
//ç­‰ä»·äºä¸Šä¸Šé¢é‚£ä¸€è¡Œ
```


# STLä¸å­—ç¬¦ä¸²å¤„ç†

## Abstract
- stringå­—ç¬¦ä¸²ç±»
- iostreamè¾“å…¥è¾“å‡ºæµ
- å­—ç¬¦ä¸²å¤„ç†ä¸æ­£åˆ™è¡¨è¾¾å¼

## string å­—ç¬¦ä¸²ç±»

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

## iostream è¾“å…¥è¾“å‡ºæµ

> What the hell is ostream?

![avatar](pics/stl_iostream.png)

### ä» ostream å’Œ cout å¼€å§‹

#### ostream
ostreamæ˜¯stlåº“ä¸­æ‰€æœ‰**è¾“å‡ºæµ**çš„**åŸºç±»**  
å®ƒé‡è½½äº†é’ˆå¯¹åŸºç¡€ç±»å‹çš„è¾“å‡ºæµè¿ç®—ç¬¦ <<

#### cout
cout æ˜¯STLä¸­å†…å»ºçš„ä¸€ä¸ªostreamå¯¹è±¡

å®ƒä¼šå°†æ•°æ®é€åˆ°**æ ‡å‡†è¾“å‡ºæµ**(usually the screen)

### Make your own ostream

> å“ªä¸ªç”·å­©ä¸æƒ³æ‹¥æœ‰è‡ªå·±çš„ostreamå‘¢ï¼Ÿ

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

å®ç°åŸç†ï¼š<<è¿ç®—ç¬¦ä¸º**å·¦ç»“åˆ**

### æ ¼å¼åŒ–è¾“å‡º

\#include \<iomanip\>  // input \ output manipulation

cout << **fixed** << 2018.0 << " " << 0.0001 << endl;  
				//æµ®ç‚¹æ•° -> 2018.000000 0.000100  
cout << **scientific** << 2018.0 << " " << 0.0001 << endl;  
				//ç§‘å­¦è®¡æ•°æ³• -> 2.018000e+03 1.000000e-04  
cout << **defaultfloat**;  //è¿˜åŸé»˜è®¤è¾“å‡ºæ ¼å¼  
cout << **setprecision(2)** << 3.1415926 << endl;  
				//è¾“å‡ºç²¾åº¦è®¾ç½®ä¸º2 -> 3.2  
cout << **oct** << 12 << " " << **hex** << 12 << endl;   
				//å…«è¿›åˆ¶è¾“å‡º -> 14  åå…­è¿›åˆ¶è¾“å‡º -> c  
cout << **dec**;	//è¿˜åŸåè¿›åˆ¶  
cout << **setw(3)** << **setfill('*')** << 5 << endl;  
				//è®¾ç½®å¯¹é½é•¿åº¦ä¸º3ï¼Œå¯¹é½å­—ç¬¦ä¸º* -> **5  

**fixed scientific setprecision** ç­‰éƒ½æ˜¯ **æµæ“çºµç®—å­**ï¼Œå¤§è‡´åˆ†ä¸ºä¸¤ç§ï¼šä¸å¸¦å‚æ•°ï¼ˆè§„èŒƒæœ‰å®šä¹‰ï¼‰ã€å¸¦å‚æ•°ï¼ˆè§„èŒƒæ— å®šä¹‰ï¼‰

### æµæ“çºµç®—å­ stream manipulator

å€ŸåŠ©è¾…åŠ©ç±»è®¾ç½®æˆå‘˜å˜é‡

setprecision(2)æ˜¯ä¸€ä¸ªç±»çš„å¯¹è±¡

ä¸€ç§å®ç°æ–¹å¼çš„ç¤ºä¾‹ï¼š
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

> C++æ ‡å‡†ä¸­endlçš„å£°æ˜ï¼šostream& endl(ostream& os);

endl æ˜¯ä¸€ä¸ªå‡½æ•°ï¼Œå¯ä»¥è°ƒç”¨endl(cout);
```cpp
ostream& endl(ostream& os) {
    os.put('\n');
    os.flush();
    return os;
}
```
å®ƒåŒæ—¶åˆæ˜¯ä¸€ä¸ªæµæ“çºµç®—å­ cout << endl;
```cpp
//å®ç°æ–¹å¼ç¤ºä¾‹
ostream& operator<< (ostream& (*fn)(ostream&)) {    // æµè¿ç®—ç¬¦é‡è½½ï¼Œå‡½æ•°æŒ‡é’ˆä½œä¸ºå‚æ•°
    return (*fn)(*this);
}
```

#### cout

> ä¸èƒ½å¤åˆ¶

é‡è½½æµè¿ç®—ç¬¦éœ€è¦è¿”å›**å¼•ç”¨**ï¼Œé¿å…å¤åˆ¶

```cpp
ostream(const ostream&) = delete;
ostream(ostream&& x);
```
**ç¦æ­¢å¤åˆ¶ï¼Œåªå…è®¸ç§»åŠ¨**

ä»…ä½¿ç”¨coutä¸€ä¸ªå…¨å±€å¯¹è±¡
- é¿å…å¤åˆ¶å¼€é”€
- ä¸€ä¸ªå¯¹è±¡å¯¹åº”ä¸€ä¸ªæ ‡å‡†è¾“å‡ºï¼Œç¬¦åˆoopæ€æƒ³
- å¤šä¸ªå¯¹è±¡ä¹‹é—´**æ— æ³•åŒæ­¥è¾“å‡ºçŠ¶æ€**

## æ–‡ä»¶è¾“å…¥è¾“å‡ºæµ

> ä»¥æ–‡ä»¶è¾“å…¥æµä¸ºä¾‹å­

ifstreamæ˜¯istreamçš„å­ç±»ï¼ŒåŠŸèƒ½æ˜¯ä»æ–‡ä»¶ä¸­è¯»å…¥æ•°æ®

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
    while(ifs) {			//åˆ¤æ–­æ–‡ä»¶æ˜¯å¦åˆ°æœ«å°¾ åˆ©ç”¨äº†é‡è½½çš„boolè¿ç®—ç¬¦
        ifs >> ws;  		//é™¤å»å‰å¯¼ç©ºæ ¼ wsä¹Ÿæ˜¯æµæ“çºµç®—å­
        int c = ifs.peek();		//æ£€æŸ¥ä¸‹ä¸€ä¸ªå­—ç¬¦ï¼Œä½†ä¸è¯»å–
        if (c == EOF) break;
        if (isdigit(c))			//<cctype>åº“å‡½æ•°
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

å…¶ä»–æ“ä½œ
```cpp
getline(ifs, str);

char c = ifs.get();
ifs.ignore(int n=1, int delim=EOF); // omit n chars, or until delim separator
char c = ifs.peek();
ifs.putback(c);
ifs.unget();
```

## å­—ç¬¦ä¸²è¾“å…¥è¾“å‡ºæµ

> ä»¥è¾“å…¥è¾“å‡ºæµä¸ºä¾‹å­

**stringstream**æ˜¯**iostream**çš„å­ç±»  
**iostream**ç»§æ‰¿äº**istream**å’Œ**ostream**  
// å¤šé‡ç»§æ‰¿ï¼  
**stringstream**å®ç°äº†è¾“å…¥è¾“å‡ºæµåŒæ–¹çš„æ¥å£

### stringstream

- åœ¨å¯¹è±¡å†…éƒ¨ç»´æŠ¤äº†ä¸€ä¸ªbuffer
- ä½¿ç”¨æµè¾“å‡ºå‡½æ•°å¯ä»¥å°†æ•°æ®å†™å…¥buffer
- ä½¿ç”¨æµè¾“å…¥å‡½æ•°å¯ä»¥ä»bufferä¸­è¯»å…¥æ•°æ®
- **ä¸€èˆ¬ç”¨äºç¨‹åºå†…éƒ¨çš„å­—ç¬¦ä¸²æ“ä½œ**

```cpp
stringstream ss;
stringstream ss(str);
```

#### What can it do?

- è¿æ¥å­—ç¬¦ä¸²
- å°†å­—ç¬¦ä¸²è½¬æ¢ä¸ºå…¶ä»–ç±»å‹çš„æ•°æ®
- é…åˆæµæ“ä½œç®—å­è¾¾åˆ°æ ¼å¼åŒ–è¾“å‡ºæ•ˆæœ

#### è·å–stringstreamçš„buffer

![avatar](pics/stringstream_buffer.png)

#### å®ç°ä¸€ä¸ªç±»å‹è½¬æ¢å‡½æ•°

```cpp
template<class outtype, class intype>
outtype convert(intype val)
{
	static stringstream ss;
						//ä½¿ç”¨é™æ€å˜é‡é¿å…é‡å¤åˆå§‹åŒ–
	ss.str(""); 	//æ¸…ç©ºç¼“å†²åŒº
	ss.clear(); 	//æ¸…ç©ºçŠ¶æ€ä½ï¼ˆä¸æ˜¯æ¸…ç©ºå†…å®¹ï¼‰
	ss << val;
	outtype res;
	ss >> res;
	return res;
}
```

# æ­£åˆ™è¡¨è¾¾å¼

## ä¸‰ç§æ¨¡å¼

- åŒ¹é…
- æœç´¢
- æ›¿æ¢

## åŒ¹é…

- **å­—ç¬¦ä»£è¡¨å…¶æœ¬èº«**  
  > The car parked in **the** garage.
- **è½¬ä¹‰å­—ç¬¦**  
  > \nã€\t etc
- **ç‰¹æ®ŠåŒ¹é…å­—ç¬¦** 
  > ^å­—ç¬¦ä¸²å¼€å¤´  
  $å­—ç¬¦ä¸²ç»“å°¾  

### å­—ç¬¦ç°‡ [ ]

- **åŒ¹é…çš„*****å•ä¸ª*****å­—ç¬¦åœ¨æŸä¸ªèŒƒå›´ä¸­**
- - [aeiou]
- - [a-z]
- - [0-9]
- **èŒƒå›´å–å**
- - [^a-z] åŒ¹é…æ‰€æœ‰éå°å†™å­—æ¯çš„å•ä¸ªå­—ç¬¦
- - [^c]ar: The car **par**ked in the **gar**age.
- **è¿ç”¨**
- - [a-z][0-9] : **a1**ã€**b9** ...
- - ^[^0-9][0-9]$ : **?2**ã€**g5**ã€**-1** ...
- - [Tt]he : **The** car parked in **the** garage.
- **ç‰¹æ®Šå­—ç¬¦**
- - |å­—ç¬¦|åŒ¹é…|
    |----|----|
    |.|é™¤æ¢è¡Œä»¥å¤–ä»»æ„å­—ç¬¦|
    |[.]æˆ–\\.|åŒ¹é…å¥å·|
    |\d|ç­‰ä»·[0-9]|
    |\D|[^0-9]|
    |\s|æ‰€æœ‰ç©ºç™½å­—ç¬¦å¦‚\t\n|
    |\S|æ‰€æœ‰éç©ºç™½å­—ç¬¦|
    |\w|å­—æ¯ã€æ•°å­—ã€ä¸‹åˆ’çº¿ï¼ˆ[a-zA-Z0-9_]ï¼‰|
    |\W|[^a-zA-Z0-9_]|

### é‡å¤æ¨¡å¼

- **x{n,m} é‡å¤n~mæ¬¡**
- - a{4} : aaaa
- - a{2,4} : aa aaa aaaa
- - a{2,} : é•¿åº¦å¤§äºç­‰äº2çš„a
- **æ‹“å±•åˆ°å­—ç¬¦ç°‡**
- **ç‰¹æ®Šå­—ç¬¦**
- - |ç‰¹æ®Šå­—ç¬¦|ç­‰ä»·|
    |----|----|
    |?|{0,1}|
    |+|{1,}|
    |*|{0,}|

### æˆ–è¿æ¥ç¬¦

#### åŒ¹é…æ¨¡å¼å¯ä»¥ä½¿ç”¨ **|** è¿›è¡Œè¿æ¥

Examples:
- (Chapter|Section) [1-9][0-9]?
- - > **Chapter 1**    **Section 10**
- 0\d{2}-\d{8}|0\d{3}-\d{7}
- - > **010-12345678**   **0376-2233445**
- (c|g|p)ar

#### ä½¿ç”¨()æ”¹å˜ä¼˜å…ˆçº§

- m|food    -----    mæˆ–food
- (m|f)ood  -----   moodæˆ–food
- (T|t)he|car   ----- Theã€theã€car

## æ­£åˆ™è¡¨è¾¾å¼åº“ \<regex\>
```cpp
regex re("^[1-9][0-9]{10}$");  // 11ä½æ•°
```
Notice that "\\" is also a è½¬ä¹‰å­—ç¬¦ in Cpp string.
```cpp
regex re("\\d+");   \\ "\d+"
```

### åŸç”Ÿå­—ç¬¦ä¸²

å–æ¶ˆè½¬ä¹‰ï¼Œä¿ç•™å­—é¢å€¼

Syntax:   **R"(str)"**

"\\d+" = R"(\d+)" = \d+

åŸç”Ÿå­—ç¬¦ä¸²æ”¯æŒæ¢è¡Œ

### åŒ¹é…

regex_match(s, re) : è¯¢é—®å­—ç¬¦ä¸²sèƒ½å¦å®Œå…¨åŒ¹é…æ­£åˆ™è¡¨è¾¾å¼re

### æ•è·å’Œåˆ†ç»„

ä½¿ç”¨()è¿›è¡Œæ ‡è¯†ï¼Œæ¯ä¸ªæ ‡è¯†çš„å†…å®¹è¢«ç§°ä½œ**åˆ†ç»„**

- æ­£åˆ™è¡¨è¾¾å¼åŒ¹é…åï¼Œæ¯ä¸ªåˆ†ç»„çš„å†…å®¹å°†è¢«æ•è·
- ç”¨äºæå–å…³é”®ä¿¡æ¯
 
`regex_match(s, result, re)`ï¼š  
è¯¢é—®å­—ç¬¦ä¸²sæ˜¯å¦èƒ½å®Œå…¨åŒ¹é…æ­£åˆ™è¡¨è¾¾å¼reï¼Œå¹¶å°†æ•è·ç»“æœå‚¨å­˜åˆ°resultä¸­

resultéœ€è¦æ˜¯smatchç±»å‹çš„å¯¹è±¡

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

#### åˆ†ç»„ä¼šæŒ‰é¡ºåºæ ‡å·
- 0å·æ°¸è¿œæ˜¯è¢«åŒ¹é…çš„å­—ç¬¦ä¸²æœ¬èº«
- å¦‚æœéœ€è¦æ‹¬å·ï¼Œåˆä¸æƒ³æ•è·è¯¥åˆ†ç»„ï¼Œå¯ä»¥ä½¿ç”¨ **(?:pattern)**

### æœç´¢

`regex_search(s, result, re)` : æœç´¢å­—ç¬¦ä¸²sä¸­èƒ½åŒ¹é…æ­£åˆ™è¡¨è¾¾å¼reçš„**ç¬¬ä¸€ä¸ª**å­ä¸²ï¼Œå¹¶å°†ç»“æœå‚¨å­˜åœ¨ä¸€ä¸ªsmatchå¯¹è±¡resultä¸­

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
  //æ¯æ¬¡æœç´¢æ—¶å½“ä»…ä¿å­˜ç¬¬ä¸€ä¸ªåŒ¹é…åˆ°çš„å­ä¸²
  while(regex_search(s,sm,e)){
    for (unsigned i=0; i<sm.size(); ++i)
      cout << "[" << sm[i] << "] ";
    cout << endl;
    s = sm.suffix().str();  // suffixå¾—åˆ°åŒ¹é…éƒ¨åˆ†çš„åé¢éƒ¨åˆ†
  }
}
```

### æ›¿æ¢

`regex_replace(s, re, s1)` æ›¿æ¢sä¸­**æ‰€æœ‰**åŒ¹é…æ­£åˆ™è¡¨è¾¾å¼reçš„å­ä¸²ï¼Œå¹¶æ›¿æ¢æˆs1

- s1å¯ä»¥æ˜¯ä¸€ä¸ªæ™®é€šæ–‡æœ¬
- ä¹Ÿå¯ä»¥ä½¿ç”¨ä¸€äº›**ç‰¹æ®Šç¬¦å·**ï¼Œä»£è¡¨æ•è·çš„åˆ†ç»„  
  **\$\&** ä»£è¡¨reæ‰€æœ‰åŒ¹é…æˆåŠŸçš„**å­ä¸²**  
  **\$1, \$2** ä»£è¡¨reåŒ¹é…çš„**å­ä¸²ä¸­çš„**ç¬¬1/2ä¸ª**åˆ†ç»„**

**Example**

```cpp
#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main() {
  string s("this subject has a submarine");
  regex e(R"((sub)([\S]*))");
  //regex_replaceè¿”å›å€¼å³ä¸ºæ›¿æ¢åçš„å­—ç¬¦ä¸² 
  cout << regex_replace(s,e,"SUBJECT") << "\n";
  //$&è¡¨ç¤ºæ‰€æœ‰åŒ¹é…æˆåŠŸçš„éƒ¨åˆ†ï¼Œ[$&]è¡¨ç¤ºå°†å…¶ç”¨[]æ‹¬èµ·æ¥
  cout << regex_replace(s,e,"[$&]") << "\n";
  //$iè¾“å‡ºeä¸­ç¬¬iä¸ªæ‹¬å·åŒ¹é…åˆ°çš„å€¼
  cout << regex_replace(s,e,"$1") << "\n";
  cout << regex_replace(s,e,"$1 and [$2]") << "\n";
}
/*
è¾“å‡ºï¼š
this SUBJECT has a SUBJECT
this [subject] has a [submarine]
this sub has a sub
this sub and [ject] has a sub and [marine]
*/
```

## More on re...

### é¢„æŸ¥

- **æ­£å‘é¢„æŸ¥**  
  >ç°åœ¨ï¼Œæˆ‘ä»¬å‡è®¾éœ€è¦ä»…åŒ¹é… Windowsï¼Œä¸åŒ¹é…åé¢çš„ç‰ˆæœ¬å·ï¼Œå¹¶ä¸”è¦æ±‚ Windows åé¢çš„ç‰ˆæœ¬å·åªèƒ½æ˜¯ æ•°å­—ç±»å‹ï¼Œæ¢è¨€ä¹‹ï¼ŒXP å’Œ Vista ä¸èƒ½è¢«åŒ¹é…ï¼Œ  
  åœ¨æ­£åˆ™è¡¨è¾¾å¼ä¸­ï¼Œå¯ä»¥ä½¿ç”¨ æ­£å‘é¢„æŸ¥ æ¥è§£å†³è¿™ä¸ªé—®é¢˜ã€‚æœ¬ä¾‹ä¸­ï¼Œå†™æ³•æ˜¯ï¼šâ€œWindows(?= [\d.]+\b)â€ã€‚  
  å®ƒçš„è¯­æ³•æ˜¯**åœ¨ å­æ¨¡å¼å†…éƒ¨ å‰é¢åŠ â€œ?=â€**ï¼Œè¡¨ç¤ºçš„æ„æ€æ˜¯ï¼šé¦–å…ˆï¼Œè¦åŒ¹é…çš„æ–‡æœ¬**å¿…é¡»æ»¡è¶³æ­¤å­æ¨¡å¼å‰é¢çš„è¡¨è¾¾å¼**(æœ¬ä¾‹ï¼Œâ€œWindows â€)ï¼›å…¶æ¬¡ï¼Œ**æ­¤å­æ¨¡å¼ä¸å‚ä¸åŒ¹é…**ã€‚  
  ä½ ä¹Ÿå¯ä»¥è¿™æ ·ç†è§£ä¸Šé¢çš„åŒ¹é…è¿‡ç¨‹:  
  >1. å…ˆè¿›è¡Œæ™®é€šåŒ¹é…ï¼šWindows ([\d.]+\b)
  >2. ç„¶åä»åŒ¹é…æ–‡æœ¬ä¸­**å°† å­æ¨¡å¼ å†…çš„æ–‡æœ¬æ’é™¤æ‰**ã€‚
  
  å­æ¨¡å¼å†…çš„æ–‡æœ¬ç”±äºä¸å‚ä¸åŒ¹é…ï¼Œæ‰€ä»¥å¯ä»¥å‚ä¸åˆ°åé¢çš„åŒ¹é…ä¸­ï¼
- **åå‘é¢„æŸ¥**
  å°±æ˜¯å­æ¨¡å¼åœ¨è¡¨è¾¾å¼çš„å‰é¢

||æ­£å‘|åå‘|
|----|----|----|
|**è‚¯å®š**|xxx(?=pattern)|(?<=pattern)xxx|
|**å¦å®š**|xxx(?!pattern)|(?<!pattern)xxx|


### åå‘å¼•ç”¨

\b(\w+)\b\s+\1\b åŒ¹é…é‡å¤ä¸¤éçš„å•è¯

æ¯”å¦‚go go æˆ– kitty kitty

![avatar](pics/re_back_reference.png)

### è´ªå©ªä¸æ‡’æƒ°

é»˜è®¤å¤šæ¬¡é‡å¤ä¸ºè´ªå©ªåŒ¹é…ï¼Œå³åŒ¹é…æ¬¡æ•°æœ€å¤š

åœ¨é‡å¤æ¨¡å¼ååŠ ï¼Ÿå¯ä»¥å˜ä¸ºæ‡’æƒ°åŒ¹é…ï¼Œå³åŒ¹é…æ¬¡æ•°æœ€å°‘

|è´ªå©ªå‹|æ‡’æƒ°å‹|
|----|----|
|\*|\*?|
|+|+?|
|{n,}|{n,}?|# STL: å‡½æ•°å¯¹è±¡

## Abstract
- å‡½æ•°å¯¹è±¡

## å‡½æ•°å¯¹è±¡

> å‡½æ•°å = æŒ‡å‘å‡½æ•°çš„æŒ‡é’ˆ

- å‡½æ•°æŒ‡é’ˆçš„å£°æ˜ï¼š
```cpp
    void (*func)(int&);  // <-
// è¿”å›å€¼ | å£°æ˜çš„å˜é‡å    å‚æ•°åˆ—è¡¨
//     æŒ‡é’ˆç¬¦å·
```

- åˆ©ç”¨autoè‡ªåŠ¨æ¨æ–­å‡½æ•°ç±»å‹ï¼š
```cpp
auto func = flag==1?increase:decrease;
for(int &x : arr) { func(x);}
```

### åº”ç”¨ä¸¾ä¾‹ï¼š**std::sort()**

`std::sort(arr, arr + n, comp);`

```cpp
template <class Iterator, class Compare>
void sort(Iterator first, Iterator last, Compare comp);
```

Compareå°±æ˜¯compçš„ç±»å‹ï¼šå‡½æ•°æŒ‡é’ˆ

bool (*)(int,int)

STLæä¾›äº†é¢„å®šä¹‰çš„æ¯”è¾ƒå‡½æ•° (#include \<functional\>)
```cpp
sort(arr, arr+5, less<int>())  
sort(arr, arr+5, greater<int>())
// ä¸ºä½•æœ‰æ‹¬å·ï¼Ÿ
```

### greater\<int\>() æ˜¯ä¸€ä¸ªå¯¹è±¡

- greateræ˜¯ä¸€ä¸ªæ¨¡æ¿ç±»
- greater\<int\> æ˜¯ç”¨intå®ä¾‹åŒ–çš„ç±»
- greater\<int\> è¯¥ç±»çš„ä¸€ä¸ªå¯¹è±¡

åŒæ—¶ï¼Œå®ƒè¡¨ç°å¾—åƒä¸€ä¸ªå‡½æ•°
```cpp
auto func = greater<int>();
cout << func(2,1) << endl;
```
å› æ­¤è¿™ç§å¯¹è±¡è¢«ç§°ä¸ºå‡½æ•°å¯¹è±¡

### å¦‚ä½•å®ç°å‡½æ•°å¯¹è±¡

```cpp
template<class T>
class Greater {
puclic:
    bool operator()(const T &a, const T &b) const {
        return a > b;
    }
};
```
æ³¨æ„ä¸‰ä¸ªconst:
- æ’åºæ—¶compä¸èƒ½ä¿®æ”¹æ•°æ®
- ä¸€èˆ¬æƒ…å†µä¸‹compä¹Ÿä¸åº”è¯¥ä¿®æ”¹è‡ªèº«

### å‡½æ•°å¯¹è±¡çš„è¦æ±‚
- é‡è½½operator()è¿ç®—ç¬¦
- éœ€è¦æ˜¯publicè®¿é—®æƒé™

> å¦‚æœä¸€ä¸ªç‰©ä½“ï¼Œå«å£°åƒé¸­å­ï¼Œèµ°è·¯åƒé¸­å­ï¼Œé‚£ä¹ˆå®ƒå°±æ˜¯é¸­å­
> â€”â€” Duck Typing

### ä¾‹å­ï¼šä¸€ä¸ªç®€å•è®¡ç®—å™¨
è§è¯¾ä»¶

### std::functionç±»

std::functionç±»ï¼Œæ¥è‡ª\<functional\>å¤´æ–‡ä»¶

ä¸º**å‡½æ•°æŒ‡é’ˆä¸å¯¹è±¡**æä¾›äº†**ç»Ÿä¸€çš„æ¥å£**

```cpp
//  function<è¿”å›å€¼(å‚æ•°åˆ—è¡¨)>   arr[] = { some func_ptr/obj }, 
//                              var = func_ptr/obj;

function<string()> readArr[] = {readFromScreen, ReadFromFile()};
function<string(string)> calculateArr[] = {calculateAdd, CalculateMul()};
function<void(string)> writeArr[] = {writeToScreen, WriteToFile()};
```

### å¯¹æ¯”å‡ ç§å®ç°æ–¹å¼

#### ä½¿ç”¨è™šå‡½æ•°å®ç°
- éœ€è¦æ„é€ åŸºç±»å’Œå­ç±»
- æ™šç»‘å®š

#### ä½¿ç”¨æ¨¡æ¿å®ç°
- å¯ä»¥æ”¯æŒå‡½æ•°æŒ‡é’ˆå’Œå‡½æ•°å¯¹è±¡ï¼ˆé€šè¿‡æ¨¡æ¿ï¼Œè‡ªåŠ¨é‡è½½å®ç°ï¼‰
- æ—©ç»‘å®šï¼ˆç¼–è¯‘å™¨ç»‘å®šï¼‰

#### ä½¿ç”¨std::functionå®ç°
- ä¹Ÿå¯ä»¥æ”¯æŒå‡½æ•°æŒ‡é’ˆå’Œå‡½æ•°å¯¹è±¡ï¼ˆé€šè¿‡functionçš„å¤šæ€ï¼‰
- æ™šç»‘å®šï¼ˆè¿è¡Œæ—¶ç»‘å®šï¼‰

![avatar](pics/func_obj_excercise.png)
# æ™ºèƒ½æŒ‡é’ˆä¸å¼•ç”¨è®¡æ•°

> Aã€Bå¯¹è±¡å…±äº«ä¸€ä¸ªCå¯¹è±¡ï¼ŒCä¸æƒ³äº¤ç”±å¤–éƒ¨é”€æ¯  
> åº”å½“åœ¨Aã€Béƒ½é”€æ¯æ—¶Cæ‰èƒ½é”€æ¯  
> å¦‚ä½•è‡ªåŠ¨å¤„ç†ï¼Ÿ

## æ™ºèƒ½æŒ‡é’ˆ

**shared_ptr**  \<memory\>åº“
```cpp
#include <memory>
shared_ptr<int> p1(new int(1));
shared_ptr<MyClass> p2 = make_shared<MyClass>(2);
shared_ptr<MyClass> p3 = p2;
shared_ptr<int> p4;

int x = *p1;
int y = p2->val;

// p2å’Œp3æŒ‡å‘åŒä¸€å¯¹è±¡ï¼Œå½“ä¸¤è€…å‡å‡ºä½œç”¨åŸŸæ‰ä¼šè¢«é”€æ¯ï¼

```

## å¼•ç”¨è®¡æ•°

æ™ºèƒ½æŒ‡é’ˆä¾é **å¼•ç”¨è®¡æ•°**æ¥åˆ¤æ–­ä½•æ—¶é”€æ¯å¯¹è±¡

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
	}	//p2å‡ºä½œç”¨åŸŸ
	cout << p1.use_count() << ' '; // 1
}
```

### å®ç°è‡ªå·±çš„å¼•ç”¨è®¡æ•°
> å“ªä¸ªç”·å­©ä¸æƒ³æ‹¥æœ‰å±äºè‡ªå·±çš„å¼•ç”¨è®¡æ•°å‘¢ï¼Ÿ

```cpp
template <typename T>
class SmartPtr;

template <typename T>
class U_Ptr {
private:
    friend class SmartPtr<T>;
    U_Ptr(T *ptr) : p(ptr), count(1) {}
    ~Uptr() { delete p;}

    int count;  // å¼•ç”¨è®¡æ•°
    T *p;   // å®é™…æ•°æ®å­˜æ”¾
};

class SmartPtr {
    U_Ptr *rp;
public:
    // æ„é€ å‡½æ•°ï¼šåˆå§‹åŒ–æˆå‘˜è¾…åŠ©æŒ‡é’ˆrpï¼Œå°†ç±»å‹Tçš„æ•°æ®å­˜æ”¾ç»™rp
    SmartPtr(T *ptr) :rp(new U_Ptr<T>(ptr)) {}
    // æ‹·è´æ„é€ å‡½æ•°ï¼šå…ˆåˆå§‹åŒ–rpä¸ºæ¥æºrpï¼Œå¹¶å°†rpçš„è®¡æ•°+1
    SmartPtr(const SmartPtr<T> &sp) :rp(sp.rp) {
        ++rp->count;
    }
    // èµ‹å€¼è¿ç®—ç¬¦ï¼šå°†åŸå…ˆçš„å¼•ç”¨è®¡æ•°-1ï¼Œå¦‚æœä¸º0åˆ™åˆ é™¤ï¼›å†æ¢æ–°çš„rp
    SmartPtr& operator=(const SmartPtr<T>& rhs) {
        ++rhs.rp->count;
        if(--rp->count == 0)
            delete rp;
        rp = rhs.rp;
        return *this;
    }
    // ææ„
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

## shared_ptrçš„å…¶ä»–ç”¨æ³•

```cpp
p.get() //è·å–è£¸æŒ‡é’ˆ
p.reset() // æ¸…é™¤æŒ‡é’ˆå¹¶å‡å°‘å¼•ç”¨æ¬¡æ•°
static_pointer_cast<int>(p)
dynamic_pointer_cast<Base>(p)
```

æ³¨æ„ï¼
- ä¸èƒ½ä½¿ç”¨åŒä¸€ä¸ªè£¸æŒ‡é’ˆåˆå§‹åŒ–å¤šä¸ªæ™ºèƒ½æŒ‡é’ˆï¼Œä¼šäº§ç”Ÿå¤šä¸ªè¾…åŠ©æŒ‡é’ˆï¼
- ä¸èƒ½ç›´æ¥ä½¿ç”¨æ™ºèƒ½æŒ‡é’ˆç»´æŠ¤**å¯¹è±¡æ•°ç»„**  
  å› ä¸ºåˆ é™¤æ•°ç»„éœ€è¦delete[], è€Œæ™ºèƒ½æŒ‡é’ˆæ‰€æœ‰çš„å®ç°éƒ½æ˜¯delete p;

## æ™ºèƒ½æŒ‡é’ˆå¹¶ä¸æ€»æ˜¯æ™ºèƒ½çš„

å½“å‡ºç°ç¯çŠ¶ç»“æ„ï¼ˆå¦‚ä¸¤ä¸ªå¯¹è±¡äº’ç›¸ç”¨æ™ºèƒ½æŒ‡é’ˆæŒ‡å‘å¯¹æ–¹ï¼‰æ—¶ï¼Œå¯¹è±¡ä¸èƒ½å¤Ÿæ­£ç¡®åœ°é”€æ¯

### How to fix this?

- å¼±å¼•ç”¨ **weak_ptr**     **æŒ‡å‘å¯¹è±¡ä½†ä¸è®¡æ•°**
  ```cpp
  shared_ptr<int> sp(new int(3));
  weak_ptr<int> wp1 = sp;

  //Usage:
  wp.use_count()
  wp.reset()    // é‡Šæ”¾æŒ‡é’ˆ
  wp.expired()  // æ£€æŸ¥å¯¹è±¡æ˜¯å¦æ— æ•ˆ
  sp = wp.lock()    // ä»å¼±å¼•ç”¨è·å¾—ä¸€ä¸ªæ™ºèƒ½æŒ‡é’ˆ
  ```
- ç‹¬å æ‰€æœ‰æƒ **unique_ptr ä¿è¯å¯¹è±¡åªè¢«ä¸€ä¸ªæŒ‡é’ˆå¼•ç”¨**
  ```cpp
  auto up1 = std::make_unique<int>(20);
  unique_ptr<int> up2 = std::move(up1); // å¯ä»¥ç§»åŠ¨uniqueæŒ‡é’ˆ(ç§»äº¤æ§åˆ¶æƒ)
  int *p = up2.release();               // æ”¾å¼ƒæŒ‡é’ˆæ§åˆ¶æƒï¼Œè¿”å›è£¸æŒ‡é’ˆ
  delete p;
  ```

## æ™ºèƒ½æŒ‡é’ˆæ€»ç»“

### ä¼˜ç‚¹
- å¯ä»¥å¸®åŠ©ç®¡ç†å†…å­˜ï¼Œé¿å…å†…å­˜æ³„æ¼
- åŒºåˆ†unique_ptrå’Œshared_ptrèƒ½å¤Ÿæ˜ç¡®è¯­ä¹‰
- åœ¨æ‰‹åŠ¨ç»´æŠ¤æŒ‡é’ˆä¸å¯è¡Œï¼Œå¤åˆ¶å¯¹è±¡å¼€é”€å¤ªå¤§æ—¶ï¼Œæ™ºèƒ½æŒ‡é’ˆæ˜¯å”¯ä¸€é€‰æ‹©

### ç¼ºç‚¹
- å¼•ç”¨è®¡æ•°ä¼šå½±å“æ€§èƒ½
- æ™ºèƒ½æŒ‡é’ˆä¸æ€»æ˜¯æ™ºèƒ½ï¼Œéœ€è¦äº†è§£å†…éƒ¨åŸç†
- éœ€è¦å°å¿ƒç¯çŠ¶ç»“æ„å’Œæ•°ç»„æŒ‡é’ˆ# å¹¶å‘ç¼–ç¨‹ä¸å¹¶å‘è®¾è®¡æ¨¡å¼

## Abstract
- å¹¶å‘ç¼–ç¨‹
- threadä¸ä¸»ä»æ¨¡å¼
- mutexä¸äº’æ–¥é”æ¨¡å¼
- async,future,promiseä¸å¼‚æ­¥

## å¹¶å‘ç¼–ç¨‹

### â€œå¹¶å‘â€ä¸â€œå¹¶è¡Œâ€
- **ä¸€ä¸ªæ—¶é—´æ®µå†…**å‡ ä¸ªç¨‹åºéƒ½å¤„äºå¯åŠ¨åˆ°å®Œæˆä¹‹é—´ï¼š**å®è§‚ä¸Š***åŒæ—¶*
- â€œå¹¶å‘â€ï¼šä»»æ„æ—¶åˆ»**åªæœ‰ä¸€ä¸ªç¨‹åº**åœ¨è®¡ç®—å•å…ƒä¸Šè¿è¡Œï¼š**å¾®è§‚ä¸Š***é¡ºåºæ‰§è¡Œ*
- â€œå¹¶è¡Œâ€ï¼šä»»æ„æ—¶åˆ»**å¯ä»¥æœ‰å¤šä¸ªç¨‹åº**è¿è¡Œï¼š**å¾®è§‚ä¸Š**ä¹Ÿå¯ä»¥æ˜¯*åŒæ—¶*

å¹¶å‘ã€å¹¶è¡Œéƒ½æ˜¯**å¤šä»»åŠ¡**ç¯å¢ƒä¸‹çš„ç³»ç»Ÿ

### â€œè¿›ç¨‹â€ä¸â€œçº¿ç¨‹â€

**è¿›ç¨‹ process**  
- å·²è¿è¡Œçš„ç¨‹åº
  
**çº¿ç¨‹ thread**  
- æ˜¯æ“ä½œç³»ç»Ÿèƒ½å¤Ÿè¿›è¡Œ**è¿ç®—è°ƒåº¦**çš„**æœ€å°å•ä½**
- å®ƒè¢«åŒ…å«åœ¨è¿›ç¨‹ä¹‹ä¸­ï¼Œæ˜¯è¿›ç¨‹ä¸­çš„å®é™…è¿ä½œå•ä½
- **ä¸€ä¸ªè¿›ç¨‹**å¯ä»¥**å¹¶å‘å¤šä¸ªçº¿ç¨‹**ï¼Œè®¾å¤‡å…è®¸çš„æƒ…å†µä¸‹ï¼Œæ•°ä¸ªçº¿ç¨‹å¯ä»¥å¹¶è¡Œæ‰§è¡Œä¸åŒçš„ä»»åŠ¡
- åŒä¸€è¿›ç¨‹çš„å¤šæ¡çº¿ç¨‹**å…±äº«**è¯¥è¿›ç¨‹çš„å…¨éƒ¨**ç³»ç»Ÿèµ„æº**ï¼Œå¦‚è™šæ‹Ÿåœ°å€ç©ºé—´ï¼Œæ–‡ä»¶æè¿°ç¬¦å’Œä¿¡æ¯å¤„ç†ç­‰

## threadä¸ä¸»ä»æ¨¡å¼

### thread ç±»
ç¤ºä¾‹ï¼šcode/thread.cpp
- **é»˜è®¤æ„é€ å‡½æ•°**   
  å®šä¹‰ï¼š  
  `thread() noexcept;`  
  åˆ›å»ºä¸€ä¸ªç©ºçº¿ç¨‹å¯¹è±¡ï¼Œä¸ä»£è¡¨ä»»ä½•å¯æ‰§è¡Œçš„çº¿ç¨‹  
  ä¾‹ï¼š`thread s1;`
- **åˆå§‹åŒ–æ„é€ å‡½æ•°**  
  å®šä¹‰ï¼š  
  ```
  template <class Fn, class ... Args> 
  explicit thread (Fn&&, Args&& ... args);
  ```
  æ³¨æ„ï¼šçº¿ç¨‹ä¸€æ—¦åˆ›å»ºï¼Œçº¿ç¨‹å°±å¼€å§‹æ‰§è¡Œ
  - å¯ä»¥ä¸å¯è°ƒç”¨å¯¹è±¡ï¼ˆCallable Objectsï¼‰ä¸€èµ·ä½¿ç”¨
  - å¦‚ Lambda è¡¨è¾¾å¼
  - ```cpp
    thread t(
      [] (int a,int b) {
        cout << a + b << endl;
      }.
      1, 2);
      t.join();
    ```
- **æ‹·è´æ„é€ å‡½æ•°**  
  **è¢«ç¦ç”¨**ï¼Œå› ä¸ºthreadä¸å¯è¢«æ‹·è´æ„é€ ï¼ˆçº¿ç¨‹æ¶‰åŠç³»ç»Ÿåº•å±‚ï¼‰
- **ç§»åŠ¨æ„é€ å‡½æ•°**  
  å®šä¹‰ï¼š  
  `thread (thread&& x) noexcept;`
  æœ‰é»˜è®¤çš„ç§»åŠ¨æ„é€ å‡½æ•°ï¼Œè°ƒç”¨æˆåŠŸåxä¸æŒ‡å‘ä»»ä½•å…·ä½“æ‰§è¡Œçº¿ç¨‹

### join detach
threadæä¾›äº†ä¸¤ç§æ¥å£æ¥å¤„ç†å½“å‰çº¿ç¨‹ä¸ç›®æ ‡çº¿ç¨‹

- **thread::join()**  
  è°ƒç”¨è¯¥æ¥å£æ—¶ï¼Œå½“å‰çº¿ç¨‹ä¼šä¸€ç›´é˜»å¡ï¼Œç›´åˆ°ç›®æ ‡çº¿ç¨‹æ‰§è¡Œå®Œæˆ
- **thread::detach()**
  - è°ƒç”¨æ­¤æ¥å£æ—¶ï¼Œç›®æ ‡çº¿ç¨‹æˆä¸ºå®ˆæŠ¤çº¿ç¨‹ï¼ˆdaemon threadsï¼‰ï¼Œå°†å®Œå…¨ç‹¬ç«‹æ‰§è¡Œ
  - å³ä½¿ç›®æ ‡çº¿ç¨‹å¯¹åº”çš„threadå¯¹è±¡è¢«é”€æ¯ä¹Ÿä¸å½±å“çº¿ç¨‹çš„æ‰§è¡Œ

### joinable
thread::joinable() å¯ä»¥åˆ¤æ–­ threadå®ä¾‹æŒ‡å‘çš„çº¿ç¨‹æ˜¯å¦å¯ä»¥ join æˆ–è€… detach

ä¸‰ç§æƒ…å†µä¸‹threadå®ä¾‹ä¸æ˜¯joinableï¼š
- é»˜è®¤æ„é€ å‡½æ•°åˆ›å»ºçš„å®ä¾‹ï¼ˆä¸æŒ‡å‘ä»»ä½•å…·ä½“çš„æ‰§è¡Œçº¿ç¨‹ï¼‰
- è¢«ç§»åŠ¨æ„é€ å‡½æ•°æ“ä½œè¿‡çš„å®ä¾‹
- å·²ç»è°ƒç”¨è¿‡join()æˆ–è€…detach()çš„å®ä¾‹

å¯åŠ¨ç›®æ ‡çº¿ç¨‹åï¼Œå¿…é¡»å†³å®šå½“å‰çº¿ç¨‹æ˜¯è¦ç­‰å¾…ç›®æ ‡çº¿ç¨‹ç»“æŸï¼ˆjoinï¼‰ï¼Œè¿˜æ˜¯è®©ç›®æ ‡çº¿ç¨‹ç‹¬ç«‹ï¼ˆdetachï¼‰ï¼Œ**å¿…é¡»äºŒé€‰ä¸€**

å¦‚æœç›®æ ‡çº¿ç¨‹çš„threadå¯¹è±¡é”€æ¯æ—¶ä¾ç„¶æ²¡æœ‰è°ƒç”¨joinæˆ–è€…detachï¼Œthreadå¯¹è±¡åœ¨ææ„æ—¶å°†å¯¼è‡´ç¨‹åºè¿›ç¨‹å¼‚å¸¸é€€å‡º

å³thread**ææ„æ—¶å¿…é¡»æ˜¯éjoinableçš„çŠ¶æ€**

### ç›¸å…³åŠŸèƒ½æ€§æ¥å£

- `this_thread::get_id`
- `this_thread::sleep_for`
- `this_thread::sleep_until`
- `this_thread::yield`

### ä¸»ä»æ¨¡å¼

ç¤ºä¾‹ï¼šcode/thread_prime.cpp

![avatar](pics/master_worker.png)

é€‚ç”¨åœºæ™¯
- æ•´ä½“ä»»åŠ¡å¯ä»¥è¢«åˆ’åˆ†ä¸ºè¯¸å¤šå­ä»»åŠ¡
- å­ä»»åŠ¡é—´å…³è”è¾ƒå¼±ï¼Œå¯ä»¥å¹¶å‘æ‰§è¡Œ
- è®¡ç®—è®¾å¤‡æ”¯æŒå¤šä»»åŠ¡åŒæ—¶æ‰§è¡Œ

## mutexä¸äº’æ–¥é”æ¨¡å¼

ç¤ºä¾‹äºŒï¼šä¿®æ”¹ç¤ºä¾‹ä¸€ï¼šè®©æ¯ä¸ªå­çº¿ç¨‹ç›´æ¥ä¿®æ”¹å…¨å±€å˜é‡total

å‡ºé”™ï¼

### ç«äº‰æ¡ä»¶ä¸ä¸´ç•ŒåŒº

- ç«äº‰æ¡ä»¶  
  - å¤šä¸ªçº¿ç¨‹åŒæ—¶è®¿é—®å…±äº«æ•°æ®æ—¶ï¼Œåªè¦æœ‰ä¸€ä¸ªä»»åŠ¡ä¿®æ”¹æ•°æ®ï¼Œé‚£ä¹ˆå°±å¯èƒ½ä¼šå‘ç”Ÿé—®é¢˜â€”â€”å¤šä¸ªçº¿ç¨‹åŒæ—¶äº‰ç›¸ä¿®æ”¹æ•°æ®ï¼Œå¯¼è‡´éƒ¨åˆ†ä¿®æ”¹æ²¡æœ‰æˆåŠŸã€‚è¿™ç§åœºæ™¯ç§°ä¸º**ç«äº‰æ¡ä»¶ï¼ˆrace conditionï¼‰**
- ä¸´ç•ŒåŒº  
  - è®¿é—®å…±äº«æ•°æ®çš„ä»£ç ç‰‡æ®µç§°ä¸º**ä¸´ç•ŒåŒºï¼ˆcritical sectionï¼‰**ï¼Œå¦‚ç¤ºä¾‹ä¸­çš„total++;
- é¿å…ç«äº‰æ¡ä»¶éœ€è¦å¯¹ä¸´ç•ŒåŒºè¿›è¡Œæ•°æ®ä¿æŠ¤  
  - ä¸€æ¬¡åªèƒ½è®©ä¸€ä¸ªçº¿ç¨‹è®¿é—®å…±äº«æ•°æ®
  - è®¿é—®å®Œäº†å†è®©å…¶ä»–çº¿ç¨‹æ¥ç€è®¿é—®

### äº’æ–¥é‡mutexä¸é”lock()

äº’æ–¥é‡mutexæœ¬èº«æ˜¯ä¸€ä¸ªç±»å¯¹è±¡ï¼Œä¸€èˆ¬ä¹Ÿæˆä¸ºâ€œé”â€

- å„ä¸ªçº¿ç¨‹å¯ä»¥**å°è¯•ç”¨mutexçš„lock()æ¥å£**å¯¹ä¸´ç•ŒåŒºæ•°æ®è¿›è¡ŒåŠ é”
  - æ¯æ¬¡åªæœ‰ä¸€ä¸ªçº¿ç¨‹èƒ½å¤Ÿé”å®šæˆåŠŸï¼Œæ ‡å¿—æ˜¯lock()æˆåŠŸè¿”å›
  - å¦‚æœæ²¡é”æˆåŠŸï¼Œåˆ™çº¿ç¨‹ä¼šé˜»å¡åœ¨é‚£é‡Œ
  - ä¸´ç•ŒåŒº**å°±åƒä¸€é—´åªèƒ½åé”çš„æˆ¿é—´**
- mutexçš„unlock()æ¥å£å¯ä»¥è§£é”äº’æ–¥é‡

å®ç°æ–¹æ³•ï¼ˆç¤ºä¾‹äºŒï¼‰ï¼š
```cpp
// å…¨å±€å˜é‡
static mutex exclusive;

// æ–¹æ³•ä¸€ï¼šç›´æ¥åœ¨total++;å‘¨å›´ä¸Šé”
if(check_num(i)) {
  exclusive.lock();
  total++;
  exclusive.unlock();
}

// æ–¹æ³•äºŒï¼š æ¯ä¸ªçº¿ç¨‹å„è‡ªç»Ÿè®¡å®Œä¹‹åå†åŠ å…¥total
for (...) if(check_num(i)) tmp_total++;
exclusive.lock();
total+=tmp_total;
exclusive.unlock();

// æ–¹æ³•äºŒæ•ˆç‡æ›´é«˜ï¼Œå› ä¸ºé”çš„å¼€å…³éœ€è¦æ—¶é—´ï¼Œæ–¹æ³•äºŒçš„é”çš„è°ƒç”¨æ¬¡æ•°æ›´å°‘
```

#### äº’æ–¥é”æ¨¡å¼çš„å¼Šç«¯

- ä½æ•ˆâ€”â€”å…±äº«èµ„æºçš„è¯»æ“ä½œå¾€å¾€å¹¶ä¸éœ€è¦äº’æ–¥
- è§£å†³æ–¹æ¡ˆâ€”â€”é‡‡ç”¨**è¯»å†™é”æ¨¡å¼**ï¼Œè¯»æ˜¯å…±äº«ï¼Œå†™æ˜¯äº’æ–¥

### å…¶ä»–äº’æ–¥é‡

- timed_mutex
- recursive_mutex
- recursive_timed_mutex
- shared_mutex

## asyncã€futureã€promise ä¸ å¼‚æ­¥

**æ¡ˆä¾‹ä¸‰ï¼š** éœ€æ±‚ï¼šä¸æ–­è¾“å…¥æ•´æ•°n,åˆ¤æ–­næ˜¯å¦ä¸ºç´ æ•° async_prime.cpp

èƒ½å¦è®©è¾“å…¥ä¸å—åˆ¤æ–­æ–¹æ³•çš„é˜»å¡ï¼Ÿ

### åŒæ­¥å’Œå¼‚æ­¥

- **åŒæ­¥ï¼ˆSynchronousï¼‰**  
  åŒæ­¥è°ƒç”¨ä¸€æ—¦å¼€å§‹ï¼Œè°ƒç”¨è€…å¿…é¡»ç­‰åˆ°è°ƒç”¨è¿”å›ç»“æœåæ‰èƒ½ç»§ç»­åç»­çš„è¡Œä¸º
  
  ![avatar](pics/synchronous.png)
- **å¼‚æ­¥ï¼ˆAsynchronousï¼‰**  
  å¼‚æ­¥è°ƒç”¨ä¸€æ—¦å¼€å§‹ï¼Œè¢«è°ƒç”¨æ–¹æ³•å°±ä¼šç«‹å³è¿”å›ï¼Œè°ƒç”¨è€…å¯ä»¥æ— é˜»å¡ç»§ç»­åç»­çš„æ“ä½œ

  è¢«è°ƒç”¨æ–¹æ³•é€šå¸¸ä¼šåœ¨å¦å¤–ä¸€ä¸ªçº¿ç¨‹ä¸­é»˜é»˜è¿è¡Œï¼Œæ•´ä¸ªè¿‡ç¨‹ï¼Œä¸ä¼šé˜»ç¢è°ƒç”¨è€…çš„å·¥ä½œ

  è¢«è°ƒç”¨æ–¹æ³•å®Œæˆåå¯ä»¥é€šè¿‡ç‰¹æ®Šæœºåˆ¶ä¼ é€’ä¿¡æ¯ç»™è°ƒç”¨è€…

  ![avatar](pics/asynchronous.png)

### async

```cpp
future async (Fn&& fn, Args&&...args);
future async (launch policy, Fn&& fn, Args&&...args);
```

asyncä¼šè¿”å›ä¸€ä¸ªfutureå¯¹è±¡ï¼Œç”¨æ¥å­˜å‚¨å¼‚æ­¥ä»»åŠ¡çš„æ‰§è¡ŒçŠ¶æ€å’Œç»“æœ

policyæœ‰ä¸‰ç§é€‰æ‹©
- launch::async ä¿è¯å¼‚æ­¥è¡Œä¸ºï¼Œæ‰§è¡Œåï¼Œç³»ç»Ÿåˆ›å»ºä¸€ä¸ªçº¿ç¨‹ï¼Œæ‰§è¡Œå¯¹åº”çš„å‡½æ•°
- launch::deffered è¡¨ç¤ºå»¶è¿Ÿè°ƒç”¨ï¼Œåœ¨è°ƒç”¨futureä¸­çš„wait()æˆ–è€…get()å‡½æ•°æ—¶ï¼Œæ‰æ‰§è¡Œå…¥å£å‡½æ•°
- launch::async||launch::deffered é»˜è®¤ç­–ç•¥ï¼Œç”±ç³»ç»Ÿè‡ªè¡Œå†³å®šæ€ä¹ˆè°ƒç”¨

### future

futureç±»æä¾›è®¿é—®å¼‚æ­¥æ“ä½œç»“æœçš„æ¥å£
- **wait()** æ¥å£ï¼Œé˜»å¡å½“å‰çº¿ç¨‹ï¼Œç­‰å¾…å¼‚æ­¥çº¿ç¨‹ç»“æŸ
- **get()** æ¥å£ï¼Œè·å–å¼‚æ­¥çº¿ç¨‹æ‰§è¡Œç»“æœ
  - éœ€è¦æ³¨æ„çš„æ˜¯ï¼Œ**futureå¯¹è±¡åªèƒ½è¢«ä¸€ä¸ªçº¿ç¨‹è·å–å€¼**ï¼Œå¹¶ä¸”åœ¨è°ƒç”¨get()ä¹‹åå°±æ²¡æœ‰å¯ä»¥è·å–çš„å€¼äº†
  - å¦‚æœå¤šä¸ªçº¿ç¨‹è°ƒç”¨åŒä¸€ä¸ªfutureå®ä¾‹çš„get()ä¼šå‡ºç°æ•°æ®ç«äº‰ï¼Œå…¶ç»“æœæ˜¯æœªå®šä¹‰çš„
  - è°ƒç”¨get()å¦‚æœå¼‚æ­¥çº¿ç¨‹æ²¡æœ‰ç»“æŸä¼šä¸€ç›´ç­‰å¾…ï¼Œç±»ä¼¼wait()
- **wait_for(timeout_duration)** å¦‚æœåœ¨åˆ¶å®šè¶…æ—¶é—´é—´éš”åä»ç„¶æ²¡æœ‰ç»“æŸå¼‚æ­¥çº¿ç¨‹ï¼Œåˆ™**è¿”å›ç›®æ ‡çº¿ç¨‹å½“å‰çŠ¶æ€**ï¼Œå¹¶**å–æ¶ˆwait_forçš„é˜»å¡**
  - future_status::deferred ä»æœªå¯åŠ¨
  - future_status::ready ç»“æœå°±ç»ª
  - future_status::timeout å·²è¶…æ—¶é™ï¼Œå¼‚æ­¥çº¿ç¨‹ä»åœ¨æ‰§è¡Œ

### ä½¿ç”¨asyncå’Œfutureå®Œæˆæ¡ˆä¾‹ä¸‰

æ„å»ºè¿ç®—ä¸é˜»å¡è¾“å…¥çš„ç¨‹åºï¼š
- ä½¿ç”¨å¼‚æ­¥çº¿ç¨‹è¿›è¡Œè¿ç®—
- ä½¿ç”¨ä¸»çº¿ç¨‹è¿›è¡ŒçŠ¶æ€ç®¡ç†
- ä¸»çº¿ç¨‹**ä¸æ–­æ£€æŸ¥**è¾“å…¥çŠ¶æ€å’Œå¼‚æ­¥çº¿ç¨‹çš„æ‰§è¡ŒçŠ¶æ€ï¼šæœ‰è¾“å…¥ç«‹åˆ»åˆ›å»ºæ–°çš„å¼‚æ­¥çº¿ç¨‹è¿›è¡Œå¤„ç†ï¼›æŸä¸€ä¸ªå¼‚æ­¥çº¿ç¨‹å®Œæˆåï¼Œç«‹åˆ»è¾“å‡ºå¤„ç†ç»“æœ

è¿™ç§ä¸æ–­æ¶ˆè€—æçŸ­æ—¶é—´è¿›è¡Œæ£€æµ‹çš„æ–¹å¼å°±æ˜¯**è½®è¯¢**

### è½®è¯¢

![avatar](pics/polling.png)

### promise

ä¸€èˆ¬æµç¨‹
- åœ¨å½“å‰çº¿ç¨‹ä¸­åˆ›å»ºpromiseå¯¹è±¡ï¼Œå¹¶ä»è¯¥promiseå¯¹è±¡ä¸­è·å¾—å¯¹åº”çš„futureå¯¹è±¡
- å°†promiseå¯¹è±¡ä¼ é€’ç»™ç›®æ ‡çº¿ç¨‹ï¼Œç›®æ ‡çº¿ç¨‹é€šè¿‡promiseçš„æ¥å£è®¾ç½®ç‰¹å®šå€¼ï¼Œ**ç„¶åå¯ä»¥ç»§ç»­æ‰§è¡Œç›®æ ‡çº¿ç¨‹è‡ªèº«çš„å·¥ä½œ**
- åœ¨ç‰¹å®šæ—¶é—´ï¼Œå½“å‰çº¿ç¨‹æŒ‰éœ€æ±‚é€šè¿‡promiseå¯¹åº”çš„futureå–å€¼
# ×éºÏÓë¼Ì³Ğ Composition and Inheritance

## Abstract

1. ×éºÏ
2. ¼Ì³Ğ
3. ³ÉÔ±·ÃÎÊÈ¨ÏŞ
4. ÖØĞ´Òş²ØÓëÖØÔØ
5. ¶àÖØ¼Ì³Ğ

## ×éºÏ

***ÕûÌå-²¿·Ö*** ¹ØÏµÎª ***×éºÏ*** »ò *has-a* ¹ØÏµ

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

¶ÔÏó¿½±´Óë¸³ÖµÔËËã£º ÂÔ

## ¼Ì³Ğ

"is-a"¡¢"Ò»°ã-ÌØÊâ" ½á¹¹

base class »ùÀà/¸¸Àà  
--> derived class ÅÉÉúÀà/×ÓÀà/ÍØÕ¹Àà

### Way of Inheritance  
```cpp
class <Derived_Class_Name> : [private] <Base_Name> { .. }; // Default way of succession:private
class <Derived_Class_Name> : public <Base_Name> { .. };
class <Derived_Class_Name> : protected <Base_Name> { .. }; // Rarely used
```

### What **cannot** be Inherited
- ¹¹Ôìº¯Êı
- Îö¹¹º¯Êı
- ¸³ÖµÔËËã·û    Includes the parameter which is of its class
- ÓÑÔªº¯Êı      Not member of the class  

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

### ÅÉÉúÀà¶ÔÏóµÄ¹¹ÔìÓëÎö¹¹

#### ¹¹Ôì£ºĞèÒªµ÷ÓÃ»ùÀà¹¹Ôìº¯Êı
- Ã»ÓĞÏÔÊ½µ÷ÓÃ£º×Ô¶¯Éú³É¶Ô»ùÀàµÄÄ¬ÈÏ¹¹Ôìº¯ÊıµÄµ÷ÓÃ
- ÔÚ¹¹Ôìº¯ÊıµÄ³õÊ¼»¯³ÉÔ±ÁĞ±íÖĞ½øĞĞÏÔÊ½µ÷ÓÃ
- - µ÷ÓÃ»ùÀàÖĞ²»´ø²ÎÊıµÄÄ¬ÈÏ¹¹Ôìº¯Êı
- - µ÷ÓÃºÏÊÊµÄ´ø²ÎÊıµÄÆäËû¹¹Ôìº¯Êı

```cpp
class Base{
    int data;
public:
    Base() : data(0) {cout << "Base::Base("<<data<<")\n";}
    Base(int i): data(i) {cout << "Base::Base("<<data<<")\n";}
};
class Derive : public Base{
public:
    // ×¢Òâ£ºÒÔÏÂ´úÂëÃ¿Ò»ĞĞÎª²»Í¬µÄ¹¹Ôìº¯Êı£¬ÔÚÍ¬Ò»³ÌĞòÖĞÖ»³öÏÖÆäÖĞÒ»¸ö
    // 1.ÎŞÏÔÊ½µ÷ÓÃ»ùÀà¹¹Ôìº¯Êı£¬µ÷ÓÃ»ùÀàÄ¬ÈÏ¹¹Ôìº¯Êı
    Derive() { cout << "Derive::Derive()"<< endl;}  
    // 2.ÏÔÊ½µ÷ÓÃ»ùÀà¹¹Ôìº¯Êı
    Derive(int i) : Base(i) { cout << "Derive::Derive()"<< endl;}
    // 3.¼Ì³Ğ»ùÀà¹¹Ôìº¯Êı
    using Base::Base; ///Ïàµ±ÓÚ Derive(int i):Base(i){}
    // µ±»ùÀà´æÔÚ¶à¸ö¹¹Ôìº¯ÊıÊ±,
    // Ê¹ÓÃusing»á¸øÅÉÉúÀà×Ô¶¯¹¹Ôì¶à¸öÏàÓ¦µÄ¹¹Ôìº¯Êı
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

#### ×¢Òâ
- Èç¹û»ùÀàµÄÄ³¸ö¹¹Ôìº¯Êı±»ÉùÃ÷ÎªË½ÓĞ£¬ÔòÅÉÉúÀàÖĞ²»ÄÜÉùÃ÷¼Ì³Ğ¸Ã¹¹Ôìº¯Êı
- Èç¹ûÅÉÉúÀàÊ¹ÓÃÁË¼Ì³Ğ¹¹Ôìº¯Êı£¬±àÒëÆ÷¾Í²»»áÔÙÎªÅÉÉúÀàÉú³ÉÄ¬ÈÏ¹¹Ôìº¯Êı

### How to choose way of inheritance

#### public Inherit
»ùÀàÖĞ¹«ÓĞ³ÉÔ±ÔÚÅÉÉúÀàÖĞ±£³Ö¹«ÓĞ£¬Ô­½Ó¿Ú¿ÉÑØÓÃ  
is-a: »ùÀà¶ÔÏóÄÜÊ¹ÓÃµÄµØ·½£¬ÅÉÉúÀà¶ÔÏóÒ²ÄÜÊ¹ÓÃ  
#### private Inherit
is-implementing-in-terms-of(ÕÕ´ËÊµÏÖ)£ºÓÃ»ùÀà½Ó¿ÚÊµÏÖÅÉÉúÀà¹¦ÄÜ£¬ÒÆ³ıis-a¹ØÏµ  
Í¨³£²»Ê¹ÓÃ£¬**ÓÃ×éºÏÌæ´ú**£¬¿ÉÓÃÓÚÒş²Ø/¹«¿ª»ùÀàµÄ²¿·Ö½Ó¿Ú¡£  
¹«¿ª·½·¨£º ÔÚ public ²¿·Ö Ê¹ÓÃ using ¹Ø¼ü×Ö  
// »ùÀà¹«ÓĞ³ÉÔ±£¨½Ó¿Ú£© ±ä ÅÉÉúÀàË½ÓĞ³ÉÔ±£¨¹¦ÄÜ£©

## ³ÉÔ±·ÃÎÊÈ¨ÏŞ

|¼Ì³Ğ±í||¼Ì³Ğ·½·¨|||
|----|----|----|----|----|
|||public|private|protected|
|»ùÀà¡ı|public|OK(pub/yes)|OK(prv/no)|OK(pro/no)|
|³ÉÔ±¡ı|private|NO(prv/no)|NO(prv/no)|NO(prv/no)|
|ÀàĞÍ|protected|OK(pro/no)|OK(prv/no)|OK(pro/no)|

OK/NO : **ÅÉÉúÀà³ÉÔ±º¯Êı**ÄÜ·ñ·ÃÎÊ»ùÀà³ÉÔ±  
pub/pro/prv/ : »ùÀà³ÉÔ±ÔÚÅÉÉúÀàÖĞµÄ³ÉÔ±ÀàĞÍ  
yes/no : **ÅÉÉúÀà¶ÔÏó**ÄÜ·ñ·ÃÎÊ»ùÀà³ÉÔ±(//¼´ÄÜ·ñµ÷ÓÃº¯Êı»òÄÜ¶ÁĞ´Êı¾İ)

#### Some Notes  
- »ùÀàÖĞË½ÓĞ³ÉÔ±ÎŞÂÛÈçºÎ¶¼²»ÄÜ±»ÆäËûÀà£¨¶ÔÏó/³ÉÔ±º¯Êı£©·ÃÎÊ¡££¨Ë½ÓĞµÄÎŞÂÛÊ²Ã´Ê±ºò¶¼ÊÇË½ÓĞµÄ£©  
- ÅÉÉúÀà**¶ÔÏó**²»¿É·ÃÎÊ»ùÀàÖĞ±£»¤³ÉÔ±£¬µ«**³ÉÔ±º¯Êı**¿ÉÒÔ

## ×éºÏÓë¼Ì³Ğ ¶Ô±ÈÓëÊµÀı

ÂÔ£¬¼û¿Î¼ş

## ÖØĞ´Òş²ØÓëÖØÔØ

ÖØÔØOverload-->¾²Ì¬¶àÌ¬£¬²ÎÊı±ØĞë²»Í¬£¬×÷ÓÃÓòÏàÍ¬  
ÖØĞ´Òş²ØRedefining-->²ÎÊı¿ÉÒÔ²»Í¬

### ÖØĞ´Òş²Ø

ÆÁ±Î»ùÀàÖĞ¸Ã³ÉÔ±º¯ÊıµÄÈÎÒ»ÖØÔØº¯Êı

¿ÉÒÔÍ¨¹ı`using ClassName::MemberName;`ÔÚÅÉÉúÀàÖĞ»Ö¸´Ö¸¶¨µÄ»ùÀà³ÉÔ±º¯Êı

Example ÖØĞ´Òş²Ø

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
    void f(int i) {}    //ÖØĞ´Òş²Ø
};
int main(){
    Derive d;
    d.f(10);
    d.f(4.9); // ¡ª¡ª> d.f(4);
    // d.f();       // compiling error
    // d.f(T());    // compiling error
    return 0;
}
```
Example »Ö¸´»ùÀà³ÉÔ±

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
    void f(int i) {}    //ÖØĞ´Òş²Ø
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

### using ¹Ø¼ü×Ö

- ¼Ì³Ğ»ùÀà¹¹Ôìº¯Êı
- »Ö¸´±»ÆÁ±ÎµÄ»ùÀà³ÉÔ±º¯Êı
- Ö¸Ê¾ÃüÃû¿Õ¼ä `using namespace std;`
- ½«ÁíÒ»¸öÃüÃû¿Õ¼äµÄ³ÉÔ±ÒıÈëµ±Ç°ÃüÃû¿Õ¼ä `using std::cout; cout<<endl;`
- ¶¨ÒåÀàĞÍ±ğÃû`using a = int;` 

## ¶àÖØ¼Ì³Ğ

ÅÉÉúÀàÍ¬Ê±¼Ì³Ğ¶à¸ö»ùÀà
```cpp
class File{};
class InputFile: public File{};
class OutputFile: public File{};
class IOFile: public InputFile, public OutputFile{};
```
### ´æÔÚµÄÎÊÌâ

- Êı¾İ´æ´¢  
  ¼Ì³ĞµÄ¶à¸ö»ùÀàÈôÊÇÍ¬Ò»¸öÀàµÄ¼Ì³Ğ£¬ÔòÀ´×Ô¸Ã»ùÀàµÄÊı¾İ³ÉÔ±»áÓĞ¶à¸ö¸±±¾£¬¿ÉÄÜ´øÀ´Êı¾İÈßÓà
- ¶şÒåĞÔ  
  Í¬Ãû³ÉÔ±ÎÊÌâ--->±àÒë´íÎó



# Ğéº¯Êı

## Abstract

- ÏòÉÏÀàĞÍ×ª»»
- ¶ÔÏóÇĞÆ¬
- º¯Êıµ÷ÓÃÀ¦°ó
- Ğéº¯ÊıºÍĞéº¯Êı±í
- Ğéº¯ÊıºÍ¹¹Ôìº¯Êı¡¢Îö¹¹º¯Êı
- ÖØĞ´¸²¸Ç¡¢overloadºÍfinal

## ÏòÉÏÀàĞÍ×ª»»

ÅÉÉúÀà ¶ÔÏó/ÒıÓÃ/Ö¸Õë  ¡ª¡ª¡ª> »ùÀà ¶ÔÏó/ÒıÓÃ/Ö¸Õë

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

## ¶ÔÏóÇĞÆ¬

When a Derived ***obj*** is cast into a Base obj, the non-base part is sliced off
and the data will be ommited.

### Example ÅÉÉúÀàĞÂÊı¾İ¶ªÊ§

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
    getSize(g);         // Pet size: 4  // ¶ÔÏóÇĞÆ¬£¨´«²Î£©
    p = g;        
    cout << "Pet size:" << sizeof(p) << endl; // Pet size: 4 // ¶ÔÏóÇĞÆ¬£¨¸³Öµ£©
    return 0;
}
```
### Example ÅÉÉúÀàĞÂ·½·¨¶ªÊ§

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

### Ö¸Õë/ÒıÓÃ µÄÏòÉÏ×ª»»

µ±ÅÉÉúÀàµÄÖ¸Õë£¨ÒıÓÃ£©±»×ª»»Îª»ùÀàÖ¸Õë£¨ÒıÓÃ£©Ê±£¬²»»á´´½¨ĞÂµÄ¶ÔÏó£¬µ«Ö»±£Áô»ùÀàµÄ½Ó¿Ú¡£

#### Example ÒıÓÃµÄÏòÉÏÀàĞÍ×ª»»

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
  Pet& p = g;               /// ÒıÓÃÏòÉÏ×ª»»
  cout << p.i << endl;                  // 2
  p.i = 1;                  /// ĞŞ¸Ä»ùÀà´æÔÚµÄÊı¾İ
  cout << p.i << endl;                  // 1
  cout << g.i << " " << g.j << endl; /// Ó°ÏìÅÉÉúÀà     // 1 3
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

### Ë½ÓĞ¼Ì³Ğ¡°ÕÕ´ËÊµÏÖ¡±

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
    // d1.setData(10);  ///Òş²ØÁË»ùÀàµÄsetDataº¯Êı£¬²»¿É·ÃÎÊ
    // B& b = d1;       ///²»ÔÊĞíË½ÓĞ¼Ì³ĞµÄÏòÉÏ×ª»»
    // b.setData(10);   ///·ñÔò¿ÉÒÔÈÆ¹ıD1£¬µ÷ÓÃ»ùÀàµÄsetDataº¯Êı
}
```
## º¯Êıµ÷ÓÃÀ¦°ó

À¦°ó(binding): º¯ÊıÌåÓëº¯Êıµ÷ÓÃÏàÁªÏµ  
- ÔçÀ¦°ó(early binding): ÔÚ³ÌĞòÔËĞĞÖ®Ç°Íê³É
- ÍíÀ¦°ó(late binding): ¸ù¾İ¶ÔÏóµÄÊµ¼ÊÀàĞÍ£¬·¢ÉúÔÚ³ÌĞòÔËĞĞÊ±£¬ÓÖ³Æ ¶¯Ì¬À¦°ó/ÔËĞĞÊ±À¦°ó
- - Ö»¶Ô**Ğéº¯Êı**Æğ×÷ÓÃ£¬Ê¹ÓÃ**virtual**¹Ø¼ü×ÖÉùÃ÷

## Ğéº¯Êı

¶ÔÓÚ**±»ÅÉÉúÀàÖØĞÂ¶¨ÒåµÄ³ÉÔ±º¯Êı**£¬ÈôËüÔÚ»ùÀàÖĞ±»ÉùÃ÷Îª**Ğéº¯Êı**£¬ÔòÍ¨¹ı**»ùÀàÖ¸Õë»òÒıÓÃ**µ÷ÓÃ¸Ã³ÉÔ±º¯ÊıÊ±£¬±àÒëÆ÷½«¸ù¾İËùÖ¸£¨»òÒıÓÃ£©¶ÔÏóµÄÊµ¼ÊÀàĞÍ¾ö¶¨ÊÇµ÷ÓÃ»ùÀàÖĞµÄº¯Êı£¬»¹ÊÇµ÷ÓÃÅÉÉúÀàÖØĞ´µÄº¯Êı

```cpp
class Base {
public:
    virtual ReturnType FuncName (argument);
};
```

µ±±»**ÖØĞ´¸²¸Ç**Ê±£¬ÎŞÂÛÊÇ·ñÉùÃ÷£¬¸Ã³ÉÔ±º¯Êı¶¼ÈÔÈ»ÊÇĞéº¯Êı

```cpp
class Instrument {
public:
  virtual void play() { cout << "Instrument::play" << endl; }
};

class Wind : public Instrument {
public:
  void play() { cout << "Wind::play" << endl; }
     /// ÖØĞ´¸²¸Ç(ÉÔºó£ºÖØĞ´Òş²ØºÍÖØĞ´¸²¸ÇµÄÇø±ğ£©
};

void tune(Instrument& ins) {
  ins.play(); /// ÓÉÓÚ Instrument::play ÊÇĞéº¯Êı£¬±àÒëÊ±²»ÔÙÖ±½Ó°ó¶¨£¬ÔËĞĞÊ±¸ù¾İ ins µÄÊµ¼ÊÀàĞÍµ÷ÓÃ¡£
}

int main() {
  Wind flute;
  tune(flute); /// ÏòÉÏÀàĞÍ×ª»»
}

```
Íí°ó¶¨Ö»¶ÔÖ¸ÕëºÍÒıÓÃÓĞĞ§£¨ÀıÂÔ£©

### Ğéº¯ÊıµÄ·µ»ØÖµ

Ò»°ãÀ´ËµÅÉÉúÀàĞéº¯ÊıµÄ·µ»ØÖµÓ¦µ±Óë»ùÀàÏàÍ¬

»òÕßÊÇCovariantµÄ£º£¨ÈçBase& <-> Derive&, Base\* <-> Derive\*£©

- ¶¼ÊÇÖ¸Õë£¨²»ÄÜÊÇ¶à¼¶Ö¸Õë£©¡¢¶¼ÊÇ×óÖµÒıÓÃ»ò¶¼ÊÇÓÒÖµÒıÓÃ£¬ÇÒÔÚDerive::fÉúÃüÊ±£¬Derive::fµÄ·µ»ØÀàĞÍ±ØĞëÊÇDerive»òÆäËûÒÑ¾­ÍêÕû¶¨ÒåµÄÀàĞÍ
- ReturnTypeBaseÖĞ±»ÒıÓÃ»òÖ¸ÏòµÄÀàÊÇReturnYpeDeriveÖĞ±»ÒıÓÃ»òÖ¸ÏòµÄÀàµÄ×æÏÈÀà
- Base::fµÄ·µ»ØÀàĞÍÏà±ÈDerive::fµÄ·µ»ØÀàĞÍÍ¬µÈ»ò¸ü¼Ócv-qualified

### Ğéº¯Êı±í

ÓÃÀ´±íÊ¾×ÔÉíÊµ¼ÊÀàĞÍĞÅÏ¢

Ã¿¸ö°üº¬Ğéº¯ÊıµÄÀà¶ÔÏóÖĞ£¬±àÒëÆ÷ÃØÃÜµØ·ÅÒ»¸öÖ¸Õë£¬³ÆÎªĞéº¯ÊıÖ¸Õë(vpointer/VPTR)£¬Ö¸ÏòÕâ¸öÀàµÄVTABLE¡£

µ±Í¨¹ı»ùÀàÖ¸Õë×öĞéº¯Êıµ÷ÓÃÊ±£¬±àÒëÆ÷¾²Ì¬µØ²åÈëÄÜÈ¡µÃÕâ¸öVPTR²¢ÔÚVTABLE±íÖĞ²éÕÒº¯ÊıµØÖ·µÄ´úÂë£¬ÕâÑù¾ÍÄÜµ÷ÓÃÕıÈ·µÄº¯Êı²¢ÒıÆğÍíÀ¦°óµÄ·¢Éú¡£
- ±àÒëÆÚ¼ä£º½¨Á¢Ğéº¯Êı±íVTABLE£¬¼ÇÂ¼Ã¿¸öÀà»ò¸ÃÀàµÄ»ùÀàÖĞËùÓĞÒÑÉùÃ÷µÄĞéº¯ÊıÈë¿ÚµØÖ·¡£
- ÔËĞĞÆÚ¼ä£º½¨Á¢Ğéº¯ÊıÖ¸ÕëVPTR£¬ÔÚ¹¹Ôìº¯ÊıÖĞ·¢Éú£¬Ö¸ÏòÏàÓ¦µÄVTABLE¡£

![avatar](pics/virtual_table_example.png)

ÔÚ°üº¬ÁËĞéº¯ÊıµÄÀàµÄ¶ÔÏóÖĞ£¬¶ÔÏóµÄ´óĞ¡°üº¬ÁËÖ¸ÏòĞéº¯Êı±íµÄÖ¸ÕëµÄ´óĞ¡£¨Ò»¸övoidÖ¸ÕëµÄ´óĞ¡£©

### Ğéº¯ÊıºÍ¹¹Ôìº¯Êı¡¢Îö¹¹º¯Êı

#### ¹¹Ôìº¯Êı

ÉèÖÃVPTRµÄ¹¤×÷ÓÉ¹¹Ôìº¯ÊıÍê³É£¬±àÒëÆ÷**ÃØÃÜµØ**ÔÚ¹¹Ôìº¯Êı¿ªÍ·²åÈë³õÊ¼»¯´úÂë

¹¹Ôìº¯Êı**²»ÄÜÒ²²»±Ø**ÊÇĞéº¯Êı

Example
```cpp
class Base {
public:
  virtual void foo(){cout<<"Base::foo"<<endl;}
  Base(){foo();} ///ÔÚ¹¹Ôìº¯ÊıÖĞµ÷ÓÃĞéº¯Êıfoo  
  void bar(){foo();};///ÔÚÆÕÍ¨º¯ÊıÖĞµ÷ÓÃĞéº¯Êıfoo
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
Base::foo   //¹¹Ôìº¯Êıµ÷ÓÃµÄÊÇfooµÄ±¾µØ°æ±¾  
Derived::foo()  //ÔÚÆÕÍ¨º¯ÊıÖĞµ÷ÓÃ
Derived::foo()  //Ö±½Óµ÷ÓÃ

##### Explanation
Ğéº¯Êı»úÖÆÔÚ¹¹Ôìº¯ÊıÖĞ²»¹¤×÷  

Ô­Òò£º»ùÀàµÄ¹¹Ôìº¯Êı±ÈÅÉÉúÀàÏÈÖ´ĞĞ£¬µ÷ÓÃ»ùÀà¹¹Ôìº¯ÊıÊ±ÅÉÉúÀàÖĞµÄÊı¾İ³ÉÔ±»¹Ã»ÓĞ³õÊ¼»¯£¨ÉÏÀıÖĞi£©¡£Èç¹ûÔÊĞíµ÷ÓÃÊµ¼Ê¶ÔÏóµÄĞéº¯Êı£¬Ôò¿ÉÄÜ»áÓÃµ½Î´³õÊ¼»¯µÄÅÉÉúÀà³ÉÔ±¡£

³õÊ¼»¯Ë³Ğò£º£¨*Óë¹¹Ôìº¯Êı³õÊ¼»¯ÁĞ±íË³ĞòÎŞ¹Ø!*)
- »ùÀà³õÊ¼»¯
- ¶ÔÏó³ÉÔ±³õÊ¼»¯
- ¹¹Ôìº¯ÊıÌå

#### Îö¹¹º¯Êı

Îö¹¹º¯ÊıÄÜÊÇĞéµÄ£¬ÇÒ³£³£ÊÇĞéµÄ¡£ĞéÎö¹¹º¯ÊıÈÔĞè¶¨Òåº¯ÊıÌå¡£

ĞéÎö¹¹º¯ÊıµÄÓÃÍ¾£ºµ±É¾³ı»ùÀà¶ÔÏóÖ¸ÕëÊ±£¬±àÒëÆ÷½«¸ù¾İÖ¸ÕëËùÖ¸¶ÔÏóµÄÊµ¼ÊÀàĞÍ£¬µ÷ÓÃÏàÓ¦µÄÎö¹¹º¯Êı¡£

Èô»ùÀàÎö¹¹²»ÊÇĞéº¯Êı£¬ÔòÉ¾³ı»ùÀàÖ¸ÕëËùÖ¸ÅÉÉúÀà¶ÔÏóÊ±£¬±àÒëÆ÷½ö×Ô¶¯µ÷ÓÃ»ùÀàµÄÎö¹¹º¯Êı£¬¶ø²»»á¿¼ÂÇÊµ¼Ê¶ÔÏóÊÇ²»ÊÇ»ùÀàµÄ¶ÔÏó¡£Õâ¿ÉÄÜ»áµ¼ÖÂÄÚ´æĞ¹Â©¡£

ÔÚÎö¹¹º¯ÊıÖĞµ÷ÓÃÒ»¸öĞéº¯Êı£¬±»µ÷ÓÃµÄÖ»ÊÇÕâ¸öº¯ÊıµÄ±¾µØ°æ±¾£¬¼´Ğé»úÖÆÔÚÎö¹¹º¯ÊıÖĞ²»¹¤×÷¡£**£¨ÎªÁË±ÜÃâµ÷ÓÃÒ»¸öÒÑ¾­±»É¾³ıµÄ¶ÔÏóµÄº¯Êı£¬£¨»ØÒäÎö¹¹µÄË³Ğò£©£©**

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
  delete bp; /// Ö»µ÷ÓÃÁË»ùÀàµÄĞéÎö¹¹º¯Êı
  Base2* b2p = new Derived2;
  delete b2p; /// ÅÉÉúÀàĞéÎö¹¹º¯Êıµ÷ÓÃÍêºóµ÷ÓÃ»ùÀàµÄĞéÎö¹¹º¯Êı
}
```

>Output:  
>~Base()         //Ö»µ÷ÓÃÁË»ùÀàµÄÎö¹¹º¯Êı  
>
>~Dervied2()     //ÅÉÉúÀàĞéÎö¹¹º¯Êıµ÷ÓÃÍêºó  
>~Base2()        //ÔÙµ÷ÓÃ»ùÀàµÄĞé¹¹º¯Êı         

**ÖØÒªÔ­Ôò**:**×ÜÊÇ½«»ùÀàµÄÎö¹¹º¯ÊıÉèÖÃÎªĞéÎö¹¹º¯Êı**

## ÖØÔØ¡¢ÖØĞ´¸²¸ÇÓëÖØĞ´Òş²Ø

### ÖØÔØ overload

º¯ÊıÃû±ØĞëÏàÍ¬£¬ º¯Êı²ÎÊı±ØĞë²»Í¬£¬ ×÷ÓÃÓò**ÏàÍ¬**

### ÖØĞ´¸²¸Ç override

ÅÉÉúÀàÖØĞÂ¶¨Òå»ùÀàÖĞµÄ**Ğéº¯Êı**£¬º¯ÊıÃû**±ØĞëÏàÍ¬**£¬º¯Êı²ÎÊı**±ØĞëÏàÍ¬**£¬·µ»ØÖµÒ»°ãÏàÍ¬

ÅÉÉúÀàµÄĞéº¯Êı±íÖĞÔ­»ùÀàµÄĞéº¯ÊıÖ¸Õë»á±»ÅÉÉúÀàÖĞÖØĞÂ¶¨ÒåµÄĞéº¯ÊıÖ¸Õë¸²¸Çµô

### ÖØĞ´Òş²Ø redefining

ÅÉÉúÀàÖØĞÂ¶¨Òå»ùÀàÖĞµÄº¯Êı£¬º¯ÊıÃûÏàÍ¬£¬µ«ÊÇ **²ÎÊı²»Í¬** *»ò* **»ùÀàµÄº¯Êı²»ÊÇĞéº¯Êı**¡£

Ğéº¯Êı±í**²»»á·¢Éú¸²¸Ç**

---

||ÖØÔØoverload|ÖØĞ´Òş²Øredefining|ÖØĞ´¸²¸Çoverride|
|----|----|----|----|
|×÷ÓÃÓò|ÏàÍ¬£¨Í¬Ò»¸öÀàÖĞ£©|²»Í¬£¨ÅÉÉúÀàºÍ»ùÀà£©|²»Í¬£¨ÅÉÉúÀàºÍ»ùÀà£©|
|º¯ÊıÃû|ÏàÍ¬|ÏàÍ¬|ÏàÍ¬|
|º¯Êı²ÎÊı|²»Í¬|ÏàÍ¬/²»Í¬|ÏàÍ¬|
|ÆäËûÒªÇó||Èç¹ûº¯Êı²ÎÊıÏàÍ¬£¬Ôò»ùÀàº¯Êı²»ÄÜÎªĞéº¯Êı|»ùÀàº¯ÊıÎªĞéº¯Êı|

---

### Example
```cpp
class Base{
public:    
  	virtual void foo(){cout<<"Base::foo()"<<endl;}
  	virtual void foo(int ){cout<<"Base::foo(int )"<<endl;} ///ÖØÔØ 
  	void bar(){};
};
class Derived1 : public Base {
public:
    void foo(int ) {cout<<"Derived1::foo(int )"<<endl;} 
    /// ÊÇÖØĞ´¸²¸Ç
};
class Derived2 : public Base {
public:
    void foo(float ) {cout<<"Derived2::foo(float )"<<endl;}
    /// Îó°Ñ²ÎÊıĞ´´íÁË£¬²»ÊÇÖØĞ´¸²¸Ç£¬ÊÇÖØĞ´Òş²Ø
};
int main() {    
    Derived1 d1;
    Derived2 d2;
    Base* p1 = &d1;
  	Base* p2 = &d2;
  	//d1.foo(); 	///ÓÉÓÚÅÉÉúÀà¶¼¶¨ÒåÁË´ø²ÎÊıµÄfoo£¬»ùÀàfoo()¶ÔÊµÀı²»¿É¼û
  	//d2.foo();
  	p1->foo();  	///µ«ÊÇĞéº¯Êı±íÖĞÓĞ¼Ì³Ğ×Ô»ùÀàµÄfoo()Ğéº¯Êı
  	p2->foo();
  	d1.foo(3); 		///ÖØĞ´¸²¸Ç
  	d2.foo(3.0);   	///µ÷ÓÃµÄÊÇÅÉÉúÀàfoo(float )
	p1->foo(3);  	///ÖØĞ´¸²¸Ç£¬Ğéº¯Êı±íÖĞÊÇÅÉÉúÀàµÄ foo(int )    
	p2->foo(3.0);   ///ÖØĞ´Òş²Ø£¬Ğéº¯Êı±íÖĞÊÇ¼Ì³Ğ×Ô»ùÀà foo(int )
}

```

>Output:  
Base::foo()  
Base::foo()  
Derived1::foo(int )  
Derived2::foo(float )  
Derived1::foo(int )  
Base::foo(int )

## override ºÍ final ¹Ø¼ü×Ö

### override

ÀûÓÃ **override** ¹Ø¼ü×ÖÃ÷È·¸æËß±àÒëÆ÷£º¡°Ò»¸öº¯ÊıÊÇ¶Ô»ùÀàÖĞÒ»¸ö**Ğéº¯Êı**µÄÖØĞ´¸²¸Ç¡±£¬±àÒëÆ÷½«¶Ô´Ë½øĞĞ¼ì²é£¬Ö»ÓĞÌõ¼şÂú×ãÊ±²ÅÄÜÍ¨¹ı±àÒë

### final

ÔÚĞéº¯ÊıµÄÉùÃ÷»ò¶¨ÒåÖĞ£º
ÀûÓÃ **final** ¹Ø¼ü×ÖÈ·±£º¯ÊıÎªĞéÇÒ²»¿É±»ÅÉÉúÀàÖØĞ´

ÔÚÀà¶¨ÒåÖĞ£º
**final** Ö¸¶¨´ËÀà²»¿É±»¼Ì³Ğ

--- 
µ±ĞŞÊÎº¯ÊıÊ±£¬overrideºÍfinal¶¼Ö»ÄÜĞŞÊÎ**Ğéº¯Êı**

## OOPºËĞÄË¼Ïë

- Êı¾İ³éÏó£ºÀàµÄ**½Ó¿Ú**Óë**ÊµÏÖ**·ÖÀë
- ¼Ì³Ğ£º½¨Á¢Ïà¹ØÀàĞÍµÄ**²ã´Î¹ØÏµ**
- ¶¯Ì¬°ó¶¨£º**Í³Ò»Ê¹ÓÃ»ùÀàÖ¸Õë**£¬ÊµÏÖ¶àÌ¬ĞĞÎª
# å¤šæ€ä¸æ¨¡æ¿

## Abstract

- çº¯è™šå‡½æ•°ä¸æŠ½è±¡ç±»
- å‘ä¸‹ç±»å‹è½¬æ¢
- å¤šé‡ç»§æ‰¿çš„è™šå‡½æ•°è¡¨ï¼Œå¤šé‡ç»§æ‰¿çš„åˆ©å¼Š
- å¤šæ€
- å‡½æ•°æ¨¡æ¿ä¸ç±»æ¨¡æ¿

## çº¯è™šå‡½æ•°

è™šå‡½æ•° å¯è¿›ä¸€æ­¥å£°æ˜ä¸º çº¯è™šå‡½æ•°ï¼Œ åŒ…å«çº¯è™šå‡½æ•°çš„ç±»å«åšâ€œæŠ½è±¡ç±»â€

`virtual ReturnType FuncName(Parameters) = 0;`

å¯åœ¨ç±»å¤–å®šä¹‰å‡½æ•°ä½“æä¾›é»˜è®¤å®ç°ï¼Œæ´¾ç”Ÿç±»é€šè¿‡Base::f() è°ƒç”¨

æŠ½è±¡ç±»ä¸å…è®¸å®šä¹‰å¯¹è±¡ï¼Œå®šä¹‰åŸºç±»ä¸ºæŠ½è±¡ç±»çš„ä¸»è¦ç›®çš„æ˜¯ä¸ºæ´¾ç”Ÿç±»è§„å®šå…±æ€§â€œæ¥å£â€

## æŠ½è±¡ç±»

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
  Pet* p = new Dog; /// å‘ä¸Šç±»å‹è½¬æ¢
  p->motion();
  p = new Bird; /// å‘ä¸Šç±»å‹è½¬æ¢
  p->motion();
  //p = new Pet; /// ä¸å…è®¸å®šä¹‰æŠ½è±¡ç±»å¯¹è±¡
  return 0;
}
```
>Output:  
Pet motion:  
dog run  
Pet motion:  
bird fly  

- åŸºç±»çº¯è™šå‡½æ•°è¢«æ´¾ç”Ÿç±»é‡å†™è¦†ç›–ä¹‹å‰ä»æ˜¯çº¯è™šå‡½æ•°ã€‚å› æ­¤å½“ç»§æ‰¿ä¸€ä¸ªæŠ½è±¡ç±»æ—¶ï¼Œå¿…é¡»**å®ç°** **æ‰€æœ‰** çº¯è™šå‡½æ•°ï¼Œå¦åˆ™ç»§æ‰¿å‡ºæ¥çš„ç±»ä»ç„¶æ˜¯æŠ½è±¡ç±»
- çº¯è™šææ„å‡½æ•°é™¤å¤–

### çº¯è™šææ„å‡½æ•°

>å›é¡¾ï¼š  
ææ„å‡½æ•°å¯ä»¥ä¸”å¸¸å¸¸æ˜¯è™šçš„ï¼Œä»éœ€å®šä¹‰å‡½æ•°ä½“ï¼Œç”¨é€”æ˜¯ï¼šå½“åˆ é™¤åŸºç±»å¯¹è±¡æŒ‡é’ˆæ—¶ï¼Œç¼–è¯‘å™¨å°†æ ¹æ®æŒ‡é’ˆæ‰€æŒ‡å¯¹è±¡çš„**å®é™…ç±»å‹**ï¼Œè°ƒç”¨ç›¸åº”çš„ææ„å‡½æ•°

ææ„å‡½æ•°ä¹Ÿå¯ä»¥æ˜¯çº¯è™šæ„å‡½æ•°

- ä»ç„¶éœ€è¦å‡½æ•°ä½“
- ç›®çš„ï¼šä½¿åŸºç±»æˆä¸ºæŠ½è±¡ç±»ï¼Œä¸èƒ½åˆ›å»ºåŸºç±»çš„å¯¹è±¡ã€‚å¦‚æœæœ‰å…¶ä»–å‡½æ•°æ˜¯çº¯è™šå‡½æ•°ï¼Œåˆ™ææ„å‡½æ•°ä¸å¿…æ˜¯çº¯è™šçš„ã€‚

*// Comment: æˆ‘æƒ³çº¯è™šå‡½æ•°/æŠ½è±¡ç±»çš„ç›®çš„åœ¨äº**å¼ºè¿«å¯¹æ´¾ç”Ÿç±»è¿›è¡Œå„è‡ªçš„å®ç°**ï¼Œè€Œä¸ä¾èµ–åŸºç±»ï¼ˆæŠ½è±¡ï¼‰çš„å®ç°*

**å¯¹äºçº¯è™šææ„å‡½æ•°è€Œè¨€**ï¼Œå³ä¾¿æ´¾ç”Ÿç±»ä¸­ä¸æ˜¾å¼å®ç°ï¼Œ**ç¼–è¯‘å™¨ä¹Ÿä¼šè‡ªåŠ¨åˆæˆé»˜è®¤ææ„å‡½æ•°**ã€‚å› æ­¤å³ä¾¿æ´¾ç”Ÿç±»ä¸è¦†ç›–çº¯è™šææ„å‡½æ•°ï¼Œå®ƒä¹Ÿå¯ä»¥ä¸æ˜¯æŠ½è±¡ç±»ï¼Œå¯ä»¥å®šä¹‰æ´¾ç”Ÿç±»å¯¹è±¡ã€‚


## å‘ä¸‹ç±»å‹è½¬æ¢

åŸºç±»æŒ‡é’ˆ/å¼•ç”¨  --->  æ´¾ç”Ÿç±»æŒ‡é’ˆ/å¼•ç”¨

### Why å‘ä¸‹ç±»å‹è½¬æ¢ï¼Ÿ

- å‘ä¸Šè½¬æ¢ï¼š**ä¿ç•™å…±æ€§**ï¼›å‘ä¸‹è½¬æ¢ï¼š**è¡¨ç°ç‰¹æ€§**

- æ¯”å¦‚å¯ä»¥ä½¿ç”¨åŸºç±»æŒ‡é’ˆæ•°ç»„å¯¹å„ç§æ´¾ç”Ÿç±»å¯¹è±¡è¿›è¡Œç®¡ç†ï¼Œå½“å…·ä½“å¤„ç†æ—¶å¯ä»¥å°†å…¶è½¬æ¢ä¸ºå®é™…çš„æ´¾ç”Ÿç±»æŒ‡é’ˆï¼Œè¿›è€Œè°ƒç”¨æ´¾ç”Ÿç±»ä¸“æœ‰çš„æ¥å£

### å¦‚ä½•ä¿è¯è½¬æ¢çš„æ­£ç¡®æ€§ï¼Ÿ

å€ŸåŠ©è™šå‡½æ•°è¡¨è¿›è¡Œ**åŠ¨æ€ç±»å‹æ£€æŸ¥**

### dynamic_cast å®‰å…¨ç±»å‹çš„å‘ä¸‹æ˜¾å¼ç±»å‹è½¬æ¢

ä½¿ç”¨dynamic_castçš„å¯¹è±¡**å¿…é¡»æœ‰è™šå‡½æ•°**

#### Usage
```cpp
// T1* obj_p;
// T1& obj_r;
T2* pObj = dynamic_cast<T2*>(obj_p);
// å¤±è´¥æ—¶è¿”å›nullptr
T2& refObj = dynamic_cast<T2&>(obj_r);
// å¤±è´¥æ—¶æŠ›å‡ºbad_castå¼‚å¸¸
```

T1å¿…é¡»æ˜¯å¤šæ€ç±»å‹ï¼ˆå£°æ˜æˆ–ç»§æ‰¿äº†è‡³å°‘ä¸€ä¸ªè™šå‡½æ•°çš„ç±»ï¼‰ï¼ŒT2ä¸å¿…ã€‚

è‹¥ä¸¤è€…æ²¡æœ‰ç»§æ‰¿å…³ç³»ï¼Œä¹Ÿèƒ½é€šè¿‡ç¼–è¯‘ï¼Œä½†è¿è¡Œæ—¶ä¼šè½¬æ¢å¤±è´¥ã€‚

### static_cast ç”¨äºé¿å… ç¡®è®¤ç±»å‹ å¸¦æ¥çš„å¼€é”€

ç¼–è¯‘æ—¶é™æ€æµè§ˆç±»å±‚æ¬¡ï¼Œåªæ£€æŸ¥ç»§æ‰¿å…³ç³»ã€‚æ²¡æœ‰ç»§æ‰¿å…³ç³»çš„ç±»ä¹‹é—´å¿…é¡»æœ‰è½¬æ¢é€”å¾„ï¼ˆç•¥ï¼‰ã€‚è¿è¡Œæ—¶æ— æ³•ç¡®è®¤æ˜¯å¦æ­£ç¡®è½¬æ¢

```cpp
T2* pObj = static_cast<T2*>(obj_p);
T2& refObj = static_cast<T2&>(obj_P);
// ä¸å®‰å…¨ï¼
```
### dynamicä¸staticæ¯”è¾ƒ
ç›¸åŒï¼šéƒ½å¯ä»¥å®Œæˆå‘ä¸‹ç±»å‹è½¬æ¢  
ä¸åŒï¼š
- static_castæ˜¯åœ¨**ç¼–è¯‘æ—¶é™æ€**æ‰§è¡Œå‘ä¸‹ç±»å‹è½¬æ¢
- dynamic_castä¼šåœ¨**è¿è¡Œæ—¶**æ£€æŸ¥è¢«è½¬æ¢çš„å¯¹è±¡**æ˜¯å¦ç¡®å®æ˜¯æ­£ç¡®çš„æ´¾ç”Ÿç±»**ã€‚é¢å¤–çš„æ£€æŸ¥éœ€è¦RTTIï¼ˆRun-Time Type Informationï¼‰ï¼Œå› æ­¤è¦æ¯”static_castæ…¢ä¸€äº›ï¼Œä½†æ˜¯æ›´å®‰å…¨ã€‚

**ä¸€èˆ¬ä½¿ç”¨dynamic_castè¿›è¡Œå‘ä¸‹ç±»å‹è½¬æ¢**

---

### é‡è¦åŸåˆ™ï¼ˆæ¸…æ¥šæŒ‡é’ˆæ‰€æŒ‡å‘çš„çœŸæ­£å¯¹è±¡ï¼‰ï¼š
1. æŒ‡é’ˆæˆ–å¼•ç”¨çš„å‘ä¸Šè½¬æ¢æ€»æ˜¯å®‰å…¨çš„
2. å‘ä¸‹è½¬æ¢æ—¶ç”¨dynamic_castï¼Œå®‰å…¨æ£€æŸ¥
3. é¿å…**å¯¹è±¡ä¹‹é—´**çš„è½¬æ¢

### å‘ä¸Šå‘ä¸‹ç±»å‹è½¬æ¢ä¸è™šå‡½æ•°è¡¨

å¯¹äºåŸºç±»ä¸­æœ‰è™šå‡½æ•°çš„æƒ…å†µï¼š

- å‘ä¸Šç±»å‹è½¬æ¢  
  è½¬æ¢ä¸ºåŸºç±»**æŒ‡é’ˆæˆ–å¼•ç”¨**ï¼Œåˆ™å¯¹åº”è™šå‡½æ•°è¡¨ä»ç„¶ä¸ºæ´¾ç”Ÿç±»çš„è™šå‡½æ•°è¡¨ï¼ˆæ™šç»‘å®šï¼‰  
  è½¬æ¢ä¸ºåŸºç±»**å¯¹è±¡**ï¼Œåˆ™å¯¹åº”è™šå‡½æ•°è¡¨æ˜¯åŸºç±»çš„è™šå‡½æ•°è¡¨ï¼ˆæ—©ç»‘å®šï¼‰  
- å‘ä¸‹ç±»å‹è½¬æ¢  
  dynamic_casté€šè¿‡è™šå‡½æ•°è¡¨æ¥åˆ¤æ–­æ˜¯å¦èƒ½è¿›è¡Œå‘ä¸‹ç±»å‹è½¬æ¢

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
	auto d = dynamic_cast<Dog*>(p);	/// å‘ä¸‹ç±»å‹è½¬æ¢
	auto b = dynamic_cast<Bird*>(p);	/// å‘ä¸‹ç±»å‹è½¬æ¢
	if (d) /// è¿è¡Œæ—¶æ ¹æ®å®é™…ç±»å‹è¡¨ç°ç‰¹æ€§
		d->run();
	else if(b)
		b->fly();
}

int main() {
	Pet* p[2];
	p[0] = new Dog; /// å‘ä¸Šç±»å‹è½¬æ¢
	p[1] = new Bird; /// å‘ä¸Šç±»å‹è½¬æ¢
	for (int i = 0; i < 2; ++i) {
		action(p[i]);
	}
	return 0;
}
```

## å¤šé‡ç»§æ‰¿

### å¤šé‡ç»§æ‰¿çš„è™šå‡½æ•°è¡¨

å¤šé‡ç»§æ‰¿ä¼šæœ‰å¤šä¸ªè™šå‡½æ•°è¡¨ï¼Œå‡ é‡ç»§æ‰¿ï¼Œå°±ä¼šæœ‰å‡ ä¸ªè™šå‡½æ•°è¡¨ã€‚è¿™äº›è¡¨æŒ‰ç…§æ´¾ç”Ÿçš„é¡ºåºä¾æ¬¡æ’åˆ—ã€‚

å¦‚æœå­ç±»æ”¹å†™äº†çˆ¶ç±»çš„è™šå‡½æ•°ï¼Œé‚£ä¹ˆå°±ä¼šç”¨å­ç±»è‡ªå·±çš„è™šå‡½æ•°è¦†ç›–è™šå‡½æ•°è¡¨çš„ç›¸åº”ä½ç½®ï¼Œ**å¦‚æœå­ç±»æœ‰æ–°çš„è™šå‡½æ•°ï¼Œé‚£ä¹ˆå°±æ·»åŠ åˆ°ç¬¬ä¸€ä¸ªè™šå‡½æ•°è¡¨çš„æœ«å°¾ã€‚**

![avatar](pics/multi-inherit_vtable.png)


### åˆ©å¼Š

ç•¥ï¼Œè§å‰è¯¾ä»¶

Best Practice:
- æœ€å¤šç»§æ‰¿ä¸€ä¸ªéæŠ½è±¡ç±»ï¼ˆis-a)
- å¯ä»¥ç»§æ‰¿å¤šä¸ªæŠ½è±¡ç±»ï¼ˆæ¥å£ï¼‰

Why?
- é¿å… å¤šé‡ç»§æ‰¿çš„äºŒä¹‰æ€§
- åˆ©ç”¨ ä¸€ä¸ªå¯¹è±¡å®ç°å¤šä¸ªæ¥å£

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

### è™šæ‹Ÿç»§æ‰¿
è‡ªè¡Œäº†è§£

## å¤šæ€(Polymorphism)

äº§ç”Ÿå¤šæ€æ•ˆæœçš„æ¡ä»¶ï¼š ç»§æ‰¿ && è™šå‡½æ•° && ï¼ˆå¼•ç”¨ || æŒ‡é’ˆï¼‰

å¥½å¤„ï¼š
- é€šè¿‡åŸºç±»å®šå¥½æ¥å£åï¼Œä¸å¿…å¯¹æ¯ä¸€ä¸ªæ´¾ç”Ÿç±»ç‰¹æ®Šå¤„ç†ï¼Œåªéœ€è¦è°ƒç”¨æŠ½è±¡åŸºç±»çš„æ¥å£å³å¯ã€‚å¤§å¤§æé«˜ç¨‹åºçš„**å¯å¤ç”¨æ€§**
- ä¸åŒæ´¾ç”Ÿç±»å¯¹åŒä¸€æ¥å£çš„å®ç°ä¸åŒï¼Œèƒ½è¾¾åˆ°ä¸åŒçš„æ•ˆæœï¼Œæé«˜äº†ç¨‹åº**å¯æ‹“å±•æ€§å’Œå¯ç»´æŠ¤æ€§**

ç¤ºä¾‹è§è¯¾ä»¶

### åº”ç”¨ï¼šTEMPLATE METHODè®¾è®¡æ¨¡å¼

- åœ¨æ¥å£çš„ä¸€ä¸ªæ–¹æ³•ä¸­å®šä¹‰ç®—æ³•çš„éª¨æ¶
- å°†ä¸€äº›æ­¥éª¤çš„å®ç°å»¶è¿Ÿåˆ°å­ç±»ä¸­
- ä½¿å¾—å­ç±»å¯ä»¥åœ¨ä¸æ”¹å˜ç®—æ³•ç»“æ„çš„æƒ…å†µä¸‹ï¼Œé‡æ–°å®šä¹‰ç®—æ³•ä¸­çš„æŸäº›æ­¥éª¤

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

## å‡½æ•°æ¨¡æ¿ä¸ç±»æ¨¡æ¿

æ¨¡æ¿
- å‡½æ•°æ¨¡æ¿
- ç±»æ¨¡æ¿
- æˆå‘˜å‡½æ•°æ¨¡æ¿

### å‡½æ•°æ¨¡æ¿

`template <typename T> ReturnType Func(Args);`

`template <class T> ReturnType Func(Args);`

åœ¨è°ƒç”¨æ—¶ç¼–è¯‘å™¨è‡ªåŠ¨æ¨å¯¼å‡ºå®é™…å‚æ•°çš„ç±»å‹

```cpp
template <typename T>
T sum(T a,T b){return a+b;}

cout << sum(9,2.1);   //ç¼–è¯‘é”™è¯¯ï¼Œå‚æ•°ç±»å‹ä¸ä¸€è‡´ï¼Œæ— æ³•æ¨å¯¼
cout<< sum<int>(9,2.1); //æ‰‹å·¥æŒ‡å®šç±»å‹
```

### ç±»æ¨¡æ¿

```cpp
template <typename T> class A{
  T data;
public:
  void print1(){cout << data << endl;}
  void print2();      // ç±»å¤–å®šä¹‰
};

template<typename T>    // ç±»å¤–å®šä¹‰
void A<T>::print2() {cout << data << endl;}

int main(){
  A<int> a;
  a.print1();
}

```

â€œæ¨¡æ¿å‚æ•°â€
- ç±»å‹å‚æ•°ï¼š typenameæˆ–class
- éç±»å‹å‚æ•°ï¼š æ•´æ•°ï¼Œæšä¸¾ï¼ŒæŒ‡é’ˆï¼ˆæŒ‡å‘å¯¹è±¡æˆ–å‡½æ•°ï¼‰ï¼Œå¼•ç”¨ï¼ˆå¼•ç”¨å¯¹è±¡æˆ–å‡½æ•°ï¼‰ã€‚
  ```cpp
  template<typename T, unsigned size>
  class array{
    T elems[size];
    ...
  };
  
  array<char, 10> array0;
  ```
### æˆå‘˜å‡½æ•°æ¨¡æ¿

æ™®é€šç±»
```cpp
class normal_class {
public:
  int value;
  template<typename T> void set(T const& v) {
    value = int(v);
  }   /// åœ¨ç±»å†…å®šä¹‰
  template<typename T> T get();
};

template<typename T>    /// åœ¨ç±»å¤–å®šä¹‰
T normal_class::get() {
  return T(value);
}
```
æ¨¡æ¿ç±»
```cpp
template<typename T0> class A{
  T0 value;
public:
  template<typename T1> void set(T1 const& v){
    value = T0(v);
  }     /// ç±»å†…å®šä¹‰
  template<typename T1> T1 get();
};
template<typename T0> template<typename T1>
T1 A<T0>::get(){ return T1(value);}   // ç±»å¤–å®šä¹‰

/*æ³¨æ„ä¸èƒ½å†™æˆ
template<typename T0, typename T1>
T1 A<T0>::get(){ return T1(value);}   // ç±»å¤–å®šä¹‰
*/
```

æ¨¡æ¿ä½¿ç”¨ä¸­é€šå¸¸å¯ä»¥è‡ªåŠ¨æ¨å¯¼ç±»å‹ï¼Œå¿…è¦æ—¶ä¹Ÿå¯ä»¥æŒ‡å®šï¼Œæ–¹æ³•æ˜¯åœ¨è°ƒç”¨çš„ä¸œè¥¿çš„åç§°ååŠ ä¸Š <ç±»å‹å>

### æ¨¡æ¿åŸç†

åœ¨ç¼–è¯‘æœŸè¿›è¡Œå¯¹æ¨¡æ¿çš„å¤„ç†ï¼Œè¿™æ„å‘³ç€æ‰€æœ‰æ¨¡æ¿å‚æ•°å¿…é¡»åœ¨ç¼–è¯‘æœŸç¡®å®šï¼Œä¸èƒ½ä½¿ç”¨å˜é‡

è¿™æ„å‘³ç€

æ¨¡æ¿åº“å¿…é¡»åœ¨å¤´æ–‡ä»¶ä¸­å®ç°ï¼Œä¸å¯ä»¥åˆ†å¼€ç¼–è¯‘

### æ¨¡æ¿ä¸å¤šæ€

æ¨¡æ¿ä¹Ÿæ˜¯å¤šæ€ï¼Œåªä¸è¿‡æ˜¯**é™**å¤šæ€ï¼ˆç¼–è¯‘æ—¶ï¼‰

# OOP¿Î¼şÔ¤Ï°±Ê¼Ç

±¾À´¼ÇÁËL1-L6µÄ±Ê¼ÇµÄ£¬ÅªvscodeÀïµÄgitÊ±ÊÖ»¬°Ñ¶«Î÷È«É¾ÁË£¬ÈÕÁË  
ËùÒÔÖ»ÄÜ´ÓL7¿ªÊ¼ÁË  
