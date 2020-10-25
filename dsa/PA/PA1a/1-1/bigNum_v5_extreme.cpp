#include <stdio.h>
#include <cstring>

char as[10001], bs[10001];
long long a[1251], b[1251], c[1251];
int alen, blen, clen;
int n;

int main()
{
    //scanf("%d", &n);
    n = 500;
    for(int i = 0; i < n; i ++)
    {
        scanf("%s %s", as, bs);
        for(int i = 0;i < 4999;++i) as[i] = '9';
        for(int i = 0;i < 4999;++i) bs[i] = '9';
        //int al = strlen(as), bl = strlen(bs);
        int al = 4999, bl = 4999;

        alen = (al % 8) ? al / 8 + 1 : al / 8;
        int num = 0;
        for(int j = 0; j < alen; ++j)
        {
            int p = al - 8 * (j + 1);
            if (p < 0) p = 0;
            num = 0;
            while (p < al - 8 * j)
            {
                num = num * 10 + as[p++] - '0';
            }
            a[j] = num;
        }

        blen = (bl % 8) ? bl / 8 + 1 : bl / 8;
        for (int j = 0; j < blen; ++j)
        {
            int p = bl - 8 * (j + 1);
            if (p < 0)
                p = 0;
            num = 0;
            while (p < bl - 8 * j)
            {
                num = num * 10 + bs[p++] - '0';
            }
            b[j] = num;
        }

        for (int i = 0; i < 1251; ++i)
            c[i] = 0;

        clen = alen + blen - 1;
        for (int i = 0; i < clen; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                c[i] += a[j] * b[i - j];
            }
            if (c[i] >= 100000000)
            {
                c[i + 1] += c[i] / 100000000;
                c[i] %= 100000000;
            }
        }
        clen += (c[clen] && 1);

        for (int j = clen - 1; j >= 0; --j)
        {
            if(j == (clen-1) ) printf("%lld", c[j]);
            else for (int k = 10000000; k; k /= 10)
            {
                printf("%d", (c[j]/k)%10);
            }
        }
        printf("\n");
    }
}