#include <iostream>
using namespace std;

void decompose(int n, int *d)
{
    for(int i = 0; i < 4; ++i)
    {
        d[i] = n % 10;
        n /= 10;
    }
}

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

void slowSort(int *s, int *t)
{
    if (s == t - 1 || s == t)
        return;
    auto key = *s;
    auto l = s, r = t - 1;
    while (l != r)
    {
        while (r != l && *r < key)
            --r;
        if (r != l)
            *(l++) = *r;
        while (l != r && *l > key)
            ++l;
        if (l != r)
            *(r--) = *(l);
    }
    *(l) = key;
    slowSort(l + 1, t);
    slowSort(s, l);
}

int compose(int* d)
{
    int sum = 0;
    for(int i = 3; i >= 0 ; --i)
        sum = sum * 10 + d[i];
    return sum;
}

int main()
{
    int n, g, l;
    int d[4] = {0};
    cin >> n;
    int time = 0;
    while(n != 6174)
    {
        decompose(n, d);
        quickSort(d,d+4);
        g = compose(d);
        slowSort(d,d+4);
        l = compose(d);
        n = g - l;
        ++time;
    }
    cout << time << endl;
    return 0;
}