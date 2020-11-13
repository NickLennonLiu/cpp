#include <cstdlib>
#include "temperature.h"

using namespace std;

#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#define lc(x) ((x) << 1 | 1)
#define rc(x) ((x) << 1 + 2)
#define parent(x) ((x) >> 1)

struct observer
{
    int x, y, t;
}obs[200001];

struct yListNode
{
    observer ob;
    yListNode *next, *prev;
    yListNode()
    {
    }
    yListNode(observer ob)
        : ob(ob), next(nullptr), prev(nullptr)
    {
    }
};

struct yList
{
    int tmin, tmax, len;
    yListNode *header, *trailer;
    yList()
    {
        header = new yListNode();
        trailer = new yListNode();
        header->next = trailer;
        trailer->prev = header;
        tmin = -2147483648;
        tmax = 2147483647;
        len = 0;
    }
    yListNode *insertAtBack(yListNode *cur, observer ob)
    {
        yListNode *newnode = new yListNode(ob);
        newnode->prev = cur;
        newnode->next = cur->next;
        cur->next->prev = newnode;
        cur->next = newnode;
        ++len;
    }
};

struct xnode
{
    int key;
    bool isLeaf;
    yList yQuery;
    xnode(int x, bool leaf = false)
    : key(x), isLeaf(leaf)
    {}
};

xnode* xtree[400001];

xnode* leafs[400001];



// Todo: 如果是双向链表，应该如何merge？
void merge(yList& c, yList& a, yList& b)
{
    yListNode *na = a.header->next,
              *nb = b.header->next,
              *nc = c.header;
    while(na != a.trailer && nb != b.trailer)
    {
        if(na->ob.y < nb->ob.y)
        {
            nc = c.insertAtBack(nc, na->ob);
            na = na->next;
        } else {
            nc = c.insertAtBack(nc, nb->ob);
            nb = nb->next;
        }
    }
    while(na != a.trailer)
    {
        nc = c.insertAtBack(nc, na->ob);
        na = na->next;
    }
    while(nb != b.trailer)
    {
        nc = c.insertAtBack(nc, nb->ob);
        nb = nb->next;
    }
}

int xcmp(const void* a, const void* b)
{
    if (((observer *)a)->x == ((observer *)b)->x)
        return (((observer *)a)->y > ((observer *)b)->y) ? 1 : -1;
    return (((observer *)a)->x > ((observer *)b)->x) ? 1 : -1;
}

void construct(int lo, int hi, int pos)
{
    // 递归基：叶节点
    if (lo == hi)
    {
        xtree[pos] = leafs[lo];
        return;
    }
    int mid = (lo + hi) >> 1;
    construct(lo, mid, lc(pos));
    construct(mid + 1, hi, rc(pos));
    xtree[pos] = new xnode(leafs[mid]->key);
    //xtree[pos]->yQuery.header = merge(xtree[lc(pos)]->yQuery.header, xtree[rc(pos)]->yQuery.header);
    merge(xtree[pos]->yQuery, xtree[lc(pos)]->yQuery, xtree[rc(pos)]->yQuery);
    xtree[pos]->yQuery.tmax = MAX(xtree[lc(pos)]->yQuery.tmax, xtree[rc(pos)]->yQuery.tmax);
    xtree[pos]->yQuery.tmin = MIN(xtree[lc(pos)]->yQuery.tmin, xtree[rc(pos)]->yQuery.tmin);
}

void init(int n, const int *x, const int *y, const int *t)
{
    for(int i = 0; i < n; ++i)
    {
        obs[i].x = x[i];
        obs[i].y = y[i];
        obs[i].t = t[i];
    }

    qsort(obs,n,sizeof(observer),xcmp); // 按照横坐标对观测站排序
    int leaf_cnt = 0;
    leafs[0] = new xnode(obs[0].x,true);
    //yListNode *lca = leafs[0]->yQuery.header->next = new yListNode(obs[0]);
    yListNode *lca = leafs[0]->yQuery.insertAtBack(leafs[0]->yQuery.header, obs[0]);
    leafs[0]->yQuery.tmax = leafs[0]->yQuery.tmin = obs[0].t;

    for (int i = 1; i < n; ++i)
    {
        if(obs[i].x != obs[i-1].x)
        {
            leafs[++leaf_cnt] = new xnode(obs[i].x, true);
            
            lca = leafs[leaf_cnt]->yQuery.insertAtBack(leafs[leaf_cnt]->yQuery.header,obs[i]);
            //lca = leafs[leaf_cnt]->yQuery.header->next = new yListNode(obs[i]);
            
            leafs[leaf_cnt]->yQuery.tmax = leafs[leaf_cnt]->yQuery.tmin = obs[i].t;
        } else {
            leafs[leaf_cnt]->yQuery.tmax = MAX(leafs[leaf_cnt]->yQuery.tmax, obs[i].t);
            leafs[leaf_cnt]->yQuery.tmin = MIN(leafs[leaf_cnt]->yQuery.tmin, obs[i].t);
            
            lca = leafs[leaf_cnt]->yQuery.insertAtBack(lca, obs[i]);
            //lca = lca->next = new yListNode(obs[i]);
        }
    }
    construct(0, leaf_cnt, 0);
}

bool report(xnode *node, int y1, int y2, int *tmin, int *tmax)
{
    yListNode *first = node->yQuery.header->next,
              *last = node->yQuery.trailer->prev;
    if (y1 <= first->ob.y && last->ob.y <= y2)
    {
        *tmin = MIN(*tmin, node->yQuery.tmin);
        *tmax = MAX(*tmax, node->yQuery.tmax);
        return true;
    }
    if (last->ob.y < y1 || first->ob.y > y2)
        return false;
    if (last->ob.y <= y2)
    {
        while (last != node->yQuery.header && last->ob.y >= y1)
        {
            *tmin = MIN(*tmin, last->ob.t);
            *tmax = MAX(*tmax, last->ob.t);
            last = last->prev;
        }
    }
    else
    {
        while (first != node->yQuery.trailer && first->ob.y <= y2)
        {
            *tmin = MIN(*tmin, first->ob.t);
            *tmax = MAX(*tmax, first->ob.t);
            first = first->next;
        }
    }
    return true;
}

void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax)
{
    bool found = false;
    // 确定lca TODO:考虑lca为叶节点的情况
    int lca = 0, key = xtree[lca]->key;
    while(x1 < key && x2 < key
        || x1 > key && x2 > key)
    {
        lca = (x1 < key) ? lc(lca) : rc(lca);
        key = xtree[lca]->key; 
    }
    // 从lca开始往下报告 TODO：叶节点是否报告需要判断？
    int cur = lca;
    // Left side: Ignore all right turns, report leaf and right subtree.
    key = xtree[lca]->key;
    while(!xtree[cur]->isLeaf)
    {
        if(key < x1)
        {
            cur = rc(cur);
            key = xtree[cur]->key;
        }
        else
        {
            found = report(xtree[rc(cur)],y1,y2,tmin,tmax);
            cur = lc(cur);
            key = xtree[cur]->key;
        }
    }
    if(xtree[cur]->key >= x1)
        found = report(xtree[cur], y1, y2, tmin, tmax);

    // Right side: Ignore all left turns, report leaf and left subtree.
    cur = lca;
    key = xtree[lca]->key;
    while (!xtree[cur]->isLeaf)
    {
        if (x2 < key)
        {
            cur = lc(cur);
            key = xtree[cur]->key;
        }
        else
        {
            found = report(xtree[lc(cur)], y1, y2, tmin, tmax);
            cur = rc(cur);
            key = xtree[cur]->key;
        }
    }
    if(xtree[cur]->key <= x2)
        found = report(xtree[cur], y1, y2, tmin, tmax);
    if(!found)
    {
        *tmin = 0;
        *tmax = 0;
    }
}





