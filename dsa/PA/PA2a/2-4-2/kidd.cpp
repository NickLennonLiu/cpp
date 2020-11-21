#include <stdio.h>

struct node
{
    int lc, rc;
    long long flipped;
    int lazy;
};



int n, m;
char op;
int lo, hi;

node memory[10000000];
int lazy[10000000];
node* root;
int applied = 1;


void pushdown(node* v, int len)
{
    if(v->lazy)
    {
        int la = v->lazy;
        memory[v->lc].lazy += la;
        memory[v->rc].lazy += la;
        memory[v->lc].flipped += la * (len - (len >> 1));
        memory[v->rc].flipped += la * (len >> 1);
        v->lazy = 0;
    }
}

void flip(node* v, const int& lo, const int& hi, int L, int R)
{
    if(lo <= L && hi >= R)
    {
        v->flipped += R - L + 1;
        v->lazy += 1;
        return;
    }
    int mid = (L + R) >> 1;
    
    if(!v->lc)
    {
        v->lc = applied++;
        v->rc = applied++;
    }
    pushdown(v, (R - L + 1));

    if(!(hi < L || lo > mid))   // Int(lc(v)) \cap s != empty
        flip(memory + v->lc, lo, hi, L, mid);
    if(!(hi < mid+1 || lo > R)) // Int(rc(v)) \cap s != empty
        flip(memory + v->rc, lo, hi, mid+1, R);

    v->flipped = memory[v->lc].flipped + memory[v->rc].flipped;
}

long long query(node* v, const int& lo, const int& hi,int L, int R)
{
    if(lo <= L && R <= hi)
        return v->flipped;
    int mid = (L + R) >> 1;
    if (!v->lc)
    {
        v->lc = applied++;
        v->rc = applied++;
    }
    pushdown(v,R-L+1);

    long long result = 0;
    
    if (!(hi < L || lo > mid)) // Int(lc(v)) \cap s != empty
        result += query(memory + v->lc, lo, hi, L, mid);
    if (!(hi < mid + 1 || lo > R)) // Int(rc(v)) \cap s != empty
        result += query(memory + v->rc, lo, hi, mid+1, R);

    return result;
};

int main()
{
    scanf("%d %d", &n, &m);
    root = memory + (applied++);
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