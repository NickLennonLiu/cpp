#include <cstdio>

int n,m;
int guess[100000];
int temp;
int pair_cnt = 0;

int main()
{
    scanf("%d %d",&n,&m);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            scanf("%d", &temp);
            guess[i] |= (temp << j);
        }
        for(int j = 0; j < i;++ j)
        {
            if ((guess[i] ^ guess[j]) == (1 << m) - 1)
                ++pair_cnt;
        }
    }
    printf("%d", pair_cnt);
    return 0;
}