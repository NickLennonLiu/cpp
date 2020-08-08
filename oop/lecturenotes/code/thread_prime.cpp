#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
using namespace std;
thread* threads[4];

int thread_total[4];

int total = 0, mi, mx;

bool check_num(int num){
    if(num==1) return 0;
    for(int i=sqrt(num);i>1;i--){
        if(!(num%i)){
            return false;
        }
    }
    return true;
}

void check(int l, int r, int num){
    thread_total[num] = 0;
    for(int i = l; i<r; i++){
        if(check_num(i))
            thread_total[num]++;
    }
}

int main(){
    mi = 1;
    for(int i = 0;i < 4; i++){
        mx = mi + 5000000 / 4;
        if (mx > 5000000) mx = 5000000;
        threads[i] = new thread(check, mi, mx, i);
        mi = mx;
    }
    for(int i = 0;i < 4; i++) 
        threads[i]->join();
    for(int i = 0;i < 4; i++) {
        total += thread_total[i];
        delete threads[i];
    }
    cout << total << endl;
    return 0;
}