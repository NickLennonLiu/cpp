#include <stdio.h>
#include <cstring>
#include <iostream>
#include "stl/BST.h"
#include "stl/Splay.h"
using namespace std;


void print(int i)
{
    cout << i << " ";
}

struct LtNode
{
    LtNode *pre, *nex;
    char val;
};

LtNode list[];

int main()
{
    Splay<int> bst;
    bst.root()->data = 0;
    for(int i = 1;i < 10;i++)
    {
        bst.BST<int>::insert(i);
    }
    for(int i = -9;i;i++)
    {
        bst.BST<int>::insert(i);
    }
    bst.traverse_BFS(print);
    cout << endl;
    bst.zig(bst.root()->left);
    bst.traverse_BFS(print);
    LtNode *p;
    LtNode a;
    cout << sizeof(a) << endl << sizeof(p) << endl;
    
    return 0;
}