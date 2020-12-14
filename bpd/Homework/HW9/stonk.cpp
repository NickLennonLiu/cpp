#include <iostream>
using namespace std;
int n;
int price[100001];
int main()
{   
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> price[i];
    int gain = 0;
    int start = price[0];
    for(int i = 1; i < n; ++i)
    {
        if(price[i] <= start)
            start = price[i];
        else {
            gain += price[i] - start;
            start = price[i];
        }
    }
    cout << gain << endl;
    return 0;
}