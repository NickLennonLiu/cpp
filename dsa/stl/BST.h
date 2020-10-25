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
        binNode<T> *cur = binTree<T>::_root, *temp = binTree<T>::_root;
        while(cur)
        {
            if(cur->data > e) 
            {
                temp = cur;
                cur = cur->left;
            }
            else if(cur->data < e) 
            {
                temp = cur;
                cur = cur->right;
            }
            else break;
        }
        if(cur) 
        {
            ++cur->cnt;
            return cur;
        }
        else 
        {
            if(temp->data < e) return temp->insertRightChild(e);
            else return temp->insertLeftChild(e);
        }
    }
    binNodePosi(T) find(const T& e)
    {
        binNodePosi(T) cur = binTree<T>::_root;
        while(cur)
        {
            if(cur->data > e) cur = cur->left;
            else if(cur->data < e) cur = cur->right;
            else break;
        }
        return cur;
    }

};