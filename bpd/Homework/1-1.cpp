#include <iostream>
using namespace std;

int N;
bool isA = true;
int factor_cnt[100];
int factors[100];
int top = 0;

int main()
{   
    cin >> N;
    for(int i = 2;(i * i) <= N; i+=2)
    {
        if(!(N%i))
        {
            top++;
            factors[top] = i;
            while(!(N%i))
            {
                factor_cnt[top] ++;
                if(factor_cnt[top] > 1) isA = false;
                N /= i;
            }
        }
        if(i==2) --i;
    }
    if(N > 1)
    {
        top++;
        factors[top] = N;
        factor_cnt[top]++;
    }
    if(isA) cout <<"A" << endl;
    else cout << "B" <<endl;
    for(int i = 1; i<=top; i++)
    {
        while(factor_cnt[i]--)
            cout << factors[i] <<endl;
    }
    return 0;
}