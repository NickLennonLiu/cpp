#include "temperature.h"
#include <cstdlib>

#define nmax 800000
#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define lc(x) ((x) << 1)
#define rc(x) (((x) << 1) | 1)
#define MAX(x, y) (((x) < (y)) ? (y) : (x))
#define MIN(x, y) (((x) > (y)) ? (y) : (x))

// 观测站
struct observer
{
    int x, y, tmin, tmax;
};
observer obs[nmax];

// 快排比较函数：观测站之间的比较，首先比x，然后再比y
int cmp(const void *a, const void *b)
{
    if(((observer *)a)->x == ((observer *)b)->x && ((observer *)a)->y == ((observer *)b)->y)
        return 0;
    if (((observer *)a)->x == ((observer *)b)->x)
        return (((observer *)a)->y > ((observer *)b)->y) ? 1 : -1;
    return (((observer *)a)->x > ((observer *)b)->x) ? 1 : -1;
}

// kdTree节点
struct kdnode
{
    int leaf;   // 是否为叶节点
    int tmin, tmax; // 最低最高温度
    int xmin, xmax, ymin, ymax; // hitbox
    void report(int *TMIN, int *TMAX)   // 报告温度（更新最值）
    {
        *TMIN = MIN(*TMIN, tmin);
        *TMAX = MAX(*TMAX, tmax);
    }
};

kdnode tree[nmax << 1];

inline void createLeaf(int ob, int pos) // 创建叶节点
{
    tree[pos].leaf = 1; // leaf
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

// 按x坐标对点集进行划分
inline int xpartition(int lo, int hi, int mid)
{
    if(lo == hi) 
        return lo;
    swap(obs[mid], obs[lo]);
    int x = obs[lo].x;
    observer pivot = obs[lo];
    while (lo < hi)
    {
        while (lo < hi && x < obs[hi].x)
            hi--;
        if (lo < hi)
            obs[lo++] = obs[hi];
        while (lo < hi && obs[lo].x < x)
            lo++;
        if (lo < hi)
            obs[hi--] = obs[lo];
    }
    obs[lo] = pivot;
    return lo;
}

// 按y坐标对点集进行划分
inline int ypartition(int lo, int hi, int mid)
{
    swap(obs[mid], obs[lo]);
    int y = obs[lo].y;
    observer pivot = obs[lo];
    while (lo < hi)
    {
        while (lo < hi && y < obs[hi].y)
            hi--;
        if (lo < hi)
            obs[lo++] = obs[hi];
        while (lo < hi && obs[lo].y < y)
            lo++;
        if (lo < hi)
            obs[hi--] = obs[lo];
    }
    obs[lo] = pivot;
    return lo;
}

// 在d方向上对区间[lo,hi]取中位数
int findMedianAndDivide(int d, int lo, int hi)
{
    int mid = lo + ((hi - lo) >> 1);
    int q = mid;
    while (lo < hi)
    {
        q = d ? xpartition(lo, hi, mid) : ypartition(lo, hi, mid);
        if(q < mid) {
            lo = q+1;
        } else if(q > mid) {
            hi = q-1;
        } else {
            break;
        }
    }
    return mid;
}

// 创建节点pos，需要记录它的温度最值以及碰撞箱
void generate(int pos)
{
    tree[pos].tmin = MIN(tree[lc(pos)].tmin, tree[rc(pos)].tmin);
    tree[pos].tmax = MAX(tree[lc(pos)].tmax, tree[rc(pos)].tmax);
    tree[pos].xmin = MIN(tree[lc(pos)].xmin, tree[rc(pos)].xmin);
    tree[pos].xmax = MAX(tree[lc(pos)].xmax, tree[rc(pos)].xmax);
    tree[pos].ymin = MIN(tree[lc(pos)].ymin, tree[rc(pos)].ymin);
    tree[pos].ymax = MAX(tree[lc(pos)].ymax, tree[rc(pos)].ymax);
}

// 递归建树
void buildKdTree(int lo, int hi, int d, int pos)
{
    if (lo == hi)
    {
        createLeaf(lo, pos);
        return;
    }

    int mid = findMedianAndDivide(d, lo, hi);
    buildKdTree(lo, mid, d ^ 1, lc(pos));
    buildKdTree(mid + 1, hi, d ^ 1, rc(pos));
    generate(pos);
}

// 观测站同一坐标去重
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

// 初始化
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

// 碰撞箱判定：被包含
inline bool inside(kdnode *v, const int &x1, const int &x2, const int &y1, const int &y2)
{
    return v->xmin >= x1 && v->xmax <= x2 && v->ymin >= y1 && v->ymax <= y2;
}

// 碰撞箱判定：相交
inline bool intersect(kdnode *v, const int &x1, const int &x2, const int &y1, const int &y2)
{
    return !(v->xmax < x1 || v->xmin > x2 || v->ymin > y2 || v->ymax < y1);
}

// 剪枝判断
inline bool necessary(int v, int *tmin, int *tmax)
{
    // 若节点内的温度最值有可能更新当前的温度最值之一，才深入查询
    return tree[v].tmin < *tmin || tree[v].tmax > *tmax;
}

// 递归查找，返回是否找到了观测站
bool kdSearch(int v,const int& x1,const int& x2,const int& y1,const int& y2, int *tmin, int *tmax)
{
    bool found = false; // 区域内是否有观测站
    if (tree[v].leaf)   // 叶节点：单点
    {
        if (inside(tree + v, x1, x2, y1, y2))
        {
            found = true;
            tree[v].report(tmin, tmax);
        }
        return found;
    }
    // 左子树
    if (inside(tree + lc(v), x1, x2, y1, y2))
    {
        found = true;
        tree[lc(v)].report(tmin, tmax);
    } else if (intersect(tree + lc(v), x1, x2, y1, y2) && necessary(lc(v), tmin, tmax)) // 可添加剪枝
        found |= kdSearch(lc(v), x1, x2, y1, y2, tmin, tmax);
    // 右子树
    if (inside(tree + rc(v), x1, x2, y1, y2))
    {
        found = true;
        tree[rc(v)].report(tmin, tmax);
    } else if (intersect(tree + rc(v), x1, x2, y1, y2) && necessary(rc(v), tmin, tmax)) // 可添加剪枝
        found |= kdSearch(rc(v), x1, x2, y1, y2, tmin, tmax);
    return found;
}

// 询问函数
void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax)
{
    *tmin = INT_MAX;
    *tmax = INT_MIN;
    if (kdSearch(1, x1, x2, y1, y2, tmin, tmax))    // 如果查询时确实访问到了至少一个观测站，则结束
        return;
    *tmin = *tmax = -1; // 否则将tmin,tmax改为-1
}