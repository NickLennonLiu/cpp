#pragma once

#define binNodePosi(T) binNode<T>*
typedef int Rank;

template <typename T>
class binNode
{
    
public:
    T data;
    binNodePosi(T) parent, left, right;

    binNode() : parent(NULL), left(NULL), right(NULL) {}
    binNode(T e, binNodePosi(T) parent = NULL, binNodePosi(T) left = NULL, binNodePosi(T) right = NULL)
    : parent(parent)
    , left(left)
    , right(right)
    {
        data = e;
    }
    binNodePosi(T) insertLeftChild(T& lc) { return left = new binNode(lc, this); }
    binNodePosi(T) insertLeftChild(T& rc) { return right = new binNode(rc, this); }
};