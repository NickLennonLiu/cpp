#include <stdio.h>
#include <cstring>
#include <cmath>

struct Complex
{
    long double re, im;
    Complex(long double re, long double im)
        : re(re), im(im)
    {
    }
    Complex()
    {
        re = im = 0;
    }
    Complex operator+(const Complex &b)
    {
        return Complex(re + b.re, im + b.im);
    }
    Complex operator-(const Complex &b)
    {
        return Complex(re - b.re, im - b.im);
    }
    Complex operator*(const Complex &b)
    {
        return Complex(re * b.re - im * b.im, re * b.im + im * b.re);
    }
    Complex operator/(long double c)
    {
        return Complex(re / c, im / c);
    }
};

const long double PI = acos(-1.0);
int rev[5000];
Complex temp[5000];

void change(Complex *f, int n)
{
    for (int i = 0; i < n; i++)
    {
        rev[i] = rev[i / 2] / 2;
        if (i & 1)
        {
            rev[i] |= n / 2;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (i < rev[i])
        {
            Complex tmp = f[i];
            f[i] = f[rev[i]];
            f[rev[i]] = tmp;
        }
        }
}

void DFT(Complex *f, int n, int rev = 1)
{
    change(f, n);
    for (int h = 2; h <= n; h <<= 1)
    {
        Complex step(cos(2 * PI / h), sin(rev * 2 * PI / h));
        for (int j = 0; j < n; j += h)
        {
            Complex cur(1, 0);
            for (int k = j; k < j + h / 2; ++k)
            {
                Complex u = f[k], t = cur * f[k + h / 2];
                f[k] = u + t;
                f[k + h / 2] = u - t;
                cur = cur * step;
            }
        }
    }
    if (rev == -1)
    {
        for (int i = 0; i < n; i++)
        {
            f[i].re /= n;
        }
    }
}

char as[10001], bs[10001];
Complex a[5000], b[5000], c[5000];
long long s[5000];
int alen, blen, clen, len;
int n;

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
    {
        scanf("%s %s", as, bs);
        int al = strlen(as), bl = strlen(bs);

        alen = (al % 6) ? al / 6 + 1 : al / 6;
        int num = 0;
        for(int j = 0; j < alen; ++j)
        {
            int p = al - 6 * (j + 1);
            if (p < 0) p = 0;
            num = 0;
            while (p < al - 6 * j)
            {
                num = num * 10 + as[p++] - '0';
            }
            a[j] = Complex(num,0);
        }

        blen = (bl % 6) ? bl / 6 + 1 : bl / 6;
        for (int j = 0; j < blen; ++j)
        {
            int p = bl - 6 * (j + 1);
            if (p < 0)
                p = 0;
            num = 0;
            while (p < bl - 6 * j)
            {
                num = num * 10 + bs[p++] - '0';
            }
            b[j] = Complex(num,0);
        }

        len = 1;
        while((len < alen*2) || (len < blen*2)) len *= 2;

        for(int j = alen; j < len; j++) a[j] = Complex(0,0);
        for(int j = blen; j < len; j++) b[j] = Complex(0,0);

        DFT(a, len, 1);
        DFT(b, len, 1);

        for(int j = 0; j < len; j++) a[j] = a[j] * b[j];

        DFT(a, len, -1);

        for(int j = 0; j < len; ++j)
            s[j] = (long long)(a[j].re);

        for (int j = 0; j < len; ++j)
        {
            s[j + 1] += s[j] / 1000000;
            s[j] %= 1000000;
        }
        
        while(len > 0 && s[len-1]==0) len--;

        for (int j = len - 1; j >= 0; --j)
        {
            //printDigit(n[i], (i != (clen - 1)));
            if(j == (len-1) ) printf("%lld", s[j]);
            else for (int k = 100000; k; k /= 10)
            {
                printf("%d", s[j]/k);
                s[j] -= (s[j] / k) * k;
            }
        }
        printf("\n");
    }
}