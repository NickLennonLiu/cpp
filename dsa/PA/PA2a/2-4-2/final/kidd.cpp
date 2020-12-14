#include <stdio.h>

#define maxn 12000000

int n, m;
char op;
int lo, hi;

int lazy[maxn]; // 懒惰标记
int lc[maxn];   // 左右子树
int rc[maxn];
long long flipped[maxn];    // 节点值


int root;
int applied = 1;    // 新申请的节点在数组中的位置

// 节点v向下传播lazytag并更新翻转次数
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

// 翻转节点v，v对应的左端点为L,右端点为R
void flip(int v, const int& lo, const int& hi, int L, int R)
{
    if(lo <= L && hi >= R)
    {
        flipped[v] += R - L + 1;
        lazy[v] += 1;
        return;
    }
    int mid = (int)(((long long)(L) + (long long)(R)) >> 1);

    if(!lc[v])  // 若未生成左右孩子，则为其分配空间
    {
        lc[v] = applied++;
        rc[v] = applied++;
    }
    pushdown(v, (R - L + 1));   // 翻转前先将已有的tag向下传播

    if(!(hi < L || lo > mid))   // Int(lc(v)) \cap s != empty
        flip(lc[v], lo, hi, L, mid);
    if(!(hi < mid+1 || lo > R)) // Int(rc(v)) \cap s != empty
        flip(rc[v], lo, hi, mid+1, R);

    flipped[v] = flipped[lc[v]] + flipped[rc[v]];
}

// 报告节点v对应区间[L,R]的翻转次数
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