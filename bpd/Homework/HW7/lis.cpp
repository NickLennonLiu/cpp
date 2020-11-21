#include <iostream>
using namespace std;

int n;
int num[1001];
int dp[1001];
int lis = 1;

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    dp[0] = 1;
    for(int i = 1;i < n; i++)
    {
        int temp = dp[i] = 1;
        for(int j = 0; j < i; ++j)
        {
            if(num[i] >= num[j] && temp < dp[j] + 1)
                temp = dp[j] + 1;
        }
        dp[i] = temp;
        lis = (lis > temp) ? lis : temp;
    }
    cout << lis;
    return 0;
}