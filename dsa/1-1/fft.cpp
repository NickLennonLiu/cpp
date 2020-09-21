#include <iostream>
#include <cmath>
using namespace std;

struct Complex
{
    long double re, im;
    Complex(long double re, long double im)
        : re(re), im(im)
    {
    }
    Complex()
    {
        re = im = 0.0;
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
    for(int h = 2; h <= n; h <<= 1)
    {
        Complex step(cos(2 * PI / n), sin(rev * 2 * PI / n));
        for(int j = 0; j < n; j += h)
        {
            Complex cur(1,0);
            for(int k = j; k < j + h/2; ++k){
                Complex u = f[k], t = cur * f[k + h/2];
                f[k] = u + t;
                f[k + h/2] = u - t;
                cur = cur * step;
            }
        }
    }
    if(rev == -1)
    {
        for( int i = 0; i< n ;i ++){
            f[i].re /= n;
        }
    }
}

