#include <iostream>
using namespace std;

/*
Honor Code:
- Discussed with:
关于根据p,q查询低风险/中风险天数的二分查找方法，曾与贾启珑讨论
关于维护区间最大值的的实现，曾与贾启珑讨论
关于基本数据类型long long int的选取，曾与龚然同学讨论

- Reference:
DSA2020Fall lecturenote 04.S+Q.XA.Steap+Queap.pdf
*/

// 归并排序
void mergeSort(long long int *s,long long int *t)
{
    if (s == t || s == t - 1)
        return;
    auto len = (t - s) / 2;
    mergeSort(s, s + len);
    mergeSort(s + len, t);
    long long int *tmp = new long long int[t - s];
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

// 读入整数
inline long long int getint()
{
    long long int result = 0;
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
long long int binSearch(long long int s[], long long int lo, long long int hi, long long int e)
{
    while (lo < hi)
    {
        long long int mid = (lo + hi) >> 1;
        if (e < s[mid])
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo - 1;
}

// 区间最大值队列
class riskQueue
{
    long long int *maxindex; // 记录最大感染数对应的日期
    long long int front, rear, size; // 队列头、尾、长度

public:
    long long int *infected; // 记录每天的感染数目
    riskQueue(long long int n)    // 初始化
        : front(0), rear(0), size(n)
    {
        maxindex = new long long int[size + 1];
        infected = new long long int[size + 1];
        infected[0] = 0;
        front = rear = 0;
        maxindex[rear++] = 0;
    }
    ~riskQueue()        // 析构函数
    {
        delete[] maxindex;
        delete[] infected;
    }
    long long int getMax(long long int L)   // 获得起始为第L天至今的最大感染数
    {
        while(front < rear && maxindex[front] < L) front++; // 出队直到最大值对应的起始日期在L以后
        return infected[maxindex[front]];
    }
    void enqueue_by_index(long long int idx)  // 将第idx天的感染数从尾部入队
    {
        while(front < rear && infected[maxindex[rear-1]] <= infected[idx])  // 将感染数小于当天感染数的日期从尾部出队
            rear--;                                                         // 直到遇到比当天感染数大的日期
        maxindex[rear++] = idx;                                             // 再入队
    }
};

long long int n, T;
long long int mi, p, q;
long long int reference[1000001];

int main()
{
    n = getint();
    riskQueue Q(n);
    for (long long int i = 1; i <= n; ++i)
        Q.infected[i] = getint();

    for (long long int i = 1; i <= n; ++i)
    {
        mi = getint();
        reference[i] = Q.getMax(i - mi);
        Q.enqueue_by_index(i);
    }

    mergeSort(reference + 1, reference + n + 1);

    T = getint();
    for (long long int i = 0; i < T; i++)
    {
        p = getint();
        q = getint();
        long long int low, middle;
        low = binSearch(reference, 1, n + 1, p-1);
        middle = binSearch(reference, 1, n + 1, q-1);
        printf("%lld %lld\n", low, middle - low);
    }
    return 0;
}