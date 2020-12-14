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
        if(n < 0) return nullptr;
        node* child = lc;
        while(child && n--)
            child = child->rc;
        return child;   // 如果找不到就返回空指针
    }
    // 判断是否为第一个后代节点
    bool isFirstChild()
    {
        return parent && (parent->lc == this);
    }
    // 获得子树规模
    int getSize()
    {
        return size;
    }
    int getHeight()
    {
        if(lazytag) update();   // 如果需要更新则先更新
        return height;
    }
    // 更新高度
    void update()
    {
        lazytag = false;    // 更新tag状态
        node* ch = lc;
        height = 0;
        int temp;
        while(ch)   // 递归维护所有后代的高度
        {
            temp = ch->getHeight() + 1;
            height = (height > temp) ? height : temp;
            ch = ch->rc;
        }
    }
};