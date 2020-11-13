#pragma once

template <typename T>
class ListNode
{
    
public:
    T val;
    ListNode<T> *pre, *nex;
    ListNode()
    : pre(nullptr)
    , nex(nullptr)
    {}
    ListNode(T const& e, ListNode<T>* prev=nullptr, ListNode<T>* next=nullptr)
    : pre(prev)
    , nex(next)
    , val(e)
    {}
    ListNode<T>* insertAsPre(T const& e)
    {
        ListNode<T>* newpre = new ListNode<T>(e,pre,this);
        pre->nex = newpre; pre = newpre;
        return newpre;
    }
    ListNode<T>* insertAsNext(T const& e)
    {
        ListNode<T>* newnex = new ListNode<T>(e,this,nex);
        nex->pre = newnex; nex = newnex;
        return newnex;
    }
    ListNode<T>* next() const {return nex;}
    ListNode<T>* prev() const {return pre;}
    T data() const {return val;}
};