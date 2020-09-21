#include <iostream>
using namespace std;

// dp[m][n] : LCS(A[0,m), B[0,n))
int pre[501001], cur[501001];
char A[501001], B[501001];
int a, b, k;

// Shortest Edit Distance
int SED(char A[], char B[], int a, int b, int k)
{
    int min_time;
    for(int i = 0; i <= a; ++i) pre[i] = i;
    for(int j = 1; j <= b; ++j)
    {
        cur[0] = j;
        min_time = j + 1;
        for(int i = 1; i <= a; ++i)
        {
            cur[i] = min(pre[i] + 1,cur[i-1] + 1);
            cur[i] = min(cur[i], pre[i-1] + 2 * (A[i-1] != B[j-1]));
            min_time = min(min_time, cur[i]);
        }
        for(int i = 1; i <= a; ++i) {
            pre[i] = cur[i];
        }
        if(min_time > k) return -1;
    }
    return cur[a];
}

int main()
{
    scanf("%d %d %d", &a, &b, &k);
    scanf("%s", A);
    scanf("%s", B);
    if((a-b) > k || (b-a) > k) cout << -1;
    else cout << SED(A, B, a, b, k);
    return 0;
}