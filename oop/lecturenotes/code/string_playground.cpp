#include <string>
#include <iostream>
using namespace std;

int main(){
    string a = "123hehe456";
    string::size_type t;
    cout << stoi(a, &t)<<endl;
    cout << t <<endl;
    return 0;
}