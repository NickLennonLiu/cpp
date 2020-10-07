#include <iostream>
using namespace std;
int main()
{
    for(int i = 0;i < 500000;i++)
    {
        cout << (((i%4 == 0) || (i % 4==1))? 'A' : 'B');
    }
    cout << endl;
    cout << 500000 << endl;
    for(int i = 0;i < 250000;i++)
    {
        cout << "0 " << ((!(i%2))? 'A' : 'B') << endl;
    }
    for (int i = 0; i < 250000; i++)
    {
        cout << "0 " << (((i % 4 == 0) || (i % 4 == 1)) ? 'A' : 'B') << endl;
    }
    return 0;
}