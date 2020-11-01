#include <iostream>

#include "singlelist.h"
using namespace std;


int main()
{
    List<int> a;
    for(int i = 0; i < 10; i++)
        a.insertAsLast(i);
    for(int i = 0; i < 10 ; i+=2)
        a.insert(a[i],i);
    for(int i = 0; i < a.size() ; i++)
        cout << a[i]->val << endl;
    return 0;
}