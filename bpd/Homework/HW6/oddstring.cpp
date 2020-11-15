#include <iostream>
using namespace std;

char str[300] = {0};

int main()
{
    cin >> str;
    int i = 1, j = 0;
    while(str[j] != 0) ++j;
    if(!(j & 1)) j += 1;
    j -= 2;
    while(i < j)
    {
        swap(str[i],str[j]);
        i+=2;
        j-=2;
    }
    cout << str;
    return 0;
}