#pragma once

#include "binNode.h"
#include "Stack.h"
#include "Queue.h"

template <typename T>
class binTree
{
    
public:
    binNodePosi(T) _root;    // 树根节点
    int _size;
    int _height;
    // 构造函数：空树
    binTree()
    : _size(0)
    , _height(0)
    {    }
    
    int size() const {return _size;}
    int height() const {return _height;}
    binNodePosi(T) root() const {return _root;}
    // 获得一个节点的兄弟
    binNodePosi(T) sibling(binNodePosi(T) x)
    {
        if(!x->parent) return nullptr;
        return (get(x)) ? x->parent->right : x->parent->left;
    }
    // 前序遍历
    template <typename VST>
    void traverse_pre(VST& func)
    {
        Stack<binNodePosi(T)> trav;
        if(!_root) return;
        trav.push(_root);
        while(!trav.empty())
        {
            binNodePosi(T) cur = trav.pop();
            func(cur->data);
            if(cur->right) trav.push(cur->right);
            if(cur->left) trav.push(cur->left);
        }
    }
    // 中序遍历
    template <typename VST>
    void traverse_in(VST &func)
    {
        Stack<binNodePosi(T)> trav;
        if (!_root)
            return;
        binNodePosi(T) cur = _root;
        while(cur || !trav.empty())
        {
            if (cur)
            {
                trav.push(cur);
                cur = cur->left;
            } else 
            {
                cur = trav.pop();
                func(cur->data);
                trav.push(cur->right);
            }
        }
    }
    // 后序遍历
    template <typename VST>
    void traverse_post(binNodePosi(T) x, VST &func)
    {
        Stack<binNodePosi(T)> S;
        if(x) S.push(x);
        while(!S.empty())
        {
            if(S.top() == x->parent)
                gotoLeftMostLeaf(S);
            x = S.pop();
            func(x->data);
        }
        if(!_root) return;
        traverse_post_recursive(func,_root);
    }
    // 层级遍历
    template <typename VST>
    void traverse_BFS(VST &func)
    {
        Queue<binNodePosi(T)> queue;
        queue.push_back(_root);
        while(!queue.empty())
        {
            binNodePosi(T) cur = queue.pop_front();
            if(cur)
            {
                func(cur->data);
                queue.push_back(cur->left);
                queue.push_back(cur->right);
            }
        }
    }
    // 析构函数，清空根子树
    ~binTree()
    {
        remove(_root);
    }
protected:
    void maintain()
    {
        //TODO
    }
    // return if x is the left child of its father
    bool get(binNodePosi(T) x)
    {
        if (!x->parent)
            return false;
        return x->parent->left == x;
    }
    // 递归实现后序遍历
    template <typename VST>
    void traverse_post_recursive(VST& func, binNodePosi(T) x)
    {
        if(!x) return;
        traverse_post_recursive(func,x->left);
        traverse_post_recursive(func,x->right);
        func(x);
    }
    // 清空子树
    void remove(binNodePosi(T) curNode)
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
    // 后序遍历所需，查找当前栈顶节点对应的最左端后代节点
    template <typename T> 
    void gotoLeftMostLeaf( Stack<binNodePosi(T)> & S)
    {
        while( binNodePosi(T) x = S.top())
        {
            if(x->left)
            {
                if(x->right)
                    S.push(x->right);
                S.push(x->left);
            } else
                S.push(x->right);
        }
        S.pop();
    }
};