#include <iostream>
using namespace std;

#define lc(x) ((x) << 1 | 1)
#define rc(x) ((x) << 1 + 2)
#define parent(x) ((x) >> 1)

xnode* xtree[10000];  // x-Tree的完全二叉树数组，储存节点指针
ynode* ytree[10000];

struct xnode
{
    int mi;
    int left, right;
    ynode** yquery;
    bool isLeaf()
    {
        return left == right;
    }
};

struct ynode
{
    int key;
    int tmax, tmin;
};

struct ob
{
    int x, y, temp;
};

// 构建完全二叉树（几乎是）
void construct(ob* obs, int lo, int hi, xnode ** tree , int rank)
{
    if(lo == hi) return;
    // 叶节点
    if(lo + 1 == hi)
    {
        tree[rank] = new xnode();
        tree[rank]->left = tree[rank]->right = tree[rank]->mi = obs[lo].x;
        // 叶节点的yTree的构建
        tree[rank]->yquery = buildYQuery(obs, lo, hi);
    }
    int mi = (lo + hi) >> 1;

    construct(obs,lo,mi,tree,lc(rank));
    construct(obs,mi,hi,tree,rc(rank));

    // 将obs的区间[lo,hi)按照y坐标进行归并排序。
    merge(obs, lo, mi, hi);
    
    // 创建节点，这里xTree节点的创建与yTree节点的创建有些不同。
    tree[rank] = new xnode();
    tree[rank]->left = obs[lo].x;
    tree[rank]->right = obs[hi-1].x;
    tree[rank]->mi = obs[mi].x;
    //
    
}

void merge(ob* obs,int lo, int mi, int hi)
{

}

ynode** buildYQuery(ob* obs, int lo , int hi)
{
    
}

void query(xnode** tree, int root, int lo, int hi)
{
    
}


// 报告子树，其实就是遍历子树，这里先简单采用递归
void report_subtree(xnode** tree, int root, int* tmax, int* tmin)
{
    
}

// 报告节点
void report_node(xnode **tree, int root, int *tmax, int *tmin)
{
    
}

int main()
{
    int A[100];
    construct(A,0,100,xtree,1);
    return 0;
}