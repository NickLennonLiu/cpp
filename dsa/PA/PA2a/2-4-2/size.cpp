#include <iostream>
using namespace std;

int main()
{
    int a = 2147483647;
    cout << a << endl;
    int b = a;
    int m = (int)(((long long)(a) + (long long)(b)) >> 1);
    cout << m;
    return 0;
}