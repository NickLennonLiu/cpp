#include <iostream>
using namespace std;

int num[1001];
int main()
{
    int n, a;
    cin >> n;
    int cnt = 0;
    for(int i = 0; i < n; ++i)
    {
        cin >> a;
        if(!num[a]) ++cnt;
        num[a]++;
    }
    cout << cnt << endl;
    for(int i = 1; i <= 1000; ++i)
    {
        if(num[i])
            cout << i << " ";
    }
    return 0;
}