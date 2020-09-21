#include <iostream>
#include <algorithm>
using namespace std;

int n, w, cnt;
int nug[100002];

int main()
{
    cin >> n;
    for(int i = 0; i < n; i ++){
        cin >> w;
        nug[w] += 1;
    } 
    for(int i = 0; i < 100002; i++){
        nug[i + 1] += nug[i] / 3;
        cnt += nug[i] % 3;
    }
    cout << cnt;
    return 0;
}