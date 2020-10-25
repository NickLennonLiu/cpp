#include <iostream>
using namespace std;

/*
Honor Code:
- Discussed with:
- - 2018年dsa习题课PA1 计73 王雨田PPT 获得根据限制k进行优化的思路
- Reference:
- - dsa2020讲义 绪论 dp lcs部分
*/

// pre[j] at layer = i : LCS(A[0,i),B[0,j))
// curK[j+k] at layer = i : 范围为[i-k,i+k]内的LCS
int pre[501001], curK[201];
char A[501001], B[501001];
int a, b, k;

int LCS(char A[], char B[], int a, int b, int k)
{
    // layer 0: LCS(A[0,0),B[0,j)) j from 0 to b
    for(int j = 0;j <= b;j++) pre[j] = 0;
    for(int i = 1;i <= a;i++)
    {
        for(int j = -k; j <= k; j++)
        {
            int b_hi = i + j;   // b_hi : i-k -> i + k

            // 跳过越界部分
            if(b_hi <= 0) continue;
            if(b_hi > b) break;

            // A[i-1] == B[i-1] : LCS[i][j] = LCS[i-1][j-1] + 1;
            if(A[i-1]==B[b_hi-1]) curK[j+k] = pre[b_hi - 1] + 1;
            // A[i-1] != B[i-1] : LCS[i][j] = max{LCS[i][j-1], LCS[i-1][j]};
            else curK[j+k] = max((j+k>0) ? curK[j+k-1] : 0,pre[b_hi]);
        }
        // 更新滚动数组
        for(int j = -k; j <= k; j++)
        {
            int b_hi = i + j;   // b_hi : i-k -> i+k
            if(b_hi <= 0) continue;
            if(b_hi > b) break;
            pre[b_hi] = curK[j+k];
        }
    }
    return pre[b];  // LCS[a][b]
}

int main()
{
    scanf("%d %d %d", &a, &b, &k);
    scanf("%s", A);
    scanf("%s", B);

    int lcs = LCS(A, B, a, b, k);   // 计算相差最大距离为K限制下的LCS
    int result = a + b - 2 * lcs;   // 编辑距离 = (alen - lcs) + (blen - lcs);
    if (result > k)                 
        cout << -1;
    else
        cout << result;
    return 0;
}
