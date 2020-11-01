#pragma once

#define DEFAULT_CAPACITY 16

template <typename T>
class Vector
{
    
public:
    // 默认构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
    {
        _elem = new T[_capacity = c];
        for(_size = 0; _size < s; ++_size)
            _elem[_size] = v;
    }
    // 数组构造函数
    Vector(T const * A, int lo, int hi)
    {
        copyFrom(A,lo,hi);
    }
    // 复制构造函数
    Vector(Vector<T> const& V)
    {
        copyFrom(V._elem, 0, V._size);
    }
    // 复制构造函数一定区间
    Vector(Vector<T> const& V,int lo, int hi)
    {
        copyFrom(V._elem, lo, hi);
    }
    int size() const {return _size;}        // 规模
    int capacity() const {return _capacity;}    // 容量
    bool empty() const {return !_size;}         // 判空
    // 插入元素在指定位置
    int insert(T const& e, int rank)
    {
        expand();
        for(int i = _size; i > rank; --i)
            _elem[i] = _elem[i-1];
        _elem[rank] = e;
        ++_size;
        return rank;
    }
    // 插入元素，默认在末尾
    int insert(T const& e)
    {
        return insert(e, _size);
    }
    // 移除指定位置的元素，返回元素值
    T remove(int rank)
    {
        T old = _elem[rank];
        remove(rank, rank+1);
        return old;
    }
    // 移除一定区间，返回区间长度
    int remove(int lo, int hi)
    {
        if( lo == hi) return 0;
        while(hi < _size)
            _elem[lo++] = _elem[hi++];
        _size = lo;
        shrink();
        return hi - lo;
    }
    // 无序查找
    int find(T const& e)
    {
        return find(e, 0, _size);
    }
    int find(T const& e, int lo, int hi);
    // 二分查找
    int search(T const& e)
    {
        return search(e, 0, _size);
    }
    int search(T const& e, int lo, int hi);
    // 排序，默认归并排序，归排大法好
    void sort()
    {
        if(!_size || _size == 1) return;
        mergeSort(0, _size);
    }
    T operator[](int n)
    {
        return _elem[n];
    }
protected:
    T *_elem;
    int _size, _capacity;
    void copyFrom(T const* A, int lo, int hi);
    void expand();
    void shrink();
    void merge(int lo, int mid, int hi);
    void mergeSort(int lo, int hi);
};

template <typename T>
void Vector<T>::merge(int lo, int mid, int hi)
{
    T* A = _elem + lo;
    int i = 0;
    int j = 0, lb = mid - lo; T* B = new T[lb];
    for(int i = 0; i < lb; i++) B[i] = A[i];
    int k = 0, lc = hi - mid; T* C = _elem + mid;
    while((j < lb) && (k < lc))
        A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++];
    while( j < lb )
        A[i++] = B[j++];
    delete [] B;
}

template <typename T>
void Vector<T>::mergeSort(int lo, int hi)
{
    if(hi <= lo + 1) return;
    mergeSort(lo, (lo + hi) >> 1);
    mergeSort((lo + hi) >> 1, hi);
    merge(lo,(lo + hi) >> 1, hi);
}


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
        else if(_elem[mid] < e)
            lo = mid + 1;
    }
    return lo - 1;
}