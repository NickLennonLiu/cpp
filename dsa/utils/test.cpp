#include <iostream>
#include "bitmap.cpp"
using namespace std;

int main()
{
    Bitmap_O1 b(1000);
    while(true)
    {
        int op, a;
        cin >> op >> a;
        if(op == 0) // set
        {
            b.set(a);
        }
        else if(op == 1) // test
        {
            if(b.test(a)) cout << "a in B" << endl;
            else cout << "a not in B" <<endl;
        }
        else if (op== 2)    // remove
        {
            b.remove(a);
        }
    }
    return 0;
}