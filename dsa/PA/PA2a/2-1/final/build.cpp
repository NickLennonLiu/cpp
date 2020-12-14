#include "Tree.h"
#include <stdio.h>

using namespace std;

Tree tree;
Stack<node*> post;
Queue<node*> pre;
int n,m;
int op;

// 寻找节点
inline node* findNode(Tree& tr)
{
    int path_len, rank;
    scanf("%d",&path_len);
    node* cur = tr._root, *nex;
    while(cur && path_len--)
    {
        scanf("%d",&rank);
        nex = (*cur)[rank];
        if(nex == nullptr)
            break;
        cur = nex;
    }
    if(path_len>0)
        while(path_len--)
            scanf("%*d");

    return cur;
}

// 根据直接后代来更新高度与规模（用于建树完成后的维护）
inline void simpleUpdate(node* x)
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

    // 树的高度的初始化 
    tree.traverse_post(tree._root, simpleUpdate,post, pre);

    for(int i = 0; i < m; ++i)
    {
        scanf("%d", &op);
        switch(op)
        {
            case 0: // 移动子树
            {
                node *src, *dst;

                src = findNode(tree);   // 确定源子树根节点位置
                tree.secede(src);       // 分离完成后
                dst = findNode(tree);   // 再进行目标节点的查找

                int rank;
                scanf("%d", &rank);

                tree.insertSubtree(src, dst, rank); // 按位置插入

                break;
            }
            case 1: // 询问子树高度
            {
                printf("%d\n", findNode(tree)->getHeight());
                break;
            }
            case 2: // 询问子树规模
            {
                printf("%d\n", findNode(tree)->getSize());
                break;
            }
        }
    }
    return 0;
}