#include <iostream>
#include <cmath>
using namespace std;

struct Complex
{
    long double re, im;
    Complex(long double re, long double im)
        : re(re)
        , im(im)
    {}
    Complex()
    {
        re = im = 0;
    }
    Complex operator+ (const Complex& b)
    {
        return Complex(re+b.re, im+b.im);
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

#define PI 3.14159265358979323846

Complex temp[1000];

// n == 1<<m;
void DFT(Complex* f, int n, int rev = 1)
{
    if(n == 1) return;
    // 区分奇数偶数
    for(int i = 0;i < n; i++) temp[i] = f[i];
    for(int i = 0;i < n; i++){
        if(i & 1){
            f[i / 2 + n / 2] = temp[i];
        } else {
            f[i / 2] = temp[i];
        }
    }
    //
    // 递归求解DFT
    DFT(f, n/2, rev), DFT(f+n/2, n/2, rev);
    //
    Complex cur(1,0), step(cos(2*PI/n), sin(rev*2*PI/n));
    for(int k = 0;k < n/2; k++)
    {
        temp[k] = f[k] + cur * f[k + n/2];
        temp[k + n/2] = f[k] - cur * f[k + n/2];
        cur = cur * step;
    }
    for(int i = 0; i < n; i++) f[i] = temp[i];
}