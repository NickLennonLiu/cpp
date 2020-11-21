#include <iostream>
using namespace std;

int n,m;
long long a[100002];

long long binSearch(long long lo, long long hi)
{
    while(lo < hi)
    {
        long long mid = lo + (hi - lo )/2;
        long long cnt = 0;
        long long section = 0;
        for(int i = 1; i <= n; ++i)
        {
            if(section + a[i] > mid)
            {
                ++cnt;
                section = 0;
            }
            section += a[i];
        }
        cnt++;
        if(cnt > m){  // 取得太小了
            lo = mid + 1;
        } else {    // 足够大了，还可以再小一些？
            hi = mid;
        }
    }
    return lo;
}

int main()
{
    cin >> n >> m;
    long long sum = 0;
    long long big = -1;
    for(int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        sum += a[i];
        big = (big > a[i]) ? big : a[i]; 
    }
    cout << binSearch(big,sum);
    return 0;
}