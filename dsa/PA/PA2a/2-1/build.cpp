#include "Tree.h"
#include <iostream>
#include <stdio.h>

//#define DEBUG
using namespace std;

Tree tree;
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
    int path_len, rank, len;
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
            scanf("%d",&rank);
    #ifdef DEBUG
    cout << "~~~debug: found node: " << cur->index << endl;
    #endif

    return cur;
}

// 根据直接后代更新高度与规模（后序遍历用）
void simpleUpdate(node* x)
{
    node* ch = x->firstChild();
    int height = 0;
    int size = 1;
    while(ch)
    {
        height = (height > (ch->height + 1)) ? height : (ch->height + 1);
        size += ch->size;
        ch = ch->nextSibling();
    }
    x->size = size;
    x->height = height;
}

int main()
{
    scanf("%d %d",&n,&m);
    tree.init(n);
    for(int i = 1; i <= n; ++i)  // 多叉树的初始化
    {
        int l, rank;
        scanf("%d",&l);
        if(!l)
            continue;
        // 插入firstChild
        scanf("%d", &rank);
        tree.nodes[i]->lc = tree.nodes[rank];       // set firstChild
        tree.nodes[rank]->parent = tree.nodes[i];   // set parent

        // 依次插入nextSibling
        node* cur = tree.nodes[rank];
        while(--l)
        {
            scanf("%d", &rank);
            cur->rc = tree.nodes[rank];             // set nextSibling
            tree.nodes[rank]->parent = tree.nodes[i];   // set parent
            tree.nodes[rank]->brother = cur;            // set brother
            cur = cur->rc;                          
        }
    }

    tree.traverse_post(tree._root, simpleUpdate);

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

                src = findNode(tree);
                tree.secede(src);
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