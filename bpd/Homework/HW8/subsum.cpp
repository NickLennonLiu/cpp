#include <iostream>
using namespace std;

#define nmax 100000

long long sum[nmax];
int n;
int temp;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {   
        cin >> temp;
        sum[i] = sum[i-1] + temp;
    }
    int min = 0;
    long long ans = 0;
    for(int i = 1; i <= n; ++i)
    {
        long long tempans = sum[i] - min;
        ans = (ans > tempans) ? ans : tempans;
        min = (min < sum[i]) ? min : sum[i];
    }
    cout << ans;
    return 0;
}