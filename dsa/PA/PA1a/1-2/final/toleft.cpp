#include <stdio.h>

// 返回真：会有交点，返回假：不会有交点
// lx: 线段与x轴交点的横坐标，ly: 线段与y轴交点的纵坐标
// px: 点的横坐标， py：点的纵坐标
inline bool toLeft(long long lx, long long ly, long long px, long long py)
{
    return ((-lx * py - ly * (px - lx)) <= 0);
}
// 关于点位于直线右侧/左侧的判断，参考了oi-wiki:https://oi-wiki.org/geometry/2d/#_14

long long n, m, x, y;
long long lx[200001], ly[200001];

// 快排（递归版本）
void quickSort(long long *s, long long *t)
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
    quickSort(s, l);
    quickSort(l + 1, t);
}

// 二分查找满足位于点左侧的最外侧线段的对应序号
int bisearch(int lo, int hi)
{
    if(lo==hi) return lo;
    int mid = (lo + hi) / 2;
    if(toLeft(lx[mid],ly[mid],x,y)){
        return bisearch(mid+1,hi);
    } else {
        return bisearch(lo,mid);
    }
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%d", lx+i);
    for(int i = 0; i < n; i ++) scanf("%d", ly+i);

    quickSort(lx,lx+n);
    quickSort(ly,ly+n);

    scanf("%d", &m);
    for(int i = 0;i < m;++i)
    {
        scanf("%lld %lld", &x, &y);
        printf("%d\n",bisearch(0,n));
    }
    return 0;
}