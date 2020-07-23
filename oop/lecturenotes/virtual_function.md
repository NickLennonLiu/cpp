# 虚函数

## Abstract

- 向上类型转换
- 对象切片
- 函数调用捆绑
- 虚函数和虚函数表
- 虚函数和构造函数、析构函数
- 重写覆盖、overload和final

## 向上类型转换

派生类 对象/引用/指针  ———> 基类 对象/引用/指针

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

## 对象切片

When a Derived ***obj*** is cast into a Base obj, the non-base part is sliced off
and the data will be ommited.

### Example 派生类新数据丢失

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
    getSize(g);         // Pet size: 4  // 对象切片（传参）
    p = g;        
    cout << "Pet size:" << sizeof(p) << endl; // Pet size: 4 // 对象切片（赋值）
    return 0;
}
```
### Example 派生类新方法丢失

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

### 指针/引用 的向上转换

当派生类的指针（引用）被转换为基类指针（引用）时，不会创建新的对象，但只保留基类的接口。

#### Example 引用的向上类型转换

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
  Pet& p = g;               /// 引用向上转换
  cout << p.i << endl;                  // 2
  p.i = 1;                  /// 修改基类存在的数据
  cout << p.i << endl;                  // 1
  cout << g.i << " " << g.j << endl; /// 影响派生类     // 1 3
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

### 私有继承“照此实现”

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
    // d1.setData(10);  ///隐藏了基类的setData函数，不可访问
    // B& b = d1;       ///不允许私有继承的向上转换
    // b.setData(10);   ///否则可以绕过D1，调用基类的setData函数
}
```
## 函数调用捆绑

捆绑(binding): 函数体与函数调用相联系  
- 早捆绑(early binding): 在程序运行之前完成
- 晚捆绑(late binding): 根据对象的实际类型，发生在程序运行时，又称 动态捆绑/运行时捆绑
- - 只对**虚函数**起作用，使用**virtual**关键字声明

## 虚函数

对于**被派生类重新定义的成员函数**，若它在基类中被声明为**虚函数**，则**通过基类指针或引用调用该成员函数**时，编译器将根据所指（或引用）对象的实际类型决定是调用基类中的函数，还是调用派生类重写的函数

```cpp
class Base {
public:
    virtual ReturnType FuncName (argument);
};
```

当被**重写覆盖**时，无论是否声明，该成员函数都仍然是虚函数

```cpp
class Instrument {
public:
  virtual void play() { cout << "Instrument::play" << endl; }
};

class Wind : public Instrument {
public:
  void play() { cout << "Wind::play" << endl; }
     /// 重写覆盖(稍后：重写隐藏和重写覆盖的区别）
};

void tune(Instrument& ins) {
  ins.play(); /// 由于 Instrument::play 是虚函数，编译时不再直接绑定，运行时根据 ins 的实际类型调用。
}

int main() {
  Wind flute;
  tune(flute); /// 向上类型转换
}

```
晚绑定只对指针和引用有效（例略）

### 虚函数的返回值

一般来说派生类虚函数的返回值应当与基类相同

或者是Covariant的，如Base& <-> Derive&, Base\* <-> Derive\*

### 虚函数表

用来表示自身实际类型信息

每个包含虚函数的类对象中，编译器秘密地放一个指针，称为虚函数指针(vpointer/VPTR)，指向这个类的VTABLE。

当通过基类指针做虚函数调用时，编译器静态地插入能取得这个VPTR并在VTABLE表中查找函数地址的代码，这样就能调用正确的函数并引起晚捆绑的发生。
- 编译期间：建立虚函数表VTABLE，记录每个类或该类的基类中所有已声明的虚函数入口地址。
- 运行期间：建立虚函数指针VPTR，在构造函数中发生，指向相应的VTABLE。

![avatar](pics/virtual_table_example.png)

在包含了虚函数的类的对象中，对象的大小包含了指向虚函数表的指针的大小（一个void指针的大小）

### 虚函数和构造函数、析构函数

#### 构造函数

设置VPTR的工作由构造函数完成，编译器**秘密地**在构造函数开头插入初始化代码

构造函数**不能也不必**是虚函数

Example
```cpp
class Base {
public:
  virtual void foo(){cout<<"Base::foo"<<endl;}
  Base(){foo();} ///在构造函数中调用虚函数foo  
  void bar(){foo();};///在普通函数中调用虚函数foo
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
Base::foo   //构造函数调用的是foo的本地版本  
Derived::foo()  //在普通函数中调用
Derived::foo()  //直接调用

##### Explanation
虚函数机制在构造函数中不工作  

原因：基类的构造函数比派生类先执行，调用基类构造函数时派生类中的数据成员还没有初始化（上例中i）。如果允许调用实际对象的虚函数，则可能会用到未初始化的派生类成员。

初始化顺序：（*与构造函数初始化列表顺序无关!*)
- 基类初始化
- 对象成员初始化
- 构造函数体

#### 析构函数

析构函数能是虚的，且常常是虚的。虚析构函数仍需定义函数体。

虚析构函数的用途：当删除基类对象指针时，编译器将根据指针所指对象的实际类型，调用相应的析构函数。

若基类析构不是虚函数，则删除基类指针所指派生类对象时，编译器仅自动调用基类的析构函数，而不会考虑实际对象是不是基类的对象。这可能会导致内存泄漏。

在析构函数中调用一个虚函数，被调用的只是这个函数的本地版本，即虚机制在析构函数中不工作。**（为了避免调用一个已经被删除的对象的函数，（回忆析构的顺序））**

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
  delete bp; /// 只调用了基类的虚析构函数
  Base2* b2p = new Derived2;
  delete b2p; /// 派生类虚析构函数调用完后调用基类的虚析构函数
}
```

>Output:  
>~Base()         //只调用了基类的析构函数  
>
>~Dervied2()     //派生类虚析构函数调用完后  
>~Base2()        //再调用基类的虚构函数         

**重要原则**:**总是将基类的析构函数设置为虚析构函数**

