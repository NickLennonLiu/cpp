#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "temperature.h"

using namespace std;

#define nmax 400000
#define lc(x) ((x) << 1)
#define rc(x) (((x) << 1) | 1)
#define MAX(x, y) (((x) < (y)) ? (y) : (x))
#define MIN(x, y) (((x) > (y)) ? (y) : (x))

struct observer
{
    int x, y, tmin, tmax;
};
observer obs[nmax];

// 快排比较函数：观测站之间的比较，首先比x，然后再比y
int cmp(const void *a, const void *b)
{
    if (((observer *)a)->x == ((observer *)b)->x && ((observer *)a)->y == ((observer *)b)->y)
        return 0;
    if (((observer *)a)->x == ((observer *)b)->x)
        return (((observer *)a)->y > ((observer *)b)->y) ? 1 : -1;
    return (((observer *)a)->x > ((observer *)b)->x) ? 1 : -1;
}

int xcmp(const void *a, const void *b)
{
    if (((observer *)a)->x == ((observer *)b)->x)
        return 0;
    return (((observer *)a)->x > ((observer *)b)->x) ? 1 : -1;
}

int ycmp(const void *a, const void *b)
{
    if (((observer *)a)->y == ((observer *)b)->y)
        return 0;
    return (((observer *)a)->y > ((observer *)b)->y) ? 1 : -1;
}

struct kdnode
{
    int d;
    int splitline;
    int tmin, tmax;
    int xmin, xmax, ymin, ymax;
    void report(int *TMIN, int *TMAX)
    {
        *TMIN = MIN(*TMIN, tmin);
        *TMAX = MAX(*TMAX, tmax);
    }
};

kdnode tree[nmax << 1];

void createLeaf(int ob, int pos)
{
    tree[pos].d = 2; // leaf
    tree[pos].xmin = tree[pos].xmax = obs[ob].x;
    tree[pos].ymin = tree[pos].ymax = obs[ob].y;
    tree[pos].tmin = obs[ob].tmin;
    tree[pos].tmax = obs[ob].tmax;
}

inline void swap(observer &a, observer &b)
{
    observer c = a;
    a = b;
    b = c;
}

int partition(int d, int lo, int hi)
{
    if (d)
    {
        int x = obs[hi].x, i = lo - 1;
        for (int j = lo; j < hi; ++j)
        {
            if (obs[j].x <= x)
            {
                swap(obs[++i], obs[j]);
            }
        }
        swap(obs[i + 1], obs[hi]);
        return i + 1;
    }
    else
    {
        int y = obs[hi].y, i = lo - 1;
        for (int j = lo; j < hi; ++j)
        {
            if (obs[j].y <= y)
            {
                swap(obs[++i], obs[j]);
            }
        }
        swap(obs[i + 1], obs[hi]);
        return i + 1;
    }
}

void findMedianAndDivide(int d, int lo, int hi)
{
    int mid = lo + ((hi - lo) >> 1);
    //int q = partition(d, lo, hi);
    cout << "debug: divide start" << lo << hi << endl;
    int q = 0;
    while (1)
    {
        
        //q = (q < mid) ? partition(d, q + 1, hi) : partition(d, lo, q - 1);
        if (d)
        {
            int x = obs[hi].x;
            q = lo - 1;
            for (int j = lo; j < hi; ++j)
            {
                if (obs[j].x <= x)
                {
                    swap(obs[++q], obs[j]);
                }
            }
            swap(obs[q + 1], obs[hi]);
            q++;
        }
        else
        {
            int y = obs[hi].y;
            q = lo - 1;
            for (int j = lo; j < hi; ++j)
            {
                if (obs[j].y <= y)
                {
                    swap(obs[++q], obs[j]);
                }
            }
            swap(obs[q + 1], obs[hi]);
            q++;
        }
        if (q < mid)
        {
            lo = q + 1;
        }
        else if (q > mid)
        {
            hi = q - 1;
        }
        else
        {
            break;
        }
        cout << "debug" << q <<" " << mid<< " " << lo <<" "<<  hi << endl;
    }
}

void generate(int pos)
{
    tree[pos].tmin = MIN(tree[lc(pos)].tmin, tree[rc(pos)].tmin);
    tree[pos].tmax = MAX(tree[lc(pos)].tmax, tree[rc(pos)].tmax);
    tree[pos].xmin = MIN(tree[lc(pos)].xmin, tree[rc(pos)].xmin);
    tree[pos].xmax = MAX(tree[lc(pos)].xmax, tree[rc(pos)].xmax);
    tree[pos].ymin = MIN(tree[lc(pos)].ymin, tree[rc(pos)].ymin);
    tree[pos].ymax = MAX(tree[lc(pos)].ymax, tree[rc(pos)].ymax);
}

// [lo,hi]
void buildKdTree(int lo, int hi, int d, int pos)
{
    cout << "debug start" << pos << lo << hi << endl;
    if (lo == hi)
    {
        createLeaf(lo, pos);
        return;
    }

    int mid = lo + ((hi - lo) >> 1);
    tree[pos].d = d;
    findMedianAndDivide(d, lo, hi);
    /*
    if(d)
        qsort(obs+lo,(hi-lo)+1,sizeof(obs[0]),xcmp);
    else
        qsort(obs+lo,(hi-lo)+1,sizeof(obs[0]),ycmp);
    */

    tree[pos].splitline = d ? obs[mid].x : obs[mid].y;
    buildKdTree(lo, mid, d ^ 1, lc(pos));
    buildKdTree(mid + 1, hi, d ^ 1, rc(pos));
    generate(pos);
    //cout << "debug" << pos << endl;
}

int deduplicate(int n)
{
    int newn = 0;
    for (int i = 1; i < n; ++i)
    {
        if (obs[i].x == obs[newn].x && obs[i].y == obs[newn].y)
        {
            obs[newn].tmin = MIN(obs[newn].tmin, obs[i].tmin);
            obs[newn].tmax = MAX(obs[newn].tmax, obs[i].tmax);
        }
        else
        {
            obs[++newn] = obs[i];
        }
    }
    return newn + 1;
}

void init(int n, const int *x, const int *y, const int *t)
{
    for (int i = 0; i < n; ++i)
    {
        obs[i].x = x[i];
        obs[i].y = y[i];
        obs[i].tmin = obs[i].tmax = t[i];
    }
    qsort(obs, n, sizeof(observer), cmp);
    n = deduplicate(n);
    buildKdTree(0, n - 1, 1, 1); // 从根建起，初始方向为x
}

inline bool inside(kdnode *v, int x1, int x2, int y1, int y2)
{
    return v->xmin >= x1 && v->xmax <= x2 && v->ymin >= y1 && v->ymax <= y2;
}

inline bool intersect(kdnode *v, int x1, int x2, int y1, int y2)
{
    return !(v->xmax < x1 || v->xmin > x2 || v->ymin > y2 || v->ymax < y1);
}

bool kdSearch(int v, const int &x1, const int &x2, const int &y1, const int &y2, int *tmin, int *tmax)
{
    bool found = false;
    if (tree[v].d == 2)
    {
        if (inside(tree + v, x1, x2, y1, y2))
        {
            found = true;
            tree[v].report(tmin, tmax);
        }
        return found;
    }
    if (inside(tree + lc(v), x1, x2, y1, y2))
    {
        found = true;
        tree[lc(v)].report(tmin, tmax);
    }
    else if (intersect(tree + lc(v), x1, x2, y1, y2)) // 可添加剪枝
        found |= kdSearch(lc(v), x1, x2, y1, y2, tmin, tmax);
    if (inside(tree + rc(v), x1, x2, y1, y2))
    {
        found = true;
        tree[rc(v)].report(tmin, tmax);
    }
    else if (intersect(tree + rc(v), x1, x2, y1, y2)) // 可添加剪枝
        found |= kdSearch(rc(v), x1, x2, y1, y2, tmin, tmax);
    return found;
}

void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax)
{
    *tmin = INT_MAX;
    *tmax = INT_MIN;
    if (kdSearch(1, x1, x2, y1, y2, tmin, tmax))
        return;
    *tmin = *tmax = -1;
}

int main()
{
    // in case of defined(NDEBUG), do not write `assert(1 == scanf("%d", &n))'
    int res; // store the return value of `scanf'
    int n;
    res = scanf("%d", &n);
    assert(1 == res);
    assert(1 <= n && n <= 200000);

    // init stations
    int *x = new int[n], *y = new int[n];
    int *t = new int[n];
    for (int i = 0; i < n; i++)
    {
        long long xi, yi, ti;
        res = scanf("%lld%lld%lld", &xi, &yi, &ti);
        assert(3 == res);
        x[i] = xi;
        y[i] = yi;
        t[i] = ti;
        assert(x[i] == xi && y[i] == yi && t[i] == ti); // check overflow
        assert(t[i] >= 0);
    }
    init(n, x, y, t);

    // after init(), forbid using x, y, and t
    memset(x, 0, n * sizeof(int));
    memset(y, 0, n * sizeof(int));
    memset(t, 0, n * sizeof(int));
    delete[] x;
    delete[] y;
    delete[] t;

    // do query
    long long x1, x2, y1, y2;
    int m = 0;
    while (EOF != (res = scanf("%lld%lld%lld%lld", &x1, &x2, &y1, &y2)))
    {
        assert(4 == res);
        assert(x1 == (int)x1 && x2 == (int)x2 && y1 == (int)y1 && y2 == (int)y2); // check overflow
        assert(x1 <= x2 && y1 <= y2);
        int tmin, tmax;
        query(x1, x2, y1, y2, &tmin, &tmax);
        printf("%d %d\n", tmin, tmax);
        m++;
    }

    assert(1 <= m && m <= 160000);

    return 0;
}
