#include <iostream>
#include <future>
#include <cmath>
using namespace std;

bool check_num(int num) {
    bool flag = true;
    if(num == 1)
        flag = false;
    else
        for(int i = sqrt(num); i > 1; i-- ){
            if (!(num%i)) {
                flag = false;
                break;
            }
        }
    if (flag) 
        cout << num << " is a prime number" << endl;
    else
        cout << num << " is not a prime number" << endl;
    return flag;
}

int main(){
    // std::future<bool> fut = async(check_num, 194232491);
    // 也可以 auto fut = async(check_num, 194232491);
    // 与可调用对象（如lambda表达式）一起使用
    auto fut = async([](int num) {
        bool flag = true;
        if(num == 1)
            flag = false;
        else
            for(int i = sqrt(num); i > 1; i-- ){
                if (!(num%i)) {
                    flag = false;
                    break;
                }
            }
        if (flag) 
            cout << num << " is a prime number" << endl;
        else
            cout << num << " is not a prime number" << endl;
        return flag;
    }, 194232491);
    cout << "check the number..." << endl;
    return 0;
}
