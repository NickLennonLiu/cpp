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

����**�����������¶���ĳ�Ա����**�������ڻ����б�����Ϊ**�麯��**����**ͨ������ָ������õ��øó�Ա����**ʱ����������������ָ�������ã������ʵ�����;����ǵ��û����еĺ��������ǵ�����������д�ĺ���

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

������Covariant�ģ���Base& <-> Derive&, Base\* <-> Derive\*

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

