#include <iostream>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    return n;
    int len;
    int maxlen = 0;
    int dummy, dummy2;
    for(int i = 0; i < n; i++)
    {
        cin >> len;
        for(int j = 0; j < len; j++)
            cin >> dummy;
    }
    for(int i = 0; i < m; i++)
    {
        cin >> dummy;
        switch (dummy)
        {
        case 0:
        {
            cin >> len;
            maxlen = (maxlen > len) ? maxlen : len;
            while(len--)
                cin >> dummy2;
            cin >> len;
            maxlen = (maxlen > len) ? maxlen : len;
            while (len--)
                cin >> dummy2;
            cin >> dummy2;
            break;
        }
        default:
        {
            cin >> len;
            maxlen = (maxlen > len) ? maxlen : len;
            while (len--)
                cin >> dummy2;
            break;
        }
        }
    }
    return maxlen;
}