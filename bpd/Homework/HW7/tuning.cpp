#include <iostream>
using namespace std;

int n,blevel, mlevel;
int c[100];

char dp[51][1001];

int main()
{
    cin >> n >> blevel >> mlevel;
    dp[0][blevel] = 1;
    for(int i = 1; i <= n; ++i)
    {
        cin >> c[i];
        for(int j = 0; j <= mlevel; ++j)
        {
            if(j - c[i] >= 0)
                dp[i][j] |= dp[i-1][j-c[i]];
            if (j + c[i] <= mlevel)
                dp[i][j] |= dp[i-1][j+c[i]];
        }
    }
    int ans = -1;
    while(mlevel)
    {
        if(dp[n][mlevel])
        {
            ans = mlevel;
            break;
        }
        mlevel--;
    }
    cout << ans;
    return 0;
}