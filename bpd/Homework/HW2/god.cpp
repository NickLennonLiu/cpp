#include <iostream>
using namespace std;

int n, Q, lo, hi;
int a[2000];

int main()
{
    cin >> n >> Q;
    for(int i = 0; i < n; i++) 
        cin >> a[i];
    for(int i = 0; i < Q; i++)
    {
        cin >> lo >> hi;
        int min = 1001;
        while(hi >= lo)
        {
            if(a[hi] < min) min = a[hi];
            --hi;
        }
        cout << min << endl;
    }
    return 0;
}