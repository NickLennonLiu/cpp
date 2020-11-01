#include <iostream>
using namespace std;

int carpets[10000][4];
int n;
int x,y, id;

bool inArea(int s,int t,int w,int l,int x, int y)
{
    return (x >= s) && (x <= s + w) && (y >= t) && (y <= t + l);
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> carpets[i][0] >> carpets[i][1] >> carpets[i][2] >> carpets[i][3];
    id = -1;
    cin >> x >> y;
    for(int i = 0 ; i < n; ++i)
    {
        if(inArea(carpets[i][0],carpets[i][1],carpets[i][2],carpets[i][3],x,y))
        {
            id = i+1;
        }
    }
    cout << id << endl;
    return 0;
}