#include <stdio.h>
#include <cstring>
using namespace std;

#define MAX_LEN 100000

void getNum(long long a[], int &alen){
    alen = 0;
    int d[MAX_LEN/2], len = 0;

    char c;
    while ((c = getchar()) == ' ' || c == '\n');

    while(c != ' ' && c != '\n'){
        d[len++] = c-'0';
        c = getchar();
    }

    int num = 0;
    alen = (len % 4) ? len/4 + 1 : len/4;
    for(int i = 0; i < alen; i++){
        int p = len - 4*(i+1);
        if(p < 0) p = 0;
        num = 0;
        while(p < len - 4 * i)
        {
            num = num*10 + d[p++];
        }
        a[i] = num;
    }
}

void bigNumMultiplication(const long long a[],const int alen,const long long b[],const int blen, long long r[], int &rlen)
{
    for(int i = 0; i < MAX_LEN/4; ++i) r[i] = 0;
    
    int idx = 0, result = 0, next = 0;
    for(int i = 0; i < alen; ++i) {
        next = 0;
        for(int j = 0; j < blen; ++j) {
            idx = i+j;
            result = a[i] * b[j] + next + r[idx];
            r[idx] = result % 10000;
            next = result / 10000;
        }
        r[i + blen] += next;
    }
    r[alen+blen]  = next;
    rlen = (alen + blen - 1) + (next > 0);
    
}

inline void printDigit(int n, bool preZero)
{
    if(!preZero) printf("%d", n);
    else for (int i = 1000; i; i /= 10)
    {
        printf("%d", n/i);
        n -= (n / i) * i;
    }
}

inline void outputNum(const long long n[], const int len)
{
    for(int i = len-1; i>=0; --i)
    {
        printDigit(n[i],(i!=(len-1)));
    }
    printf("\n");
}

int n;
long long a[MAX_LEN/4], b[MAX_LEN/4], r[MAX_LEN/2];
int alen = 0, blen = 0, rlen = 0;
char x[MAX_LEN], y[MAX_LEN];

int main()
{
    scanf("%d", &n);
    for(int i = 0;i < n;i++){
        scanf("%s %s", x, y);
        getNum(a, alen);
        getNum(b, blen);
        bigNumMultiplication(a, alen, b, blen, r, rlen);
        outputNum(r,rlen);
    }
}