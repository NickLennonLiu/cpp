#include "sort.h"

void insertionSort(int *s, int *t){
    for(auto i = s;i < t;++i){
        auto cur = *i;
        auto j = i-1;
        while(j>=s && *j > cur){
            *(j+1) = *(j);
            --j;
        }
        *(j+1) = cur;
    }
}