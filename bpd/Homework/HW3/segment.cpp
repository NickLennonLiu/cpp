#include <iostream>
using namespace std;

struct segment
{
    long long lo, hi;
};

segment seg[10000];

void quickSort(segment *s, segment *t)
{
    if (s == t - 1 || s == t)
        return;
    auto key = s->lo;
    auto tmp = s->hi;
    auto l = s, r = t - 1;
    while (l != r)
    {
        while (r != l && r->lo > key)
            --r;
        if (r != l)
        {
            l->lo = r->lo;
            l->hi = r->hi;
            ++l;
        }
        while (l != r && l->lo < key)
            ++l;
        if (l != r)
        {
            r->lo = l->lo;
            r->hi = l->hi;
            --r;
        }
    }
    l->lo = key; l->hi = tmp;
    quickSort(s, l);
    quickSort(l + 1, t);
}

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> seg[i].lo >> seg[i].hi;
    quickSort(seg+0, seg+n);
    long long left = seg[0].lo, right = seg[0].hi, sum = 0;
    for(int i = 1; i < n; ++i)
    {
        if(seg[i].lo > right)
        {
            sum += (right - left);
            left = seg[i].lo;
            right = seg[i].hi;
        }
        else
            right = (right > seg[i].hi) ? right : seg[i].hi;
    }
    sum += (right - left);
    cout << sum;
    
    return 0;
}