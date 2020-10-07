#pragma once

struct ListNode
{
    char val;
    ListNode *pre, *nex;
    ListNode()
    : pre(nullptr)
    , nex(nullptr)
    {}
    ListNode(char const& e, ListNode* prev=nullptr, ListNode* next=nullptr)
    : pre(prev)
    , nex(next)
    , val(e)
    {}
    inline void insertAsPre(char const& e)
    {
        ListNode* newpre = new ListNode(e,pre,this);
        pre->nex = newpre; pre = newpre;
    }
    inline void insertAsNext(char const& e)
    {
        ListNode* newnex = new ListNode(e,this,nex);
        nex->pre = newnex; nex = newnex;
    }
};