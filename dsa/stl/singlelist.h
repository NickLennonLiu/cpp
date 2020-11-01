#pragma once 
#include "singlenode.h"

template <typename T>
struct List
{
    myNode<T> *header, *trailer;
    int len;
    List()
    : len(0)
    {
        header = new myNode<T>;
        trailer = new myNode<T>;
        header->next = trailer;
        trailer->next = nullptr;
    }
    ~List()
    {
        while(header)
        {
            myNode<T> *nex = header->next;
            delete header;
            header = nex;
        }
    }
    int size() const {return len;}
    bool empty() const {return !len;}
    myNode<T>* insert(myNode<T>* x, T const& e)
    {
        ++len;
        return x->insertAsPre(e);
    }
    T remove(myNode<T>* x)
    {
        T e = x->val;
        --len;
        x->val = x->next->val;
        myNode<T>* temp = x->next->next;
        delete x->next;
        x->next = temp;
        return e;
    }
    myNode<T>* insertAsFirst(const T& e)
    {
        ++len;
        return header->insertAsNext(e);
    }
    myNode<T>* insertAsLast(const T& e)
    {
        ++len;
        myNode<T>* newnode = trailer->insertAsPre(e);
        trailer = trailer->next;
        return newnode;
    }
    myNode<T>* operator[](int n)
    {
        myNode<T>* cur = header->next;
        while(cur != trailer && n--)
            cur = cur->next;
        return cur;
    }
};