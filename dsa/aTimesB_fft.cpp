#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;

#define MAX_LEN 131072

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

const double PI = acos(-1.0);

int rev[131072];
Complex temp[131072];

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
            swap(f[i], f[rev[i]]);
    }
}

// n == 1<<m;
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

Complex a[MAX_LEN/2], b[MAX_LEN/2];
int alen = 0, blen = 0, len = 0;
int s[MAX_LEN];

void getNum(Complex num[], int &n){
    n = 0;
    int d[MAX_LEN/2], len = 0;

    char c;
    while ((c = getchar()) == ' ' || c == '\n');

    while(c != ' ' && c != '\n'){
        d[len++] = c-'0';
        c = getchar();
    }

    for(int i = len-1; i >= 0; i--){
        num[n++] = Complex(d[i],0);
    }
}

int main()
{
    int n;
    cin >> n;
    for(int i = 0;i < n;i++){
        getNum(a, alen);
        getNum(b, blen);

        len = 2;
        while(len < (alen*2) || len < (blen*2)) len <<= 1;

        for(int j = alen; j < len ;++ j) a[j] = Complex(0,0);
        for (int j = blen; j < len; ++j)
            b[j] = Complex(0, 0);

        DFT(a, len, 1), DFT(b, len, 1);

        for(int j = 0;j < len; j++) a[j] = a[j] * b[j];

        DFT(a, len, -1);

        for(int j = 0; j < len; j++){
            s[j] = int(a[j].re + 0.5);
        }

        for(int j = 0;j < len;j++)
        {
            s[j + 1] += s[j] / 10;
            s[j] %= 10;
        }

        int clen = alen + blen + 1;
        while(s[clen] == 0 && clen >=0) --clen;
        while(clen>=0)
        {
            printf("%d", s[clen--]);
            cout << s[clen--];
        }        
        cout << endl;
    }
}