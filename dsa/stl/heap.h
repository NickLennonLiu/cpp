#pragma once
#include "binTree.h"

template <typename T>
class maxHeap : public binTree<T>
{
    protected:
        void maxHeapify(binNodePosi(T) root);
        void buildMaxHeap(T* elems, Rank n);
        void heapSort();
        binNodePosi(T) Max();
        binNodePosi(T) insert(T& elem);
        binNodePosi(T) last();        
};