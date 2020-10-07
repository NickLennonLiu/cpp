#pragma once

#include "binNode.h"
#include "Stack.cpp"

template <typename T>
class binTree
{
    binNodePosi(T) _root;    // 树根节点
public:
    binNodePosi(T) root() const {return _root;}
    binNodePosi(T) sibling(binNodePosi(T) x)
    {
        if(!x->parent) return nullptr;
        return (get(x)) ? x->parent->right : x->parent->left;
    }
    binTree() : _root(NULL){}
    ~binTree()
    {
        remove(_root);
    }
protected:
    // return if x is the left child of its father
    bool get(binNodePosi(T) x)
    {
        if (!x->parent)
            return false;
        return x->parent->left == x;
    }
    // clear the subtree of which the root is curNode
    int remove(binNodePosi(T) curNode)
    {
        Stack<binNodePosi(T)> rmstack;
        rmstack.push(curNode);
        while(!rmstack.empty())
        {
            binNodePosi(T) cur = rmstack.pop();
            if(cur->left) rmstack.push(cur->left);
            if(cur->right) rmstack.push(cur->right);
            delete cur;
        }
    }
};