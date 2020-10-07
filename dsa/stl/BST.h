#pragma once 
#include "binTree.h"

template <typename T>
class BST : public binTree<T>
{

public:
    BST()
    : binTree<T>()
    {}

    binNodePosi(T) insert(const T& e)
    {
        binNodePosi(T) cur = _root;
        while(cur)
        {
            if(cur->data > e) cur = cur->left;
            else if(cur->data < e) cur = cur->right;
            else break;
        }
        return cur;
    }
    binNodePosi(T) find(const T& e)
    {
        binNodePosi(T) cur = _root;
        while(cur)
        {
            if(cur->data > e) cur = cur->left;
            else if(cur->data < e) cur = cur->right;
            else break;
        }
        return cur;
    }

};