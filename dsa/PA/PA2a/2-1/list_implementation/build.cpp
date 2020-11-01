#include "Tree.h"
#include <iostream>
#include <stdio.h>

//#define DEBUG
using namespace std;

Tree tree;
Stack<node*> post;
Queue<node*> pre;
int n,m;
int op;

// 测试用： 查看节点的信息（高度与子树规模）
void viewNode(node* x)
{
    cout << "Node: " << x->index << " " << x->height << " " << x->size << endl;
}

// 测试用：层次遍历多叉树，输出子树的高度与规模
void debugBFS(Tree& tr)
{
    cout << "---debug: bfs tree" << endl;
    tree.bfs(tr._root, viewNode);
    cout << "---" << endl;
}

// 寻找节点
node* findNode(Tree& tr)
{
    int path_len, rank;
    scanf("%d",&path_len);
    node* cur = tr._root, *nex;
    while(path_len--)
    {
        scanf("%d",&rank);
        nex = (*cur)[rank];
        if(nex != nullptr)
            cur = nex;
        else
            break;
    }
    if(path_len>0)
        while(path_len--)
            scanf("%*d");
    #ifdef DEBUG
    cout << "~~~debug: found node: " << cur->index << endl;
    #endif

    return cur;
}

// 寻找节点, 并保留其对应父节点的列表节点
node *findNode(Tree &tr, ListNode<node*>*& pos)
{
    int path_len, rank;
    scanf("%d", &path_len);

    node *cur = tr._root, *nex;
    ListNode<node*>* old = pos;

    while (path_len--)
    {
        scanf("%d", &rank);
        pos = cur->nthChild(rank);
        if(pos) {
            old = pos;
            cur = pos->data();
        } else {
            pos = old;
            break;
        }
    }
    if (path_len > 0)
        while (path_len--)
            scanf("%*d");
    #ifdef DEBUG
        cout << "~~~debug: found node: " << cur->index << endl;
    #endif

    return cur;
}

// 根据直接后代更新高度与规模（后序遍历用）
inline void simpleUpdate(node* x)
{
    x->size = 1;
    x->height = 0;
    ListNode<node*>* cur = x->child.first();
    while(cur != x->child.end())
    {
        x->size += cur->data()->size;
        x->height = (x->height > cur->data()->height + 1) ? x->height : cur->data()->height + 1;
        cur = cur->nex;
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    tree.init(n);
    for(int i = 1; i <= n; ++i)  // 多叉树的初始化
    {
        int l, rank;
        scanf("%d",&l);
        while(l--)
        {
            scanf("%d", &rank);
            tree.nodes[i]->child.insertAsLast(tree.nodes[rank]);
            tree.nodes[rank]->parent = tree.nodes[i];
        }
    }

    tree.traverse_post(tree._root, simpleUpdate, post, pre);

    #ifdef DEBUG
    debugBFS(tree);
    #endif

    for(int i = 0; i < m; ++i)
    {
        scanf("%d", &op);
        switch(op)
        {
            case 0:
            {
                node *src, *dst;
                ListNode<node*>* src_listNode;

                src = findNode(tree, src_listNode);

                tree.secede(src, src_listNode);
                #ifdef DEBUG
                debugBFS(tree);
                #endif

                dst = findNode(tree);

                int rank;
                scanf("%d", &rank);

                tree.insertSubtree(src, dst, rank);

                #ifdef DEBUG
                debugBFS(tree);
                #endif

                break;
            }
            case 1:
            {
                printf("%d\n", findNode(tree)->getHeight());
                break;
            }
            case 2:
            {
                printf("%d\n", findNode(tree)->getSize());
                break;
            }
        }
    }
    return 0;
}