#pragma once
#include "Queue.h"

template <typename T>
class Queap : public Queue<T>
{
    Queue<T> P, Q;
public:
    T dequeue()
    {
        P.dequeue();
        return Q.dequeue();
    } //O(1)
    void enqueue(const T& e)
    {
        Q.enqueue(e);
        P.enqueue(e);
        for (ListNode<T>* x = P.rear(); x && (x->val <= e); x = x->pre) //最坏情况O(n)
            x->val = e;
    }
    T getMax()
    {
        return P.front()->data();
    }
};