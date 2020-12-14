#include "Linear/Vector.h"
#include "Trees/binTree.h"

#define nmax 100000
#define parent(x) ((x - 1) >> 1)
#define lc(x) ((x << 1) | 1)
#define rc(x) ((x + 1) << 1)

template <typename T>
void swap(T& a, T& b)
{
    T t = a;
    a = b;
    b = t;
}

template <typename T> struct PQ
{
    virtual void insert(T)  = 0;
    virtual T getMax() = 0;
    virtual T delMax() = 0;
};

template <typename T> 
struct PQ_ComplHeap : public PQ<T>, public Vector<T> 
{
    PQ_ComplHeap(T *A, int n)
    {
        Vector<T>::copyFrom(A, 0, n);
        heapify(Vector<T>::_elem, n);
    }
    void insert(T e)
    {
        Vector<T>::insert(e);
        percolateUp(Vector<T>::_elem, Vector<T>::_size - 1);
    }
    T getMax()
    {
        return Vector<T>::_elem[0];
    }
    T delMax()
    {
        T maxElem = Vector<T>::_elem[0];
        Vector<T>::_elem[0] = Vector<T>::_elem[--Vector<T>::_size];
        percolateDown(Vector<T>::_elem, Vector<T>::_size, 0);
        return maxElem;
    }
    int ProperParent(T *A, int n, int i)
    {
        int re = i;
        if(lc(i) < n && A[lc(i)] > A[re]) re = lc(i);
        if(rc(i) < n && A[rc(i)] > A[re]) re = rc(i);
        return re;
    }
    int percolateDown(T* A, int n, int i)
    {
        int j;
        while(i != (j = ProperParent(A, n, i)))
        {
            swap(A[i], A[j]);
            i = j;
        }
        return i;
    }
    int percolateUp(T* A, int i)
    {
        while(0 < i)
        {
            int j = parent(i);
            if(A[i] < A[j]) break;
            swap(A[i], A[j]);
            i = j;
        }
        return i;
    }
    void heapify(T* A, int n)
    {
        for(int i = n/2 - 1; 0 <= i; i--)
            percolateDown(A, n, i);
    }
};

template <typename T>
static binNodePosi(T) merge(binNodePosi(T) a, binNodePosi(T) b)
{
    if(!a) return b;
    if(!b) return a;
    if(a->data < b->data) swap(b ,a);
    a->rc = merge(a->rc, b);
    a->rc->parent = a;
    if (!a->lc || a->lc->binNode<T>::npl < a->rc->binNode<T>::npl)
        swap(a->lc, a->rc);
    a->binNode<T>::npl = a->rc ? 1 + a->rc->binNode<T>::npl : 1;
    return a;
}

template <typename T>
class PQ_LeftHeap : public PQ<T> , public binTree<T>
{
public:
    PQ_LeftHeap(T *A, int n)
    {
        for(int i = 0; i < n; ++i)
            insert(A[i]);
    }
    T getMax() { return binTree<T> ::_root->binNode<T>::data; }
    void insert(T e)
    {
        binTree<T>::_root = merge(binTree<T>::_root, new binNode<T>(e, nullptr));
        binTree<T>::_size++;
    }
    T delMax()
    {
        binNodePosi(T) lHeap = binTree<T>::_root->lc;
        if(lHeap) lHeap->parent = nullptr;
        binNodePosi(T) rHeap = binTree<T>::_root->rc;
        if(rHeap) rHeap->parent = nullptr;
        T e = binTree<T>::_root->data;
        delete binTree<T>::_root;
        binTree<T>::_size--;
        binTree<T>::_root = merge(lHeap, rHeap);
        return e;
    }
};