#include <iostream>
using namespace std;

int det = 0;

int a[1000][1000];
int n;
int p[1000];

void addsum()
{
    int rev = 0;
    int sing = 1;
    for (int i = 0; i < n; ++i)
    {
        sing *= a[i][p[i]];
        for (int j = i + 1; j < n; ++j)
            if (p[i] > p[j])
                ++rev;
    }
    sing *= (rev & 1) ? (-1) : 1;
    det += sing;
}

void permutation(int *A, int n)
{
    if(!n)
    {
        addsum();
        return;
    }
    for(int i = 0;i < n; ++i)
    {
        swap(A[0], A[i]);
        permutation(A+1, n-1);
        swap(A[0], A[i]);
    }
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        p[i] = i;
        for(int j = 0; j < n; j++)
            cin >> a[i][j];
    }
    permutation(p,n);
    cout << det;
    return 0;
}