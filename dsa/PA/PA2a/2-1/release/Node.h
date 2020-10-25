#pragma once

struct node
{
    int index;
    node *parent, *lc, *rc; // 父亲节点、FirstChild、NextSibling
    node *brother;
    int size;   // 子树规模
    int height; // 高度
    node(int idx, node* parent = nullptr, node* brother = nullptr)
    : index(idx), size(1), height(0), lc(nullptr)
    , rc(nullptr), parent(parent), brother(brother)
    {
    }
    node* firstChild() const {return lc;}   // 第一个后代
    node* nextSibling() const {return rc;}  // 下一个兄弟节点
    node* prevSibling() const {return brother;} // 上一个兄弟节点
    node* operator[](int n)  // 返回第n个后代
    {
        node* child = lc;
        while(child && n--)
            child = child->rc;
        if(!child) return this;
        return child;
    }
    bool isFirstChild()
    {
        return parent && (parent->lc == this);
    }
};