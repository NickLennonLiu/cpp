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

struct yListNode
{
    observer ob;
    yListNode *next, *prev;
    yListNode()
    {}
    yListNode(observer ob)
    : ob(ob), next(nullptr), prev(nullptr)
    {}
};

struct yList
{
    int tmin, tmax;
    yListNode *header, *trailer;
    yList()
    {
        header = new yListNode();
        trailer = new yListNode();
        header->next = trailer;
        trailer->prev = header;
        tmin = INT_MIN;
        tmax = INT_MAX;
    }
    yListNode* insertAtBack(yListNode* cur, observer ob)
    {
        yListNode* newnode = new yListNode(ob);
        newnode->prev = cur;
        newnode->next = cur->next;
        cur->next->prev = newnode;
        cur->next = newnode;
    }
};

// Todo: 如果是双向链表，应该如何merge？
yListNode* merge(yListNode* ha, yListNode* hb)
{
    yListNode *header = new yListNode(),
              *na = ha->next,
              *nb = hb->next;
    yListNode *tmp  = header;
    while(na && nb)
    {
        if (na->ob.y < nb->ob.y)
        {
            header = header->next = new yListNode(na->ob);
            na = na->next;
        } else {
            header = header->next = new yListNode(nb->ob);
            nb = nb->next;
        }
    }
    while (na)
    {
        header = header->next = new yListNode(na->ob);
        na = na->next;
    }
    while (nb)
    {
        header = header->next = new yListNode(nb->ob);
        nb = nb->next;
    }
    return tmp;
}

int xcmp(const void* a, const void* b)
{
    if (((observer *)a)->x == ((observer *)b)->x)
        return (((observer *)a)->y > ((observer *)b)->y) ? 1 : -1;
    return (((observer *)a)->x > ((observer *)b)->x) ? 1 : -1;
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
    yListNode *lca = leafs[0]->yQuery.header->next = new yListNode(obs[0]);
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

void construct(int lo, int hi, int pos)
{
    // 递归基：叶节点
    if(lo==hi)
    {
        xtree[pos] = leafs[lo];
        return;
    }
    int mid = (lo + hi) >> 1;
    construct(lo, mid, lc(pos));
    construct(mid + 1, hi, rc(pos));
    xtree[pos] = new xnode(leafs[mid]->key);
    xtree[pos]->yQuery.header = merge(xtree[lc(pos)]->yQuery.header, xtree[rc(pos)]->yQuery.header);
    xtree[pos]->yQuery.tmax = MAX(xtree[lc(pos)]->yQuery.tmax,xtree[rc(pos)]->yQuery.tmax);
    xtree[pos]->yQuery.tmin = MIN(xtree[lc(pos)]->yQuery.tmin,xtree[rc(pos)]->yQuery.tmin);
}


void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax)
{
    *tmin = rand();
    *tmax = rand();
}

void xQuery(int x1, int x2, int y1, int y2, int *tmin, int *tmax)
{
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
            report(xtree[rc(cur)],y1,y2,tmin,tmax);
            cur = lc(cur);
            key = xtree[cur]->key;
        }
    }
    if(xtree[cur]->key >= x1)
        report(xtree[cur], y1, y2, tmin, tmax);

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
            report(xtree[lc(cur)], y1, y2, tmin, tmax);
            cur = rc(cur);
            key = xtree[cur]->key;
        }
    }
    if(xtree[cur]->key <= x2)
        report(xtree[cur], y1, y2, tmin, tmax);
}

void report(xnode* node,int y1, int y2, int *tmin, int *tmax)
{

}



