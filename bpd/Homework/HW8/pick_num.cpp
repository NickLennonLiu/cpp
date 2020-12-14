#include <iostream>
using namespace std;

#define nmax 100010
int num[nmax];
long long dp[nmax];
int n;
long long ans = 0;


int main()
{
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> num[i];
    for(int i = 1; i <= n-1; ++i)
    {
        dp[i] = num[i];
        if(i >= 4)
            dp[i] += (dp[i-2] > dp[i-3]) ? dp[i-2] : dp[i-3];
        else if(i==3)
            dp[i] += dp[1];
        ans = (ans > dp[i]) ? ans : dp[i];
    }
    dp[1] = 0;
    for (int i = 2; i <= n; ++i)
    {
        dp[i] = num[i];
        if (i >= 4)
        {
            dp[i] += (dp[i - 2] > dp[i - 3]) ? dp[i - 2] : dp[i - 3];
        }
        ans = (ans > dp[i]) ? ans : dp[i];
    }
    cout << ans;
    return 0;
}