#include <iostream>
using namespace std;

/*TODO: 没有避免重复计算*/ 

int arr[1000];
int n, k;
int result[1000][1000], s[1000][1000];

int eval_arr(int* s,int* e){
    int result = 0;
    while(s!=e){
        result = result*10 + *s;
        s++;
    }
    return result;
}

int P(int left, int right, int k){
    if(!k) return eval_arr(arr+left,arr+(right+1));
    /*else if(left==right){
        return arr[left];
    }*/
    else {
        int max = 0;
        for(int i = left;i < right-k+1;++i)
        {
            int q = eval_arr(arr+left,arr+i+1)*P(i+1,right,k-1);
            if(max < q){
                max = q;
                s[left][right] = i;
            }
        }
        return max;
    }
}

int main() {
    cin >> n >> k;
    for(int i = 0;i<n;i++) cin >> arr[i];
    cout << P(0,n-1,k) << endl;
    return 0;
}