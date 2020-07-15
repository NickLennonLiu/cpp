#include "sort.h"

void bubbleSort(int *s, int *t){
    if(s >= t) return;
    for(auto i = t-1;i >= s;--i){
        for(auto j = s;j < i;++j){
            if(*j > *(j+1)) {
                swap(j,j+1);
            }
        }
    }
}