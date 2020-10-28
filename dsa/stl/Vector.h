#pragma once

#define DEFAULT_CAPACITY 16

template <typename T>
class Vector
{
    
public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
    {
        _elem = new T[_capacity = c];
        for(_size = 0; _size < s; ++_size)
            _elem[_size] = v;
    }
    Vector(T const * A, int lo, int hi)
    {
        copyFrom(A,lo,hi);
    }
    Vector(Vector<T> const& V)
    {
        copyFrom(V._elem, 0, V._size);
    }
    Vector(Vector<T> const& V,int lo, int hi)
    {
        copyFrom(V._elem, lo, hi);
    }
    int size() const {return _size;}
    int capacity() const {return _capacity;}
    bool empty() const {return !_size;}
    int insert(T const& e, int rank = 0)
    {
        expand();
        for(int i = _size; i > rank; --i)
            _elem[i] = _elem[i-1];
        _elem[rank] = e;
        ++_size;
        return rank;
    }
    T remove(int rank)
    {
        T old = _elem[rank];
        remove(rank, rank+1);
        return old;
    }
    int remove(int lo, int hi)
    {
        if( lo == hi) return;
        while(hi < _size)
            _elem[lo++] = _elem[hi++];
        _size = lo;
        shrink();
        return hi - lo;
    }
    int find(T const& e, int lo = 0, int hi = _size);
    int search(T const& e, int lo = 0, int hi = _size);
protected:
    T *_elem;
    int _size, _capacity;
    void copyFrom(T const* A, int lo, int hi);
    void expand();
    void shrink();
};

template <typename T>
void Vector<T>::copyFrom(T const* A, int lo, int hi)
{
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while(lo < hi)
        _elem[_size++] = A[lo++];
}

template <typename T>
void Vector<T>::expand()
{
    if(_size < _capacity) return;
    if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem; _elem = new T[_capacity <<= 1];
    for(int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete [] oldElem;
}

template <typename T>
void Vector<T>::shrink()
{
    if(_capacity < DEFAULT_CAPACITY << 1) return;
    if(_size << 2 > _capacity) return;
    T* oldElem = _elem; _elem = new T[_capacity >>= 1];
    for(int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete [] oldElem;
}

template <typename T>
int Vector<T>::find(T const& e, int lo, int hi)
{
    while(hi-- > lo)
    {
        if(_elem[hi] == e)
            break;
    }
    return hi;
}

template <typename T>
int Vector<T>::search(T const &e, int lo, int hi)
{
    if(lo == hi) return lo;
    int mid;
    while(lo < hi)
    {  
        mid = (lo + hi) >> 1;
        if(e < _elem[mid])
            hi = mid;
        elif(_elem[mid] < e)
            lo = mid + 1;
    }
    return lo - 1;
}