#include <iostream>
using namespace std;

long long gcd(long long a, long long b)
{
    if(a > b) swap(a,b);
    if((b % a)==0) return a;
    return gcd(b-(b/a)*a,a);
}

int t,n;
long long a[2010];

int main()
{
    cin >> t;
    for(int i = 0; i < t; ++i)
    {
        int maxgcd = 1;
        cin >> n;
        for(int j = 0; j < n; ++j)
            cin >> a[j];
        for(int j = 0; j < n; ++j)
            for(int k = j+1; k < n; ++k)
            {
                long long temp = gcd(a[j],a[k]);
                if(maxgcd < temp)
                    maxgcd = temp;
            }
        cout << maxgcd << endl;
    }
    return 0;
}