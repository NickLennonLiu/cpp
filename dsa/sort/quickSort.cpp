#include <iostream>
using namespace std;
#define MAX_LEN 1000001

int partition(int A[], int lo, int hi)  // LGU
{
    swap(A[lo], A[lo + rand() % (hi - lo)]);
    int pivot = A[lo];
    int mi = lo;
    for(int i = lo + 1; i < hi; i++)
    {
        if(A[i] < pivot)
            swap(A[++mi],A[i]);
    }
    swap(A[lo],A[mi]);
    return mi;
}

void quickSort(int A[], int lo, int hi)
{
    int* stack = new int[MAX_LEN];
    int top = 0;
    stack[top++] = lo;
    stack[top++] = hi;
    while(top)
    {
        int t = stack[--top];
        int s = stack[--top];
        int mid = partition(A,s,t);
        if(mid * 2 > t - s)
        {
            if(mid - s > 1) {
                stack[top++] = s; stack[top++] = mid;
            }
            if(t - mid > 2) {
                stack[top++] = mid + 1; stack[top++] = t;
            }
        } else {
            if(t - mid > 2) {
                stack[top++] = mid + 1; stack[top++] = t;
            }
            if(mid - s > 1) {
                stack[top++] = s; stack[top++] = mid;
            }
        }
    }
    delete [] stack;
}

