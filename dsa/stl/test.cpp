#include <iostream>
#include "Queap.h"
using namespace std;

int main()
{
    Queap<int> q;
    for(int i = 10; i > 0; --i)
    {
        q.enqueue(i);
    }
    cout << q.getMax() << endl;
    return 0;
}