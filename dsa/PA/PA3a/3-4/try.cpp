#include <cstdio>

#define nmax 1000010

int n, m, k, q;

// node
int data[nmax];
int lc[nmax], rc[nmax];
int npl[nmax];

// unifind
int connect[nmax];
inline int find(int v)
{
    int cur = v;
    while (connect[cur] != cur)
        cur = (connect[cur] = find(connect[cur]));
    return connect[v];
}
inline void unify(int from, int to)
{
    connect[find(from)] = find(to);
}

inline void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

// LeftHeap
int root[nmax];
int size[nmax];

int merge(int a, int b) // merge heap[a] and heap[b]
{
    if (!a)
        return b;
    if (!b)
        return a;
    if (data[a] > data[b])
        swap(b, a);
    rc[a] = merge(rc[a], b);
    if (npl[lc[a]] < npl[rc[a]] || !lc[a])
        swap(lc[a], rc[a]);
    npl[a] = 1 + npl[rc[a]];
    return a;
}
int getMin(int h) // get min element of heap[h]
{
    return data[root[h]];
}
inline void delMin(int h) // del min element of heap[h]
{
    size[h]--;
    root[h] = merge(lc[root[h]], rc[root[h]]);
}
void mergeKthHeap(int &u, int &v) // merge heap and preserve first Ks of maximum
{
    u = find(u);
    v = find(v);
    if (u == v)
        return;
    int newsize = size[u] + size[v];
    int newheap = merge(root[u], root[v]);

    unify(v, u);
    v = find(v);
    root[v] = newheap;
    size[v] = newsize;

    while (size[v] > k)
        delMin(v);
}

int tu, tv, op;

int main()
{
    scanf("%d%d%d%d", &n, &m, &k, &q);
    for (int i = 1; i <= n; ++i) // init unifind sets and heaps
    {
        connect[i] = root[i] = i;
        scanf("%d", data + i);
        npl[i] = size[i] = 1;
    }
    for (int i = 0; i < m; ++i) // init graph
    {
        scanf("%d%d", &tu, &tv);
        mergeKthHeap(tu, tv);
    }
    while (q--)
    {
        scanf("%d", &op);
        if (op == 1)
        { // 加边
            scanf("%d%d", &tu, &tv);
            mergeKthHeap(tu, tv);
        }
        else
        { // 查询
            scanf("%d", &tu);
            if (size[find(tu)] < k)
                printf("-1\n");
            else
                printf("%d\n", getMin(find(tu)));
        }
    }

    return 0;
}