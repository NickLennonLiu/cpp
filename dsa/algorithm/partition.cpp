#include <iostream>
#include <stdio.h>
using namespace std;

int num[1000];

int partition(int lo, int hi)
{
    int mid = lo + (hi - lo)/2;
    swap(num[mid], num[lo]);
    int y = num[lo];
    while (lo < hi)
    {
        while (lo < hi && y < num[hi])
            hi--;
        if (lo < hi)
            num[lo++] = num[hi];
        while (lo < hi && num[lo] < y)
            lo++;
        if (lo < hi)
            num[hi--] = num[lo];
    }
    num[lo] = y;
    return lo;
}

int partitionx(int lo, int hi)
{
    int mid = lo + (hi - lo) / 2;
    swap(num[mid], num[lo]);
    int y = num[lo];
    int mi = lo;
    for(int k = lo + 1; k <= hi; k++)
    {
        if(num[k] < y)
            swap(num[++mi], num[k]);
    }
    swap(num[lo], num[mi]); 
    return mi;
}

int main()
{
    int n;
    cin >> n;
    for(int i =0; i < n; ++i){
        cin >> num[i];
    }
    int q = -1;
    int lo = 0, hi = n-1;
    while(q != n/2)
    {
        q = partition(lo, hi);
        cout << q << "    ";
        for(int i = 0; i < n; ++i)
            cout << num[i] << " ";
        cout << endl;
        if(q < n/2)
            lo = q + 1;
        else if(q > n/2)
            hi = q-1;
        else break;
    }
    return 0;
}