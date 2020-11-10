#include <iostream>
using namespace std;

int steps(int n)
{
    if(n == 1) return 1;
    if(n == 2) return 2;
    if(n == 3) return 4;
    return steps(n-1) + steps(n-2) + steps(n-3);
}

int main()
{
    int n;
    cin >> n;
    if(n > 20 || n <= 3) cout << 0;
    else cout << steps(n);
    return 0;
}