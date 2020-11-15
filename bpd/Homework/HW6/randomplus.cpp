#include <iostream>
using namespace std;

int n;
int num[100001];
int deduplicate[100001];
int de = 0;

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

int main()
{
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> num[i];
    quickSort(num, num+n);
    for(int i = 0; i < n; ++i)
    {
        while(i + 1 < n && num[i] == num[i+1]) ++i;
        deduplicate[de++] = num[i];
    }
    cout << de << endl;
    for(int i = 0; i < de; ++i)
        cout << deduplicate[i] << " ";
    return 0;
}