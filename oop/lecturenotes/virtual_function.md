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






