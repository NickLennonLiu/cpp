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

        alen = (al % 3) ? al / 3 + 1 : al / 3;
        int num = 0;
        for(int j = 0; j < alen; ++j)
        {
            int p = al - 3 * (j + 1);
            if (p < 0) p = 0;
            num = 0;
            while (p < al - 3 * j)
            {
                num = num * 10 + as[p++] - '0';
            }
            a[j] = num;
        }

        blen = (bl % 3) ? bl / 3 + 1 : bl / 3;
        for (int j = 0; j < blen; ++j)
        {
            int p = bl - 3 * (j + 1);
            if (p < 0) p = 0;
            num = 0;
            while (p < bl - 3 * j)
            {
                num = num * 10 + bs[p++] - '0';
            }
            b[j] = num;
        }

        for (int i = 0; i < 2500; ++i)
            c[i] = 0;

        clen = alen + blen - 1;
        for(int i = 0; i < clen; ++i)
        {
            for(int j = 0;j <= i; ++j)
            {
                c[i] += a[j] * b[i-j];
            }
            if(c[i] >= 1000)
            {
                c[i+1] += c[i] / 1000;
                c[i] %= 1000;
            }
        }
        clen += (c[clen] && 1);

        for (int j = clen - 1; j >= 0; --j)
        {
            if(j == (clen-1) ) printf("%d", c[j]);
            else for (int k = 100; k; k /= 10)
            {
                printf("%d", c[j]/k);
                c[j] -= (c[j] / k) * k;
            }
        }
        printf("\n");
    }
}