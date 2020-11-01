#pragma once

#include "List.h"

template <typename T>
class Stack : public List<T>{
public:
    Stack()
    : List<T>()
    {
    }
    ~Stack()
    {
        List<T>::~List();
    }
    inline void push(const T e){
        List<T>::insertAsLast(e);
    }
    inline T top()
    {
        return List<T>::last()->ListNode<T>::data();
    }
    inline T pop()
    {
        return List<T>::remove(List<T>::last());
    }
};