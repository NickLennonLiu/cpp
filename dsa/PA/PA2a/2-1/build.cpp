#include "Tree.h"
#include <iostream>

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

// 寻找节点
node* findNode(Tree& tr)
{
    int path_len, rank, len;
    cin >> path_len;
    node* cur = tr._root;
    while(path_len--)
    {
        cin >> rank;
        cur = (*cur)[rank];
    }
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
    cin >> n >> m;
    tree.init(n);
    for(int i = 1; i <= n; ++i)  // 多叉树的初始化
    {
        int l, rank;
        cin >> l;
        if(!l)
        {
            //tree.updateAbove(tree.nodes[i]->parent);
            continue;
        }
        // 插入firstChild
        cin >> rank;
        tree.nodes[i]->lc = tree.nodes[rank];       // set firstChild
        tree.nodes[rank]->parent = tree.nodes[i];   // set parent

        // 依次插入nextSibling
        node* cur = tree.nodes[rank];
        while(--l)
        {
            cin >> rank;
            cur->rc = tree.nodes[rank];             // set nextSibling
            tree.nodes[rank]->parent = tree.nodes[i];   // set parent
            tree.nodes[rank]->brother = cur;            // set brother
            cur = cur->rc;                          
        }
    }

    tree.traverse_post(tree._root, simpleUpdate);

    #ifdef DEBUG
    // debug
    cout << "---debug: bfs tree" << endl;
    tree.bfs(tree._root, viewNode);
    cout << "---" << endl;
    #endif

    for(int i = 0; i < m; ++i)
    {
        cin >> op;
        switch(op)
        {
            case 0:
            {
                node *src, *dst;

                src = findNode(tree);
                
                tree.secede(src);

                dst = findNode(tree);

                int rank;
                cin >> rank;
                
                tree.insertSubtree(src, dst, rank);

                #ifdef DEBUG
                // debug
                cout << "---debug: bfs tree" << endl;
                tree.bfs(tree._root, viewNode);
                cout << "---" << endl;
                #endif

                break;
            }
            case 1:
            {
                cout << findNode(tree)->getHeight() << endl;
                break;
            }
            case 2:
            {
                cout << findNode(tree)->getSize() << endl;
                break;
            }
        }
    }
    return 0;
}