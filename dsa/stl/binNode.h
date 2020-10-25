#pragma once

#define binNodePosi(T) binNode<T>*
typedef int Rank;

template <typename T>
class binNode
{
    
public:
    T data;
    binNode<T> *parent, *left, *right;
    int subtree_size;
    int cnt;

    binNode() : parent(NULL), left(NULL), right(NULL) {}
    binNode(T e, binNodePosi(T) parent = NULL, binNodePosi(T) left = NULL, binNodePosi(T) right = NULL, int size = 1)
    : parent(parent)
    , left(left)
    , right(right)
    , subtree_size(size)
    {
        data = e;
    }
    binNodePosi(T) insertLeftChild(const T& lc) 
    { 
        if(left)
        {
            subtree_size -= left->subtree_size;
            delete left;
        }
        ++subtree_size;
        return left = new binNode(lc, this); 
    }
    binNodePosi(T) insertRightChild(const T& rc) 
    { 
        if(right)
        {
            subtree_size -= right->subtree_size;
            delete right;
        }
        return right = new binNode(rc, this); 
    }
};