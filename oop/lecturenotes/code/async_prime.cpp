#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <future>
#include <random>
using namespace std;

int total = 0;

bool check_num(int num){
    if(num==1) return 0;
    for(int i=sqrt(num);i>1;i--){
        if(!(num%i)){
            return false;
        }
    }
    return true;
}

default_random_engine e;

int input() {
    return e();
}

vector<future<bool>> future_lists;
vector<int> num_lists;

int main() {
    while (true) {
        int num = input();
        future_lists.push_back(async(check_num,num));
        num_lists.push_back(num);

        for(int i = future_lists.size() - 1; i >=0 ; i--) {
            future_status status = future_lists[i].wait_for(chrono::milliseconds(100));
            if (status == future_status::ready) {
                if(future_lists[i].get())
                    cout << num_lists[i] << " is a prime number" << endl;
                else
                {
                    cout << num_lists[i] << " is not a prime number" << endl;
                }
                future_lists.erase(future_lists.begin() + i);
                num_lists.erase(num_lists.begin() + i);
            }
        }
    }
    return 0;
}