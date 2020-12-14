#include <iostream>
using namespace std;
int n, m;

struct interval
{
    int lo, hi;
}intervals[25001];

template <typename T, typename CMP>
void quickSort(T *s, T *t, CMP &cmp)
{
    if (s == t - 1 || s == t)
        return;
    T key = *s;
    T *l = s, *r = t - 1;
    while (l != r)
    {
        while (r != l && cmp(*r, key))
            --r;
        if (r != l)
            *(l++) = *r;
        while (l != r && cmp(key, *l))
            ++l;
        if (l != r)
            *(r--) = *(l);
    }
    *(l) = key;
    quickSort(l + 1, t, cmp);
    quickSort(s, l, cmp);
}

bool cmp(interval a, interval b)
{
    if(a.lo == b.lo)
        return a.hi < b.hi;
    return a.lo > b.lo;
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
        cin >> intervals[i].lo >> intervals[i].hi;
    quickSort(intervals, intervals+n, cmp);
    int end = intervals[0].hi;
    int count = 1;
    if(intervals[0].lo > 1)
    {
        cout << -1 << endl;
        return 0;
    }
    int i = 1;
    while(i < n)
    {
        if(intervals[i].lo > end)
        {
            cout << -1 << endl;
            return 0;
        }
        if(end >= m)
        {
            cout << count << endl;
            return 0;
        }
        int tmax = -1000000;
        while(i < n && intervals[i].lo <= end)
        {
            tmax = max(intervals[i].hi, tmax);
            ++i;
        }
        count ++;
        end = tmax;
    }
    /*
    for(int i = 1; i < n; ++i)
    {
        if(end >= m) {
            cout << count << endl;
            return 0;
        }
        if(intervals[i].lo > end)
        {
            cout << -1 << endl;
            return 0;
        }
        while(i < )
        if(intervals[i].hi <= end)
            continue;
        end = intervals[i].hi;
        count ++;
    }
    */
    cout << count << endl;
    return 0;
}