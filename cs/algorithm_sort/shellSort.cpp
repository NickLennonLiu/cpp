#include "sort.h"

void insertSortByL(int*,int*,int);

void shellSort(int* s, int* t){
    int len = t - s;
    if(len == 0 || len == 1) return;
    for(int i = len/2; i; i/=2){
        insertSortByL(s, t, i);
    }
}

void insertSortByL(int *s, int *t,int l)
{
    for (auto i = s; i < t; ++i)
    {
        auto cur = *i;
        auto j = i - l;
        while (j >= s && *j > cur)
        {
            *(j + l) = *(j);
            j-=l;
        }
        *(j + l) = cur;
    }
}