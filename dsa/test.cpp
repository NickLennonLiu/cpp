#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
    unsigned int p = UINT_MAX;
    cout << (int)((p > 2000000) ? 2000000 : p-1);
    return 0;
}