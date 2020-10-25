#pragma once

#include "ListNode.h"

struct List
{
    ListNode *header, *trailer;
    List()
    {
        header = new ListNode;  //创建头哨兵节点
        trailer = new ListNode; //创建尾哨兵节点
        header->nex = trailer;
        header->pre = nullptr;
        trailer->pre = header;
        trailer->nex = nullptr;
    }
    //List(char const* elems);
    ~List()
    {
        while(header)
        {
            ListNode* next = header->nex;
            delete header;
            header = next;
        }
    }
    inline ListNode* first() const {return header->nex;}
    inline ListNode* last() const {return trailer->pre;}
    void remove(ListNode* pos)
    {
        pos->pre->nex = pos->nex;
        pos->nex->pre = pos->pre;
        char e = pos->val;
        delete pos;
    }
    inline void insertAsFirst(const char& e){
        header->insertAsNext(e);
    }
    inline void insertAsLast(const char& e){
        trailer->insertAsPre(e);
    }
};