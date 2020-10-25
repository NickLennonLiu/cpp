#pragma once
#include "Node.h"
//#define DEBUG
#include "Queue.h"
#include <iostream>
using namespace std;

struct Tree
{
    node* nodes[1000001];
    node* _root;
    void init(int size)
    {
        for(int i = 1; i <= size; i++)
        {
            nodes[i] = new node(i);
        }
        _root = nodes[1];
    }
    node*& operator[](int rank)
    {
        return nodes[rank];
    }
    node* secede(node* src)
    {
        if (src->isFirstChild()) // 如果是第一个后代，需要更新parent的lc
        {
            src->parent->lc = src->nextSibling();
            if (src->nextSibling())
                src->nextSibling()->brother = src->brother;
        }
        else // 如果不是第一个后代，需要更新上一个兄弟节点的rc
        {
            src->prevSibling()->rc = src->rc;
            if (src->nextSibling())
                src->nextSibling()->brother = src->brother;
        }
        src->rc = nullptr;
        updateAbove(src->parent);
        return src;
    }
    node* insertSubtree(node* src, node* dst, int rank)
    {
        // 将子树添加到dst的对应位置
        src->parent = dst;
        if (!rank)
        {
            if (dst->lc)
            {
                dst->lc->brother = src;
                src->rc = dst->lc;
            }
            dst->lc = src;
            src->brother = nullptr;
        }
        else
        {
            node *pre = (*dst)[rank - 1];
            if (pre->rc)
                pre->rc->brother = src;
            src->rc = pre->rc;
            pre->rc = src;
            src->brother = pre;
        }
        updateAbove(dst);
    }
    void moveSubtree(node* src, node* dst,int rank)
    {
        // 从原来的位置删除子树
        if(src->isFirstChild())                     // 如果是第一个后代，需要更新parent的lc
        {
            src->parent->lc = src->nextSibling();
            if(src->nextSibling()) src->nextSibling()->brother = src->brother;
        } else                                      // 如果不是第一个后代，需要更新上一个兄弟节点的rc
        {
            src->prevSibling()->rc = src->rc;
            if(src->nextSibling()) src->nextSibling()->brother = src->brother;
        }
        src->rc = nullptr;
        updateAbove(src->parent);
        
        // 将子树添加到dst的对应位置
        src->parent = dst;
        if(!rank)
        {
            if(dst->lc) 
            {
                dst->lc->brother = src;
                src->rc = dst->lc;
            }
            dst->lc = src;
            src->brother = nullptr;
        }else
        {
            node* pre = (*dst)[rank-1];
            if(pre->rc) pre->rc->brother = src;
            src->rc = pre->rc;
            pre->rc = src;
            src->brother = pre;
        }
        updateAbove(dst);
    }
    int update(node* x)
    {
        int height = 0;
        int newsize = 1;
        node* child = x->firstChild();
        while(child)
        {
            newsize += child->size;
            height = (height >= (child->height + 1)) ? height : (child->height + 1);
            child = child->nextSibling();
        }
        if(x->height == height && x->size == newsize) return 0;
        x->height = height;
        x->size = newsize;

        return 1;
    }
    void updateAbove(node* x)
    {
        while(x)
        {
            if(!update(x)) break;
            x = x->parent; 
        }
    }

    
    template <typename VST>
    void bfs(node* x, VST& func)
    {
        Queue<node*> Q;
        if(x) Q.enqueue(x);
        while(!Q.empty())
        {
            x = Q.dequeue();
            func(x);
            node* c = x->firstChild();
            while(c)
            {
                Q.enqueue(c);
                c = c->nextSibling();
            }
        }
    }
    
};
