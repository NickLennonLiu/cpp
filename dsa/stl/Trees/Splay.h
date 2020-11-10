#pragma once
#include "binTree.h"


template <typename T>
class Splay : public BST<T>
{
public:
    Splay()
    : BST<T>()
    {}

    void maintain(binNodePosi(T) x)
    {
        if(!x->parent) binTree<T>::_root = x;
        x->subtree_size = 1;
        if(x->left) x->subtree_size += x->left->subtree_size;
        if(x->right) x->subtree_size += x->right->subtree_size;
    }
    void clear(binNodePosi(T) x)
    {
        delete x;
    }
    // 右旋
    void zig(binNodePosi(T) x)
    {
        if(x == binTree<T>::_root) return;
        binNodePosi(T) father = x->parent;
        father->left = x->right;
        x->right->parent = father;
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
        if(x == binTree<T>::_root) return;
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
        if(!x->parent) return;
        if(!x->parent->parent)
        {
           get(x) ? zig(x) : zag(x); 
        }
        if(get(x->parent) ^ get(x))
        {
            get(x) ? zig(x) : zag(x);
            get(x) ? zig(x) : zag(x);
        }
        else 
        {
            get(x->parent) ? zig(x->parent) : zag(x->parent);
            get(x->parent) ? zig(x) : zag(x);
        }
    }
    binNodePosi(T) insert(const T& e)
    {

    }
};