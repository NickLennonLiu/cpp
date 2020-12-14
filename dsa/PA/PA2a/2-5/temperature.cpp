#include <cstdlib>
#include "temperature.h"

using namespace std;

#define omax 200010
#define INT_MAX 2147483647
#define INT_MIN -2147483648 
#define MAX(x, y) (((x) < (y)) ? (y) : (x))
#define MIN(x, y) (((x) > (y)) ? (y) : (x))
#define lc(x) ((x) << 1)
#define rc(x) (((x) << 1) | 1)
#define parent(x) ((x) >> 1)

struct observer
{
    int x, y, t;
} obs[omax];

// 快排比较函数：观测站之间的比较，首先比x，然后再比y
int xcmp(const void *a, const void *b)
{
    if (((observer *)a)->x == ((observer *)b)->x)
        return (((observer *)a)->y > ((observer *)b)->y) ? 1 : -1;
    return (((observer *)a)->x > ((observer *)b)->x) ? 1 : -1;
}

int cmp(const observer &a, const observer &b)
{
    if (a.x == b.x)
        return a.y > b.y;
    return a.x > b.x;
}

template <typename T, typename CMP>
void quickSort(T *s, T *t, CMP &cmp)
{
    if (s == t - 1 || s == t)
        return;
    T key = *s;
    T *l = s, *r = t - 1;
    while (l != r)
    {
        while (r != l && cmp(*r, key) > 0)
            --r;
        if (r != l)
            *(l++) = *r;
        while (l != r && cmp(key, *l) > 0)
            ++l;
        if (l != r)
            *(r--) = *(l);
    }
    *(l) = key;
    quickSort(l + 1, t, cmp);
    quickSort(s, l, cmp);
}

struct list
{
    int start;
    int end;
    int tmin, tmax;
};

struct node
{
    int key;
    bool isLeaf;
    list yquery;
    bool report(int y1, int y2, int *tmin, int *tmax)
    {
        int start = yquery.start, end = yquery.end;
        if (y1 <= obs[start].y && obs[end].y <= y2)
        {
            *tmin = MIN(*tmin, yquery.tmin);
            *tmax = MAX(*tmax, yquery.tmax);
            return true;
        }
        if (obs[end].y < y1 || obs[start].y > y2)
            return false;
        if (obs[end].y <= y2)
        {
            while (obs[end].y >= y1)
            {
                *tmin = MIN(*tmin, obs[end].t);
                *tmax = MAX(*tmax, obs[end].t);
                if (end == start)
                    break;
                end--;
            }
        }
        else
        {
            while (obs[start].y <= y2)
            {
                *tmin = MIN(*tmin, obs[start].t);
                *tmax = MAX(*tmax, obs[start].t);
                if (start == end)
                    break;
                ++start;
            }
        }
        return true;
    }
};

node *xtree[omax << 1];
node leafs[omax];
//int node_applied = 0;

// 查询函数
void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax)
{
    bool found = false;
    *tmin = INT_MAX;
    *tmax = INT_MIN;
    // 确定lca
    int lca = 1, key = xtree[lca]->key;
    while (!xtree[lca]->isLeaf && (x1 < key && x2 < key || x1 > key && x2 > key))
    {
        lca = (x1 < key) ? lc(lca) : rc(lca);
        key = xtree[lca]->key;
    }
    if (xtree[lca]->isLeaf) // lca为叶节点的情况
    {
        if (xtree[lca]->key >= x1 && x2 >= xtree[lca]->key)
            found = xtree[lca]->report(y1, y2, tmin, tmax);
        if (!found)
            *tmax = *tmin = -1;
        return;
    }
    // 从lca开始往下报告 TODO：叶节点是否报告需要判断？
    // Left side: Ignore all right turns, report leaf and right subtree.
    int cur = lc(lca);
    key = xtree[cur]->key;
    while (!xtree[cur]->isLeaf)
    {
        if (key < x1)
        {
            cur = rc(cur);
            key = xtree[cur]->key;
        }
        else
        {
            found |= xtree[rc(cur)]->report(y1, y2, tmin, tmax);
            cur = lc(cur);
            key = xtree[cur]->key;
        }
    }
    if (xtree[cur]->key >= x1 && xtree[cur]->key <= x2)
        found |= xtree[cur]->report(y1, y2, tmin, tmax);

    // Right side: Ignore all left turns, report leaf and left subtree.
    cur = rc(lca);
    key = xtree[cur]->key;
    while (!xtree[cur]->isLeaf)
    {
        if (x2 < key)
        {
            cur = lc(cur);
            key = xtree[cur]->key;
        }
        else
        {
            found |= xtree[lc(cur)]->report(y1, y2, tmin, tmax);
            cur = rc(cur);
            key = xtree[cur]->key;
        }
    }
    if (xtree[cur]->key >= x1 && xtree[cur]->key <= x2)
        found |= xtree[cur]->report(y1, y2, tmin, tmax);
    if (!found)
    {
        *tmin = *tmax = -1;
    }
}

void merge(list &dst, list &src1, list &src2)
{
    dst.start = src1.start;
    dst.end = src2.end;
    dst.tmax = MAX(src1.tmax, src2.tmax);
    dst.tmin = MIN(src1.tmin, src2.tmin);
}

// 构建区间为[lo,hi]，储存位置为pos的xtree节点
// lo和hi对应的是leafs数组的区间！
void construct(int lo, int hi, int pos)
{
    //printf("constructed %d %d %d\n", lo, hi, pos);
    // 递归基：叶节点
    if (lo == hi)
    {
        xtree[pos] = &leafs[lo];
        return;
    }
    int mid = lo + (hi - lo)/2;
    construct(lo, mid, lc(pos));
    construct(mid + 1, hi, rc(pos));
    //xtree[pos] = new node(leafs[mid].key);
    xtree[pos] = new node;
    xtree[pos]->isLeaf = false;
    xtree[pos]->key = leafs[mid].key;
    merge(xtree[pos]->yquery, xtree[lc(pos)]->yquery, xtree[rc(pos)]->yquery);
}

void debug_tree(int i)
{

    //printf("debug: %d\n", xtree[i]->key);
    if (xtree[i]->isLeaf)
        return;
    debug_tree(lc(i));
    debug_tree(rc(i));
}

void init(int n, const int *x, const int *y, const int *t)
{
    for (int i = 0; i < n; ++i)
    {
        obs[i].x = x[i];
        obs[i].y = y[i];
        obs[i].t = t[i];
    }

    //qsort(obs, n, sizeof(observer), xcmp); // 按照横坐标对观测站排序
    quickSort(obs, obs+n, cmp);

    int lcnt = 0;
    leafs[lcnt].key = obs[0].x;
    leafs[lcnt].isLeaf = true;
    leafs[lcnt].yquery.tmax = leafs[lcnt].yquery.tmin = obs[0].t;
    leafs[lcnt].yquery.start = leafs[lcnt].yquery.end = 0;
    //lcnt++;

    for (int i = 0; i < n; ++i)
    {
        if (obs[i].x != obs[i - 1].x)
        {
            lcnt++;
            leafs[lcnt].key = obs[i].x;
            leafs[lcnt].isLeaf = true;
            leafs[lcnt].yquery.tmax = leafs[lcnt].yquery.tmin = obs[i].t;
            leafs[lcnt].yquery.start = leafs[lcnt].yquery.end = i;
        }
        else
        {
            leafs[lcnt].yquery.tmax = MAX(leafs[lcnt].yquery.tmax, obs[i].t);
            leafs[lcnt].yquery.tmin = MIN(leafs[lcnt].yquery.tmin, obs[i].t);
            leafs[lcnt].yquery.end = i;
        }
    }
    //printf("debug lcnt %d\n", lcnt);
    construct(0, lcnt, 1);
    //debug(1);
}
