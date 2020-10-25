#include <iostream>
using namespace std;

char EncryptChar(char c)
{
    if(c <= 'Y' && c >= 'A') return c+1;
    if(c=='Z') return 'a';
    if(c<='y' && c >= 'a') return c+1;
    if(c=='z') return 'A';
    return c;
}

char s[1000000] = {0};

int main()
{
    cin >> s;
    int i = 0;
    while(s[i])
    {
        cout << EncryptChar(s[i]);
        ++i;
    }
    return 0;
}