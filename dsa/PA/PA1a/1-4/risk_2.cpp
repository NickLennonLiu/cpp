#include <iostream>
using namespace std;

// 归并排序
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

// 读入int
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

// 读入unsigned int
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

// 区间最大值队列
class riskQueue
{
    int *maxindex;      // 记录最大感染数对应的日期
    int front, rear, size;  // 队列头、尾、长度

public:
    int *infected;      // 记录每天的感染数目
    riskQueue(int n)    // 初始化
        : front(0), rear(0), size(n)
    {
        maxindex = new int[size + 1];
        infected = new int[size + 1];
        infected[0] = 0;
        front = rear = 0;
        maxindex[rear++] = 0;
    }
    ~riskQueue()        // 析构函数
    {
        delete[] maxindex;
        delete[] infected;
    }
    int getMax(int L)   // 获得起始为第L天至今的最大感染数
    {
        while(front < rear && maxindex[front] < L) front++; // 出队直到最大值对应的起始日期在L以后
        return infected[maxindex[front]];
    }
    void enqueue_by_index(int idx)  // 将第idx天的感染数从尾部入队
    {
        while(front < rear && infected[maxindex[rear-1]] <= infected[idx])  // 将感染数小于当天感染数的日期从尾部出队
            rear--;                                                         // 直到遇到比当天感染数大的日期
        maxindex[rear++] = idx;                                             // 再入队
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
        middle = binSearch(reference, 1, n + 1, (int)((q > 2000000) ? 2000000 : (q - 1)));
        printf("%u %u\n", low, middle - low);
    }
    return 0;
}