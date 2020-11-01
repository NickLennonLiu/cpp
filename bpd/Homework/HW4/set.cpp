#include <iostream>
using namespace std;

int n,m;
int A[1000], B[1000];

int binSearch(int x, int *A, int lo, int hi)
{
    while (lo != hi)
    {
        int mid = (lo + hi) >> 1;
        if (A[mid] < x)
            lo = mid + 1;
        else if (A[mid] > x)
            hi = mid;
        else
            return mid;
    }
    if (lo == hi)
        return -1;
}

void quickSort(int *s, int *t)
{
    if (s == t - 1 || s == t)
        return;
    auto key = *s;
    auto l = s, r = t - 1;
    while (l != r)
    {
        while (r != l && *r > key)
            --r;
        if (r != l)
            *(l++) = *r;
        while (l != r && *l < key)
            ++l;
        if (l != r)
            *(r--) = *(l);
    }
    *(l) = key;
    quickSort(l + 1, t);
    quickSort(s, l);
}

void intersect(int *A, int *B, int n, int m)
{
    for(int i = 0; i < n; ++i)
    {
        if(binSearch(A[i],B,0,m) != -1)
            cout << A[i] << " ";
    }
    cout << endl;
}

void Union(int *A, int *B, int n, int m)
{
    if(!n && !m){
        cout << endl;
        return ;
    }
    int* C = new int[n+m];
    for(int i = 0; i < n; i++)
        C[i] = A[i];
    int* D = C + n;
    for(int j = 0; j < m; ++j)
        D[j] = B[j];
    quickSort(C, C+n+m);
    int i = 1;
    cout << C[0] << " ";
    while(i < n + m)
    {
        if(C[i] == C[i-1]) ++i;
        else
        {
            cout << C[i++] << " ";
        }
    }
    cout << endl;
    delete [] C;
}

void subtract(int *A, int *B, int n, int m)
{
    for(int i = 0; i < n; ++i)
    {
        if(binSearch(A[i], B, 0, m) == -1)
            cout << A[i] << " ";
    }
    cout << endl;
}



int main()
{
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> A[i];
    cin >> m;
    for (int i = 0; i < m; ++i)
        cin >> B[i];
    quickSort(A,A+n);
    quickSort(B,B+m);

    intersect(A,B,n,m);
    Union(A,B,n,m);
    subtract(A,B,n,m);
    return 0;
}