#include <iostream>
using namespace std;

#define INTMAX 2147483647

int n;
int a[1001], s[1001];
int dp[1010][1010];

int dfs(int i, int j)
{
    if (dp[i][j] != INTMAX)
        return dp[i][j];
    if(i == j)
        return dp[i][j] = 0;
    for(int k = i; k < j; ++k )
    {
        dp[i][j] = min(dp[i][j], dfs(i,k) + dfs(k+1,j) + s[j] - s[i-1]);
    }
    return dp[i][j];
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        s[i] = s[i-1] + a[i];
        for(int j = 1; j <= n; ++j)
            dp[i][j] = INTMAX;
    }
    cout << dfs(1,n);
    return 0;
}