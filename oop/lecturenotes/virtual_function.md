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






