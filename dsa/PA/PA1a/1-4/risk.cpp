#include <iostream>
using namespace std;

/*
Honor Code:
- Discussed with:

- Reference:
DSA2020Fall lecturenote 04.S+Q.XA.Steap+Queap.pdf
*/

int n, T;
int infected[1000001];
int reference[1000001];
unsigned int mi, premi, p, q;

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
    quickSort(s, l);
    quickSort(l + 1, t);
}

// 二分查找，返回区间内不大于e的最大者
int binSearch(int s[], int lo, int hi, int e)
{
    while(lo < hi)
    {
        int mid = (lo + hi)/2;
        if(e < s[mid]) hi = mid;
        else lo = mid + 1;
    }
    return lo-1;
}

struct myQueap
{
    int size;
    int *maxque;
    int front, rear;
    myQueap(int size)
        : size(size), front(0), rear(0)
    {
        while((maxque = new int[size])==NULL);
        front = 0;
    }
    
    ~myQueap()
    {
        delete[] maxque;
    }
    

    void enqueue(int e)
    {
        maxque[rear] = e;
        rear = (rear + 1) % size;
        int x = (rear + size - 1) % size;
        while (maxque[x] <= e)
        {
            maxque[x] = e;
            if (x == front)
                break;
            x = (x + size - 1) % size;
        }
    }
    void dequeue(int n)
    {
        front = (front + n) % size;
    }
    int getMax()
    {
        return maxque[front];
    }
};

int main()
{
    scanf("%d", &n);
    for(int i = 1;i <= n;++i)
        scanf("%d", &infected[i]);
    
    myQueap Q(n+1);
    Q.enqueue(0);
    premi = 0;
    for(unsigned int i = 1;i <= n;++i)
    {
        scanf("%u", &mi);
        if(i > mi) Q.dequeue(min(premi,i-1) + 1 - mi);
        premi = mi;
        reference[i] = Q.getMax();
        Q.enqueue(infected[i]);
    }

    quickSort(reference+1,reference+n+1);

    scanf("%d", &T);
    for(int i = 0; i < T; i++)
    {
        scanf("%u %u",&p, &q);
        int low, middle;
        if(p > 2000000) low = n;
        else low = binSearch(reference,1,n+1,p-1);
        if(q > 2000000) middle = n;
        else middle = binSearch(reference,1,n+1,q-1);
        printf("%d %d\n", low, middle-low);
    }
    return 0;
}