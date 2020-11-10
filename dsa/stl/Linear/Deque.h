#pragma once

#include "List.h"

template <typename T>
class Deque : public List<T>
{
public:
    Deque()
        : List<T>()
    {
    }
    ~Deque()
    {
        List<T>::~List();
    }
    void push_back(const T e)
    {
        List<T>::insertAsLast(e);
    }
    void push_front(const T e)
    {
        List<T>::insertAsFirst(e);
    }
    T pop_front()
    {
        return List<T>::remove(List<T>::first());
    }
    T pop_back()
    {
        return List<T>::remove(List<T>::last());
    }
    T front()
    {
        return List<T>::first()->ListNode<T>::data();
    }
    T back()
    {
        return List<T>::last()->ListNode<T>::data();
    }
};