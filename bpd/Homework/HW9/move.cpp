#include <iostream>
using namespace std;

int n;
int steps[50001];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> steps[i];
    }
    int count = 0;
    int cur = 1;
    while(cur < n)
    {
        int tfar = cur;
        for(int j = 1 ;  j <= steps[cur]; ++j)
        {
            if ((steps[cur + j] + cur + j) > (steps[tfar] + tfar))
                tfar = cur + j;
            if(cur + j >= n)
            {
                cout << count +1 << endl;
                return 0;
            }
        }
        if(cur == tfar)
        {
            count ++;
            cur = cur + steps[cur];
        }else {
            count ++;
            cur = tfar;
        }
    }
    cout << count << endl;
    return 0;
}