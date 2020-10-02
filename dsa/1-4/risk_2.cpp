#include <iostream>
using namespace std;

void mergeSort(int *s, int *t)
{
    if (s == t || s == t - 1)
        return;
    auto len = (t - s) / 2;
    mergeSort(s, s + len);
    mergeSort(s + len, t);
    int *tmp = new int[t - s];
    auto i = s, j = s + len, k = tmp;
    while ((i != s + len) || (j != t))
    {
        while ((*i < *j || j == t) && i != s + len)
            *(k++) = *(i++);
        while ((*j <= *i || i == s + len) && j != t)
            *(k++) = *(j++);
    }
    while (k != tmp)
        *(--t) = *(--k);
    delete[] tmp;
}

inline int getint()
{
    int result = 0;
    char c;
    while ((c = getchar()) == ' ' || c == '\n')
        ;
    while (isdigit(c))
    {
        result = result * 10 + c - '0';
        c = getchar();
    }
    return result;
}

inline unsigned int getuint()
{
    unsigned int result = 0;
    char c;
    while ((c = getchar()) == ' ' || c == '\n')
        ;
    while (isdigit(c))
    {
        result = result * 10 + c - '0';
        c = getchar();
    }
    return result;
}

// 二分查找，返回区间内不大于e的最大者
int binSearch(int s[], int lo, int hi, int e)
{
    while (lo < hi)
    {
        int mid = (lo + hi)  >> 1;
        if (e < s[mid])
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo - 1;
}

class riskQueue
{
    int *maxindex;
    int front, rear, size;

public:
    int *infected;
    riskQueue(int n)
        : front(0), rear(0), size(n)
    {
        maxindex = new int[size + 1];
        infected = new int[size + 1];
        infected[0] = 0;
        front = rear = 0;
        maxindex[rear++] = 0;
    }
    ~riskQueue()
    {
        delete[] maxindex;
        delete[] infected;
    }
    int getMax(int L)
    {
        while(front < rear && maxindex[front] < L) front++;
        return infected[maxindex[front]];
    }
    void enqueue_by_index(int idx)
    {
        while(front < rear && infected[maxindex[rear-1]] <= infected[idx])
            rear--;
        maxindex[rear++] = idx;
    }
};

int n, T;
unsigned int mi, p, q;
int reference[1000001];

int main()
{
    n = getint();
    riskQueue Q(n);
    for (int i = 1; i <= n; ++i)
        Q.infected[i] = getint();

    for (unsigned int i = 1; i <= n; ++i)
    {
        mi = getuint();
        reference[i] = Q.getMax(i - mi);
        Q.enqueue_by_index(i);
    }

    mergeSort(reference + 1, reference + n + 1);

    T = getint();
    for (int i = 0; i < T; i++)
    {
        p = getuint();
        q = getuint();
        int low, middle;
        low = binSearch(reference, 1, n + 1, (int)((p > 2000000) ? 2000000 : (p - 1)));
        //if(low < 0) low = 0;
        middle = binSearch(reference, 1, n + 1, (int)((q > 2000000) ? 2000000 : (q - 1)));
        //if(middle < 0) middle = 0;
        printf("%u %u\n", low, middle - low);
    }
    return 0;
}