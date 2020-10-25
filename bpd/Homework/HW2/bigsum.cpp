#include <iostream>
using namespace std;

char as[101] = {0}, bs[101] = {0};
int c[102],a[102],b[102];


int main()
{
    scanf("%s %s",as,bs);
    int alen = 100, blen = 100;
    while(!as[alen]) --alen;
    while(!bs[blen]) --blen;
    for(int i = 0; i <= alen; i++)
    {
        a[i] = as[alen-i] - '0';
    }
    for (int i = 0; i <= blen; i++)
    {
        b[i] = bs[blen - i] - '0';
    }
    int clen = 100;
    for(int i = 0; i <= alen || i <= blen; ++i)
    {
        c[i] += a[i] + b[i];
        c[i+1] += c[i] / 10;
        c[i] %= 10;
    }
    while(!c[clen] && clen > 0) clen--;
    for(int j = clen; j >= 0; --j)
        cout << c[j];
    return 0;
}