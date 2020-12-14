#include <iostream>
#include <cstdio>
using namespace std;

#define nmax 10000001



void quickSort(int *s, int *t)
{
    if (s == t - 1 || s == t)
        return;
    auto key = *s;
    auto l = s, r = t - 1;
    while (l != r)
    {
        while (r != l && *r > key)
            --r;
        if (r != l)
            *(l++) = *r;
        while (l != r && *l < key)
            ++l;
        if (l != r)
            *(r--) = *(l);
    }
    *(l) = key;
    quickSort(l + 1, t);
    quickSort(s, l);
}

int n;
int weight[nmax];
long long tot;

int main()
{
    cin >> n;
    for(int i = 0; i < n; ++i){
        scanf("%d", weight+i);
        tot += weight[i];
    }
    quickSort(weight, weight+n);
    long long weight1 = 0;
    for(int i = 0; i < n/2; ++i){
        weight1 += weight[i];
    }
    cout << tot - 2*weight1;
    return 0;
}