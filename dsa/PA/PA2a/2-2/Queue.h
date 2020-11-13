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
    void enqueue(const T e)
    {
        List<T>::insertAsLast(e);
    }
    T dequeue()
    {
        return List<T>::remove(List<T>::first());
    }
    ListNode<T>* front()
    {
        return List<T>::first();
    }
    ListNode<T> *rear()
    {
        return List<T>::last();
    }
};