#pragma once

#include "List.h"

template <typename T>
class Queue : public List<T>
{
public:
    Queue()
        : List<T>()
    {
    }
    ~Queue()
    {
        List<T>::~List();
    }
    inline void enqueue(const T e)
    {
        List<T>::insertAsLast(e);
    }
    inline T dequeue()
    {
        return List<T>::remove(List<T>::first());
    }
    inline ListNode<T>* front()
    {
        return List<T>::first();
    }
    inline ListNode<T> *rear()
    {
        return List<T>::last();
    }
};