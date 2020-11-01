#include "sort.h"
void quickSort(int * s, int* t){
    if(s==t-1||s==t) return;
    auto key = *s;
    auto l = s, r = t-1;
    while(l!=r){
        while(r!=l && *r > key) --r;
        if(r!=l) *(l++)=*r;
        while(l!=r && *l < key) ++l;
        if(l!=r) *(r--)=*(l);
    }
    *(l) = key;
    quickSort(l + 1, t);
    quickSort(s, l);
}