#pragma once
#include "Node.h"
//#define DEBUG
#include "Queue.h"
#include "Stack.h"
#include "List.h"
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
    node* secede(node* src, ListNode<node*>* pos)
    {
        src->parent->child.remove(pos);
        updateAbove(src->parent,src->height, -1, -(src->size));
        src->parent = nullptr;
        return src;
    }
    // 将子树添加到dst的对应位置
    void insertSubtree(node* src, node* dst, int rank)
    {
        dst->child.insert(dst->child[rank], src);
        src->parent = dst;
        updateAbove(dst,-1, src->height, src->size);
    }
    // osth：某一个子树原来的高度；nsth：那个子树新的高度；ds：规模的变化
    void updateAbove(node* x,int osth, int nsth, int ds)
    {
        while(x)
        {
            x->size += ds;
            updateHeight(x, osth, nsth);
            x = x->parent;
        }
    }
    void updateHeight(node* x,int& osth, int& nsth)
    {
        
        if(nsth + 1 >= x->height)
        {
            osth = x->height;
            x->height = nsth + 1;
            ++nsth;
        }
        else if(osth != x->height - 1)
        {
            osth = nsth = x->height;
        }
        else
        {
            int height = 0;
            ListNode<node*>* cur = x->child.first();
            while(cur != x->child.end())
            {
                height = (height >= cur->data()->height) ? height : cur->data()->height;
                cur = cur->next();
            }
            osth = x->height;
            nsth = x->height = height;
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
            int size = Q.size();
            while(size--)
            {
                node* cur = Q.dequeue();
                func(cur);
                ListNode<node*> *ch = cur->child.first();
                while(ch != cur->child.end())
                {
                    Q.enqueue(ch->data());
                    ch = ch->nex;
                }
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
                ListNode<node*>* ch = cur->child.first();
                while(ch != cur->child.end())
                {
                    pre.enqueue(ch->data());
                    ch = ch->nex;
                }
            }
        }
        while(!post.empty())
        {
            func(post.pop());
        }
    }

};
