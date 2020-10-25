#include <iostream>
using namespace std;
#define N 500000

int main()
{
    for(int i = 0; i < (1 << 11); ++i)
    {
        cout << (((i % 4 == 0) || (i % 4 == 1)) ? 'A' : 'B');
    }

    for (int i = 0; i < (1 << 10)-4; ++i)
    {
        cout << (((i % 4 == 0) || (i % 4 == 1)) ? 'C' : 'D');
    }
    cout << "GFEEFFGG";
    for (int i = 0; i < (1 << 10)-4; ++i)
    {
        cout << (((i % 4 == 0) || (i % 4 == 1)) ? 'D' : 'C');
    }

    for (int i = 0; i < (1 << 11); ++i)
    {
        cout << (((i % 4 == 0) || (i % 4 == 1)) ? 'B' : 'A');
    }
    cout << endl << 1 << endl;
    cout << (2048 + 1024) << " E" << endl;
    return 0;
}