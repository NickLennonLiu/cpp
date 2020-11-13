#pragma once

#include "ListNode.h"

template <typename T>
class List
{
    ListNode<T> *header, *trailer;
    int len;
public:
    List()
    : len(0)
    {
        header = new ListNode<T>;  //创建头哨兵节点
        trailer = new ListNode<T>; //创建尾哨兵节点
        header->nex = trailer;
        header->pre = nullptr;
        trailer->pre = header;
        trailer->nex = nullptr;
    }
    List(ListNode<T>* pos, int n)
    {
        header = new ListNode<T>;  //创建头哨兵节点
        trailer = new ListNode<T>; //创建尾哨兵节点
        
        
    }
    //List(T const* elems);
    ~List()
    {
        while(header)
        {
            ListNode<T>* next = header->nex;
            delete header;
            header = next;
        }
    }
    int size() const {return len;}
    bool empty() const {return !len;}
    ListNode<T>* insert(ListNode<T>* pos,const T &e)
    {
        ++len;
        return pos->insertAsPre(e);
    }
    ListNode<T>* first() const {return header->nex;}
    ListNode<T>* last() const {return trailer->pre;}
    ListNode<T>* end() const {return trailer;}
    T remove(ListNode<T>* pos)
    {
        len--;
        pos->pre->nex = pos->next();
        pos->nex->pre = pos->prev();
        T e = pos->data();
        delete pos;
        return e;
    }
    ListNode<T>* insertAsFirst(const T& e){
        ++len;
        return header->insertAsNext(e);
    }
    ListNode<T>* insertAsLast(const T& e){
        ++len;
        return trailer->insertAsPre(e);
    }
    void sort();
protected:
    void merge(ListNode<T>* B);
};

template <typename T>
void List<T>::sort()
{

}

template <typename T>
void List<T>::merge(ListNode<T>* B)
{

}