#include <iostream>
#include <cmath>
using namespace std;
int main(){
    int N;
    cin >> N;
    int a = (int)(log2(N)+1);
    cout << a<< endl;
    for(int i = 0;i<a;++i){
        int check5 = 0;
        for(int j = 1;j<=N;++j){
            if(j & (1<<i)) {
                cout << j << " ";
                ++check5;
            }
            if(check5==4){
                cout << endl;
                check5 = 0;
            }
        }
        cout << endl;
    }
    return 0;
}