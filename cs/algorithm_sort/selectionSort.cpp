#include "sort.h"

void selectionSort(int *s,int *t){
    for(auto i = s; i < t; ++i){
        auto minIndex = i;
        for(auto j = i+1;j < t; ++j){
            if(*(j) < *minIndex){
                minIndex = j;
            }
        }
        swap(i,minIndex);
    }
}