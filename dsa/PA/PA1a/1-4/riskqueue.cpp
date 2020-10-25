#include <iostream>
using namespace std;

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

inline int partition(int A[], int lo, int hi)  // LGU
{
    int pivot = A[lo];
    int mi = lo;
    for(int i = lo + 1; i < hi; i++)
    {
        if(A[i] < pivot)
            swap(A[++mi], A[i]);
    }
    swap(A[lo],A[mi]);
    return mi;
}


void quickSort(int A[], int lo, int hi)
{
    int stack[10000];
    int top = 0;
    stack[top++] = lo;
    stack[top++] = hi;
    while(top)
    {
        int t = stack[--top];
        int s = stack[--top];
        int mid = partition(A,s,t);
        if(mid * 2 > t - s)
        {
            if(mid - s > 1) {
                stack[top++] = s; stack[top++] = mid;
            }
            if(t - mid > 2) {
                stack[top++] = mid + 1; stack[top++] = t;
            }
        } else {
            if(t - mid > 2) {
                stack[top++] = mid + 1; stack[top++] = t;
            }
            if(mid - s > 1) {
                stack[top++] = s; stack[top++] = mid;
            }
        }
    }
}

void mergeSort(int *s, int *t){
    if(s==t||s==t-1) return;
    auto len = (t-s)/2;
    mergeSort(s,s+len);
    mergeSort(s+len,t);
    int *tmp = new int[t-s];
    auto i = s,j = s+len, k = tmp;
    while((i!=s+len)||(j!=t)){
        while((*i < *j || j == t )&& i != s+len) *(k++) = *(i++);
        while((*j <= *i || i == s+len) && j != t) *(k++) = *(j++);
    }
    while(k!=tmp) *(--t) = *(--k);
    delete[] tmp;
}

// 二分查找，返回区间内不大于e的最大者
int binSearch(int s[], int lo, int hi, int e)
{
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        if (e < s[mid])
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo - 1;
}

class riskQueue
{
    int* maxindex;
    int front, rear, size;
public:
    int* infected;
    riskQueue(int n)
    : front(0)
    , rear(0)
    , size(n)
    {
        maxindex = new int[size+2];
        infected = new int[size+2];
        infected[0] = 0;
        front = rear = 0;
        maxindex[rear++] = 0;
    }
    
    ~riskQueue()
    {
        delete [] maxindex;
        delete [] infected;
    }
    
    int getMax()
    {
        return infected[maxindex[front]];
    }
    void enqueue_by_index(int idx)
    {
        int i = front;
        while(i < rear && infected[idx] < infected[maxindex[i]]) i++;
        if(i == rear) maxindex[rear++] = idx;
        else 
        {
            maxindex[i] = idx;
            rear = i+1;
        }
    }
    // 将区间最大值对应序号小于pos的都出队
    void dequeue_until(int pos)
    {
        while(maxindex[front] < pos) front++;
    }
};

int n, T;
unsigned int mi, p,q;
int reference[1000001];

int main()
{
    n = getint();
    riskQueue Q(n);
    for (int i = 1; i <= n; ++i)
        Q.infected[i] = getint();
        //scanf("%d", &Q.infected[i]);

    for (unsigned int i = 1; i <= n; ++i)
    {
        //scanf("%u", &mi);
        mi = getuint();
        Q.dequeue_until(i - mi);
        reference[i] = Q.getMax();
        Q.enqueue_by_index(i);
    }

    //quickSort(reference, 1, n + 1);
    mergeSort(reference+1,reference+n+1);

    //scanf("%d", &T);
    T = getint();
    for (int i = 0; i < T; i++)
    {
        //scanf("%u %u", &p, &q);
        p = getuint();
        q = getuint();
        int low, middle;
        low = binSearch(reference,1,n+1,(int)((p > 2000000) ? 2000000 : p-1));
        middle = binSearch(reference,1,n+1,(int)((q > 2000000) ? 2000000 : q-1));
        printf("%u %u\n", low, middle - low);
    }
    return 0;
}