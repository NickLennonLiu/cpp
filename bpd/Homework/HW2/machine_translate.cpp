#include <iostream>
using namespace std;

int m, n;
int dict[11];
int hi;

int main()
{
    cin >> m >> n;
    hi = 0;
    int cnt = 0;
    for(int j = 0; j < m; j++) dict[j] = -1;
    for(int i = 0; i < n; i++)
    {
        int word;
        cin >> word;
        int flag = 0;
        for(int j = 0;j < m; ++j)
        {
            if(word == dict[j])
            {
                flag = 1;
                break;
            }
        }
        if(!flag)
        {
            ++cnt;
            dict[hi] = word;
            hi = (hi + 1) % m;
        }
    }
    cout << cnt;
    return 0;
}