#include <iostream>
#include "PQ.h"
using namespace std;

int num[10] = {1,4,2,5,7,3,10,9,8,6};

int main()
{
    PQ_LeftHeap<int> pq(num, 10);
    for(int i = 0; i < 10; ++i)
    {
        cout << pq.delMax() << endl;
    }
    cout << endl;
    for(int i = 0; i < 10; ++i)
    {
        pq.insert(i*i);
    }
    for (int i = 0; i < 10; ++i)
    {
        pq.insert(i * i/2);
    }
    for(int i = 0; i < 20; ++i)
        cout << pq.delMax() << endl;
    return 0;
}