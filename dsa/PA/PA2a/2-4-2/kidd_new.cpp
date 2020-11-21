#include <stdio.h>

#define maxn 12000000

int n, m;
char op;
int lo, hi;

int lazy[maxn];
int lc[maxn];
int rc[maxn];
long long flipped[maxn];


int root;
int applied = 1;


void pushdown(int v, int len)
{
    if(lazy[v])
    {
        int la = lazy[v];
        lazy[lc[v]] += la;
        lazy[rc[v]] += la;
        flipped[lc[v]] += la * (len - (len >> 1));
        flipped[rc[v]] += la * (len >> 1);
        lazy[v] = 0;
    }
}

void flip(int v, const int& lo, const int& hi, int L, int R)
{
    if(lo <= L && hi >= R)
    {
        flipped[v] += R - L + 1;
        lazy[v] += 1;
        return;
    }
    int mid = (int)(((long long)(L) + (long long)(R)) >> 1);

    if(!lc[v])
    {
        lc[v] = applied++;
        rc[v] = applied++;
    }
    pushdown(v, (R - L + 1));

    if(!(hi < L || lo > mid))   // Int(lc(v)) \cap s != empty
        flip(lc[v], lo, hi, L, mid);
    if(!(hi < mid+1 || lo > R)) // Int(rc(v)) \cap s != empty
        flip(rc[v], lo, hi, mid+1, R);

    flipped[v] = flipped[lc[v]] + flipped[rc[v]];
}

long long query(int v, const int& lo, const int& hi,int L, int R)
{
    if(lo <= L && R <= hi)
        return flipped[v];
    int mid = (int)(((long long)(L) + (long long)(R)) >> 1);
    if (!lc[v])
    {
        lc[v] = applied++;
        rc[v] = applied++;
    }
    pushdown(v,R-L+1);

    long long result = 0;
    
    if (!(hi < L || lo > mid)) // Int(lc(v)) \cap s != empty
        result += query(lc[v], lo, hi, L, mid);
    if (!(hi < mid + 1 || lo > R)) // Int(rc(v)) \cap s != empty
        result += query(rc[v], lo, hi, mid+1, R);

    return result;
};

int main()
{
    scanf("%d %d", &n, &m);
    root = applied++;
    while(m--)
    {
        scanf(" %c %d %d", &op, &lo, &hi);
        if(op == 'H') { // 更新
            flip(root, lo, hi, 1, n);
        } else {    // 查询
            printf("%lld\n", query(root, lo, hi, 1, n));
        }
    }
    return 0;
}