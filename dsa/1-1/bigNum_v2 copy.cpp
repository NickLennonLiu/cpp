#include <stdio.h>
#include <cstring>

char as[10001], bs[10001];
__int128 a[1251], b[1251], c[1251];
int alen, blen, clen;
int n;

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
    {
        scanf("%s %s", as, bs);
        int al = strlen(as), bl = strlen(bs);

        alen = (al % 11) ? al / 11 + 1 : al / 11;
        long long num = 0;
        for(int j = 0; j < alen; ++j)
        {
            int p = al - 11 * (j + 1);
            if (p < 0) p = 0;
            num = 0;
            while (p < al - 11 * j)
            {
                num = num * 10 + as[p++] - '0';
            }
            a[j] = num;
        }

        blen = (bl % 11) ? bl / 11 + 1 : bl / 11;
        for (int j = 0; j < blen; ++j)
        {
            int p = bl - 11 * (j + 1);
            if (p < 0)
                p = 0;
            num = 0;
            while (p < bl - 11 * j)
            {
                num = num * 10 + bs[p++] - '0';
            }
            b[j] = num;
        }

        for (int i = 0; i < 1251; ++i)
            c[i] = 0;

        int idx = 0;
        __int128 result ,next = 0;
        for (int k = 0; k < alen; ++k)
        {
            next = 0;
            for (int j = 0; j < blen; ++j)
            {
                idx = k + j;
                result = a[k] * b[j] + next + c[idx];
                c[idx] = result % 1000000000;
                next = result / 1000000000;
            }
            c[k + blen] += next;
        }
        c[alen + blen] = next;
        clen = (alen + blen - 1) + (next > 0);

        for (int j = clen - 1; j >= 0; --j)
        {
            //printDigit(n[i], (i != (clen - 1)));
            if(j == (clen-1) ) printf("%lld", c[j]);
            else for (long long k = 10000000000; k; k /= 10)
            {
                printf("%d", c[j]/k);
                c[j] -= (c[j] / k) * k;
            }
        }
        printf("\n");
    }
}