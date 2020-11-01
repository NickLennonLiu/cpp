#pragma once
#include "List.h"

struct node
{
    // 成员
    int index;
    node* parent;
    List<node*> child;
    int size, height;

    node(int idx, node* parent = nullptr)
    : index(idx), size(1), height(0)
    , parent(parent)
    {
    }
    node* operator[](int n)  // 返回第n个后代
    {
        if(child[n] != child.end())
            return child[n]->data();
        return nullptr;
    }
    ListNode<node*>* nthChild(int n)
    {
        ListNode<node*>* ch = child.first();
        while(ch != child.end() && n--)
            ch = ch->nex;
        if(ch != child.end()) return ch;
        return nullptr;
    }

    // 获得子树规模
    int getSize()
    {
        return size;
    }
    int getHeight()
    {
        return height;
    }
    // 更新
    void update()
    {

    }
};