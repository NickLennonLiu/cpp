#include <stdio.h>
#include <cstring>

char as[10001], bs[10001];
long long a[1251], b[1251], c[1251];
int alen, blen, clen;
int n;

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
    {
        scanf("%s %s", as, bs);
        int al = strlen(as), bl = strlen(bs);

        alen = (al % 9) ? al / 9 + 1 : al / 9;
        int num = 0;
        for(int j = 0; j < alen; ++j)
        {
            int p = al - 9 * (j + 1);
            if (p < 0) p = 0;
            num = 0;
            while (p < al - 9 * j)
            {
                num = num * 10 + as[p++] - '0';
            }
            a[j] = num;
        }

        blen = (bl % 9) ? bl / 9 + 1 : bl / 9;
        for (int j = 0; j < blen; ++j)
        {
            int p = bl - 9 * (j + 1);
            if (p < 0)
                p = 0;
            num = 0;
            while (p < bl - 9 * j)
            {
                num = num * 10 + bs[p++] - '0';
            }
            b[j] = num;
        }

        for (int i = 0; i < 1251; ++i)
            c[i] = 0;

        int idx = 0;
        long long result ,next = 0;
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
            else for (int k = 100000000; k; k /= 10)
            {
                printf("%d", c[j]/k);
                c[j] -= (c[j] / k) * k;
            }
        }
        printf("\n");
    }
}