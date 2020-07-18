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

To be continued...