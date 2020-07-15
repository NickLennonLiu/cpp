#include "sort.h"
#include <iostream>
using namespace std;

int main(){
    int a[9] = {9,8,7,6,5,4,3,2,1};
    //mergeSort(a,a+9);
    heapSort(a,a+9);
    for(auto i : a) cout << i << " ";
    return 0;
}