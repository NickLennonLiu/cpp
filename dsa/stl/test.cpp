#include <iostream>

#include "Trees/AVL.h"
using namespace std;

void viewNode(int i)
{
    cout << i << " ";
}

int main()
{
    AVL<int> a;
    a.insertAsRoot(0);
    for(int i = 1;i <= 10; ++i)
    {
        a.insert(i);
        a.travLevel(viewNode);
        cout << endl;
    }
    return 0;
}