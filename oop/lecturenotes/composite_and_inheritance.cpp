#include <iostream>
using namespace std;

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