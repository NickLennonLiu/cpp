#pragma once
#include "Node.h"
//#define DEBUG
#include "Queue.h"
#include "Stack.h"
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
    // 分离子树
    node* secede(node* src)
    {
        if (src->isFirstChild()) // 如果是第一个后代，需要更新parent的lc
        {
            src->parent->lc = src->nextSibling();
            if (src->nextSibling())
                src->nextSibling()->brother = nullptr;
        }
        else // 如果不是第一个后代，需要更新上一个兄弟节点的rc
        {
            src->prevSibling()->rc = src->rc;
            if (src->nextSibling())
                src->nextSibling()->brother = src->brother;
        }
        src->rc = nullptr;
        //updateAbove(src->parent);
        tagAbove(src->parent);
        return src;
    }
    // 将子树添加到dst的对应位置
    void insertSubtree(node* src, node* dst, int rank)
    {
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
        //updateAbove(dst);
        tagAbove(dst);
    }
    
    void tagAbove(node* x)
    {
        while(x)
        {
            x->lazytag = true;
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

    template <typename VST>
    void traverse_post(node* x, VST& func)
    {
        Stack<node*> post;
        Queue<node*> pre;
        if(!x) return;
        pre.enqueue(x);
        node* cur;
        while(!pre.empty())
        {
            cur = pre.dequeue();
            post.push(cur);
            node* ch = cur->firstChild();
            while(ch)
            {
                pre.enqueue(ch);
                ch = ch->nextSibling();
            }
        }
        while(!post.empty())
        {
            func(post.pop());
        }
    }

};
