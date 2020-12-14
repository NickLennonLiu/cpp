#pragma once
#include "Node.h"
#include "Queue.h"
#include "Stack.h"
#include <iostream>
using namespace std;

struct Tree
{
    node* nodes[1000001];
    node* _root;
    int _size;
    // 初始化，给n个节点分配内存
    void init(int size)
    {
        _size = size;
        for(int i = 1; i <= size; ++i)
        {
            nodes[i] = new node(i);
        }
        _root = nodes[1];
    }
    // 析构函数
    ~Tree()
    {
        for(int i = 1; i <= _size; ++i)
            delete nodes[i];
    }
    // 按序号获得节点
    node*& operator[](int rank)
    {
        return nodes[rank];
    }
    // 分离子树
    node* secede(node* src)
    {
        if(src->lazytag) src->update();
        if (src->isFirstChild()) // 如果是第一个后代，需要更新parent的lc
        {
            src->parent->lc = src->rc;
            if (src->rc)
                src->rc->brother = nullptr;
        }
        else // 如果不是第一个后代，需要更新上一个兄弟节点的rc
        {
            src->brother->rc = src->rc;
            if (src->rc)
                src->rc->brother = src->brother;
        }
        src->rc = nullptr;
        src->brother = nullptr;

        updateSize(src->parent, -(src->size));

        src->parent->lazytag = true;    // 分离子树后，立刻更新原先父节点的高度
        if(src->height + 1 > src->parent->getHeight())  // 根据父节点高度是否更新判断是否有必要向上标记tag
            tagAbove(src->parent);
        src->parent = nullptr;
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
        updateSize(dst, src->size);         // 无论如何都向上更新规模
        if(src->height + 1 > dst->height)   // 根据当前父节点的原先高度判断是否有必要更新高度
            tagAbove(dst);                  // 如果有必要，则沿祖先标记tag
    }
    
    // 将x及以上的都打上lazytag
    void tagAbove(node* x)
    {
        while(x)
        {
            if(x->lazytag) break;   // 如果x已经被打上lazytag，说明x的祖先都已经被打上了lazytag
            x->lazytag = true;
            x = x->parent;
        }
    }

    // 更新子树规模
    void updateSize(node* x, int delta)
    {
        while(x)
        {
            x->size += delta;
            x = x->parent;
        }
    }

    // 层级遍历
    template <typename VST>
    void bfs(node* x, VST& func)
    {
        Queue<node*> Q;
        if(x) Q.enqueue(x);
        while(!Q.empty())
        {
            x = Q.dequeue();
            func(x);
            node* c = x->lc;
            while(c)
            {
                Q.enqueue(c);
                c = c->nextSibling();
            }
        }
    }

    // 后序遍历
    template <typename VST>
    void traverse_post(node* x, VST& func, Stack<node*>& post, Queue<node*>& pre)
    {
        if(!x) return ;
        pre.enqueue(x);
        node* cur;
        int tempsize;
        while(!pre.empty())
        {
            tempsize = pre.size();
            while(tempsize--)
            {
                cur = pre.dequeue();
                post.push(cur);
                node* ch = cur->lc;
                while(ch)
                {
                    pre.enqueue(ch);
                    ch = ch->rc;
                }
            }
        }
        while(!post.empty())
        {
            func(post.pop());
        }
    }

};
