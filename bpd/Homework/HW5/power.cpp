#include <iostream>
#include <math.h>
using namespace std;

int fastpower(int n, int m)
{
    long long i = n;
    int re = 1;
    while(m)
    {
        re = (m & 1) ? (re*i)%1000 : re;
        m >>= 1;
        i = (i * i) % 1000;
    }
    return re;
}

void print(int n)
{
    if(!(n/10)) cout << 0;
    if(!(n/100)) cout << 0;
    cout << n;
}

int main()
{
    int t;
    long double m,n;
    cin >> t;
    while(t--)
    {
        cin >> n >> m;
        long double l = m*log10(n) - (long double)((int)(m*log10(n)));
        long double r = (long double)((int)(m*log10(n)));
        int big = (int)(pow(10,l)*((r >= 2) ? 100 : pow(10,r))),
            small = fastpower(n,m);
        print(big);
        cout << " ";
        print(small);
        cout << endl;
    }
    return 0;
}