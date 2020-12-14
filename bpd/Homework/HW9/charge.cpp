#include <iostream>
using namespace std;
int N;
int units[10] = {10000,5000,1000,500,200,100,50,20,10};

int main()
{
    cin >> N;
    int i = 0;
    while(i<9)
    {
        cout << N/units[i];
        if(i != 8) cout << " ";
        N -= (N/units[i]) * units[i];
        ++i;
    }
    return 0;
}