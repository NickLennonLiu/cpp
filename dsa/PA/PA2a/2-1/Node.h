#pragma once

struct node
{
    int index;
    node *parent, *lc, *rc; // 父亲节点、FirstChild、NextSibling
    node *brother;
    int size;   // 子树规模
    int height; // 高度
    bool lazytag;
    node(int idx, node* parent = nullptr, node* brother = nullptr)
    : index(idx), size(1), height(0), lc(nullptr)
    , rc(nullptr), parent(parent), brother(brother)
    , lazytag(false)
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
        //if(!child) return this; // 如果找不到第n个后代，返回自身
        return child;   // 如果找不到就返回空指针
    }
    bool isFirstChild()
    {
        return parent && (parent->lc == this);
    }
    int getSize()
    {
        if(lazytag) update();
        return size;
    }
    int getHeight()
    {
        if(lazytag) update();
        return height;
    }
    void update()
    {
        lazytag = false;
        node* ch = firstChild();
        height = 0;
        int newsize = 1;
        while(ch)
        {
            newsize += ch->getSize();
            height = (height > ch->getHeight() + 1) ? height : ch->getHeight() + 1;
            ch = ch->nextSibling();
        }
        size = newsize;
    }
};