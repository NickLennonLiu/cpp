#include <iostream>
using namespace std;

// dp[m][n] : LCS(A[0,m), B[0,n))
int dp[6000][6000];
char A[501001], B[501001];
int a, b, k;

int LCS(char A[], char B[], int a, int b)
{
    for(int i = 0; i < a || i < b; i++)
        dp[i][0] = dp[0][i] = 0;
    for(int i = 1; i <= a; ++i)
    {
        for(int j = 1; j <= b; ++j)
        {
            if(A[i-1] == B[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
        }
    }
    return dp[a][b];
}

int main()
{
    scanf("%d %d %d", &a, &b, &k);
    scanf("%s", A);
    scanf("%s", B);
    int lcs = LCS(A, B, a, b);
    int result = a + b - 2*lcs;
    if(result > k) cout << -1;
    else cout << result;
    return 0;
    
}

