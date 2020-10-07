#pragma once
#include "binTree.h"


template <typename T>
class Splay : public binTree<T>
{
public:
    // return if x is x's parent's left child.
    
protected:
    void maintain(binNodePosi(T) x)
    {

    }
    void clear(binNodePosi(T) x)
    {

    }
    // 右旋
    void zig(binNodePosi(T) x)
    {
        if(x == _root) return;
        binNodePosi(T) father = x->parent;
        father->left = x->right;
        x->right->father = father;
        if(father->parent)
        {
            if (binTree<T>::get(father))
                father->parent->left = x;
            else 
                father->parent->right = x;
        }
        x->parent = father->parent;
        father->parent = x;
        x->right = father;
        maintain(father);
        maintain(x);
    }
    // 左旋
    void zag(binNodePosi(T) x)
    {
        if(x == _root) return;
        binNodePosi(T) father = x->parent;
        father->right = x->left;
        x->left->father = father;
        if(father->parent)
        {
            if(binTree<T>::get(father)) 
                father->parent->left = x;
            else 
                father->parent->right = x;
        }
        x->parent = father->parent;
        father->parent = x;
        x->left = father;
        maintain(father);
        maintain(x);
    }
    void splay(binNodePosi(T) x)
    {
        if(!x->parent || !x->parent->parent)
        {
            
        }
    }
};