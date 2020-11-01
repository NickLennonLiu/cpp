#pragma once

template <typename T> 
struct Cleaner<T*>
{
    static void clean (T* x)
    {
        if(x)
            delete x;
        static int n = 0;
    }
};

template <typename T> void release (T x)
{
    Cleaner<T>::clean(x);
}