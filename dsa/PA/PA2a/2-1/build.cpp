#include "Tree.h"
#include <iostream>

//#define DEBUG
using namespace std;

Tree tree;
int n,m;
int op;

void viewNode(node* x)
{
    cout << "Node: " << x->index << " " << x->height << " " << x->size << endl;
}

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
                //int src_depth = findNode(tree, src);
                //int dst_depth = findNode(tree, dst);
                src = findNode(tree);

                tree.secede(src);

                dst = findNode(tree);
                int rank;
                cin >> rank;
                
                tree.insertSubtree(src, dst, rank);

                //tree.moveSubtree(src, dst, rank);
                
                /*
                if(src_depth > dst_depth)
                {
                    tree.updateAbove(src_fa);
                    tree.updateAbove(dst);
                }
                else
                {
                    tree.updateAbove(dst);
                    tree.updateAbove(src_fa);
                }
                */

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
                cout << findNode(tree)->height << endl;
                break;
            }
            case 2:
            {
                cout << findNode(tree)->size << endl;
                break;
            }
        }
    }
    return 0;
}