#include <iostream>

int fact(int i){
    if(!i) return 1;
    else return i*fact(i-1);
}

int main(){
    return fact(5);
}