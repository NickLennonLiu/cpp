#include <iostream>
using namespace std;

bool isPrime(long long num)
{
    for(int i = 2; i * i <= num; ++i)
    {
        if(num % i == 0) return false;
    }
    return true;
}

bool isPalindrome(long long num)
{
    long long rev = 0, org = num;
    while(num)
    {
        rev = rev * 10 + num % 10;
        num /= 10;
    }
    return rev == org;
}

int main()
{
    long long a, b;
    cin >> a >> b;
    for(long long i = a; i <= b; ++i)
    {
        if(isPalindrome(i) && isPrime(i))
            cout << i << endl;
    }
    return 0;
}