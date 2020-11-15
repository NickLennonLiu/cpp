#include <iostream>
using namespace std;


int p1, p2, p3;
char str[110] = {0};


int distance(char a, char b)
{
    if (a >= 'a' && a <= 'z' && b >= 'a' && b <= 'z')
        return b - a;
    if (a >= '0' && a <= '9' && b >= '0' && b <= '9')
        return b - a;
    return 0;
}

void output(char a, char b, int d)
{
    if(p1 == 3)
    {
        cout << a;
        for(int i = 0; i < p2*(d-1); ++i)
            cout << '*';
        //cout << b;
        return;
    }
    if(p3 & 1)
    {
        cout << a++;
        while(a<b)
        {
            for(int i = 0; i < p2; i++)
            {
                if(a >= 'a' && a <= 'z')
                {
                    cout << ((p1 == 1) ? (char)a : (char)(a + 'A' - 'a'));
                } else {
                    cout << (char)a;
                }
            }
            ++a;
        }
        //cout << b;
    } else {
        cout << a;
        char j = b-1;
        while (a < j)
        {
            for (int i = 0; i < p2; i++)
            {
                if (j >= 'a' && j <= 'z')
                {
                    cout << ((p1 == 1) ? (char)j : (char)((int)j + 'A' - 'a'));
                }
                else
                {
                    cout << (char)j;
                }
            }
            --j;
        }
        //cout << b;
    }
}

int main()
{
    cin >> p1 >> p2 >> p3;
    cin >> str;
    int len = 0;
    while(str[len]) len++;
    
    int i = 0;
    while(i < len)
    {
        if(str[i+1] == '-')
        {
            if(distance(str[i],str[i+2]) > 0)
            {
                output(str[i],str[i+2], distance(str[i],str[i+2]));
                i += 2;
            }
            else
                for(int j = 2; j; --j)
                    cout << str[i++];
        } else {
            cout << str[i++];
        }
    }
    return 0;
}