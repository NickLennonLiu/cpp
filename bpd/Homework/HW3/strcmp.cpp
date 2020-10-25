#include <iostream>
using namespace std;

char a[10000], b[10000];

bool ignoreCaption(char x, char y)
{
    return (x-y)==('A'-'a') || (x-y)==('a'-'A');
}

int main()
{
    int status = 2;
    cin >> a;
    cin >> b;
    int i = 0;
    for(i = 0; a[i] && b[i]; ++i)
    {
        if(a[i] != b[i])
        {
            if(ignoreCaption(a[i],b[i])) status = 3;
            else
            {
                status = 4;
                break;
            }
        }
    }
    if((a[i] || b[i]) && status != 4) status = 1;
    cout << status << endl;
    return 0;
}