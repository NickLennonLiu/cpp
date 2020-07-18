# 组合与继承 Composition and Inheritance

## Abstract

1. 组合
2. 继承
3. 成员访问权限
4. 重写隐藏与重载
5. 多重继承

## 组合

***整体-部分*** 关系为 ***组合*** 或 *has-a* 关系

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

对象拷贝与赋值运算： 略

## 继承

"is-a"、"一般-特殊" 结构

base class 基类/父类  
--> derived class 派生类/子类/拓展类

### Way of Inheritance  
```cpp
class <Derived_Class_Name> : [private] <Base_Name> { .. }; // Default way of succession:private
class <Derived_Class_Name> : public <Base_Name> { .. };
class <Derived_Class_Name> : protected <Base_Name> { .. }; // Rarely used
```

### What **cannot** be Inherited
- 构造函数
- 析构函数
- 赋值运算符    Includes the parameter which is of its class
- 友元函数      Not member of the class  

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

### 派生类对象的构造与析构

#### 构造：需要调用基类构造函数
- 没有显式调用：自动生成对基类的默认构造函数的调用
- 在构造函数的初始化成员列表中进行显式调用
- - 调用基类中不带参数的默认构造函数
- - 调用合适的带参数的其他构造函数

```cpp
class Base{
    int data;
public:
    Base() : data(0) {cout << "Base::Base("<<data<<")\n";}
    Base(int i): data(i) {cout << "Base::Base("<<data<<")\n";}
};
class Derive : public Base{
public:
    // 注意：以下代码每一行为不同的构造函数，在同一程序中只出现其中一个
    // 1.无显式调用基类构造函数，调用基类默认构造函数
    Derive() { cout << "Derive::Derive()"<< endl;}  
    // 2.显式调用基类构造函数
    Derive(int i) : Base(i) { cout << "Derive::Derive()"<< endl;}
    // 3.继承基类构造函数
    using Base::Base; ///相当于 Derive(int i):Base(i){}
    // 当基类存在多个构造函数时,
    // 使用using会给派生类自动构造多个相应的构造函数
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

#### 注意
- 如果基类的某个构造函数被声明为私有，则派生类中不能声明继承该构造函数
- 如果派生类使用了继承构造函数，编译器就不会再为派生类生成默认构造函数

### How to choose way of inheritance

#### public Inherit
基类中公有成员在派生类中保持公有，原接口可沿用  
is-a: 基类对象能使用的地方，派生类对象也能使用  
#### private Inherit
is-implementing-in-terms-of(照此实现)：用基类接口实现派生类功能，移除is-a关系  
通常不使用，**用组合替代**，可用于隐藏/公开基类的部分接口。  
公开方法： 在 public 部分 使用 using 关键字  
// 基类公有成员（接口） 变 派生类私有成员（功能）

## 成员访问权限

|继承表||继承方法|||
|----|----|----|----|----|
|||public|private|protected|
|基类↓|public|OK(pub/yes)|OK(prv/no)|OK(pro/no)|
|成员↓|private|NO(prv/no)|NO(prv/no)|NO(prv/no)|
|类型|protected|OK(pro/no)|OK(prv/no)|OK(pro/no)|

OK/NO : **派生类成员函数**能否访问基类成员  
pub/pro/prv/ : 基类成员在派生类中的成员类型  
yes/no : **派生类对象**能否访问基类成员(//即能否调用函数或能读写数据)

#### Some Notes  
- 基类中私有成员无论如何都不能被其他类（对象/成员函数）访问。（私有的无论什么时候都是私有的）  
- 派生类**对象**不可访问基类中保护成员，但**成员函数**可以

## 组合与继承 对比与实例

略，见课件

## 重写隐藏与重载

To be continued...