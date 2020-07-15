#include "sort.h"

void buildMaxHeap(int*,int*);
void heapify(int*,int*,int);

void heapSort(int* s,int * t){
    int len = t - s;
    buildMaxHeap(s,t);
    for(int i = len-1;i>=0;--i){
        swap(s,s+i);
        --t;
        heapify(s,t,0);
    }
}

void buildMaxHeap(int *s,int *t){
    int len = t - s;
    for(int i = len/2; i>=0; --i){
        heapify(s,t,i);
    }
}

void heapify(int *s,int *t,int i){
    int left = 2*i + 1,
        right = 2*i + 2,
        largest = i,
        len = t-s;
    if(left < len && *(s+left) > *(s+largest)){
        largest = left;
    } 
    if(right < len && *(s+right) > *(s+largest)){
        largest = right;
    } 
    if(i!=largest){
        swap(s+i,s+largest);
        heapify(s,t,largest);
    }
}