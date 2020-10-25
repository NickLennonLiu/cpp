#include <stdio.h>
#include <cstring>

char as[10001], bs[10001];
int a[2502], b[2502], c[2502];
int alen, blen, clen;
int n;

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
    {
        scanf("%s %s", as, bs);
        int al = strlen(as), bl = strlen(bs);

        alen = (al % 4) ? al / 4 + 1 : al / 4;
        int num = 0;
        for(int j = 0; j < alen; ++j)
        {
            int p = al - 4 * (j + 1);
            if (p < 0) p = 0;
            num = 0;
            while (p < al - 4 * j)
            {
                num = num * 10 + as[p++] - '0';
            }
            a[j] = num;
        }

        blen = (bl % 4) ? bl / 4 + 1 : bl / 4;
        for (int j = 0; j < blen; ++j)
        {
            int p = bl - 4 * (j + 1);
            if (p < 0) p = 0;
            num = 0;
            while (p < bl - 4 * j)
            {
                num = num * 10 + bs[p++] - '0';
            }
            b[j] = num;
        }

        for (int i = 0; i < 2500; ++i)
            c[i] = 0;

        int idx = 0, result = 0, next = 0;
        for (int i = 0; i < alen; ++i)
        {
            next = 0;
            for (int j = 0; j < blen; ++j)
            {
                idx = i + j;
                result = a[i] * b[j] + next + c[idx];           //4mn
                c[idx] = result % 10000;
                next = result / 10000;
            }
            c[i + blen] += next;
        }
        c[alen + blen] = next;
        clen = (alen + blen - 1) + (next > 0);

        for (int j = clen - 1; j >= 0; --j)
        {
            //printDigit(n[i], (i != (clen - 1)));
            if(j == (clen-1) ) printf("%d", c[j]);
            else for (int k = 1000; k; k /= 10)
            {
                printf("%d", c[j]/k);
                c[j] -= (c[j] / k) * k;
            }
        }
        printf("\n");
    }
}