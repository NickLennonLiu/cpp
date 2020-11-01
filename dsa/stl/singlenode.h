#pragma once

template <typename T>
struct myNode
{
    T val;
    myNode<T>* next;
    myNode()
    : next(nullptr)
    {}
    myNode(T const & e)
    : next(nullptr)
    , val(e)
    {}
    myNode<T>* insertAsPre(const T& e)
    {
        myNode<T>* newme = new myNode<T>(val);
        newme->next = next;
        val = e;
        next = newme;
        return this;
    }
    myNode<T>* insertAsNext(const T& e)
    {
        myNode<T> *newnode = new myNode<T>(e);
        newnode->next = next;
        return next = newnode;
    }
};