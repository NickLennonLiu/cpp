#include <stdio.h>

#define nmax 800010
#define mmax 800010
#define MAX 2223372036854775807
#define MOD 998244353
#define parent(x) ((x) >> 1)
#define lc(x) ((x) << 1)
#define rc(x) (((x) << 1) | 1)

int n,m;
long long dis1[nmax], disn[nmax];   // （并查集意义下）1到其他节点的最短距离、n到其他节点的最短距离
long long spc1[nmax], spcn[nmax];   // （并查集意义下）1到其他节点的最短路经数、n到其他节点的最短路径数
long long edges[mmax][3];           //  建并查集、图之前储存边的数组

struct node
{
    node* next;
    long long weight;
    int succ;
};

struct list
{
    node* first;
    node* last;
    void insert(int x, long long weight)
    {
        node* n = new node;
        n->succ = x;
        n->weight = weight;
        n->next = first;
        if(!first) last = n;
        first = n;
    }
};

// 堆   用于Dijkstra算法的堆优化
struct heap
{
    int curnode;

    int vid[mmax];
    long long prio[mmax];

    void init()
    {
        curnode = 1;
        for(int i = 0; i < mmax; ++i)
        {
            prio[i] = MAX;
            vid[i] = 0;
        }
    }

    // 堆序：优先级高的靠近堆顶
    bool cmp(int x, int y)
    {
        if(vid[x] == vid[y])
            return prio[x] < prio[y];
        return prio[x] < prio[y];
    }

    void swap(int x, int y)
    {
        long long tp = prio[x];
        int tv = vid[x];
        prio[x] = prio[y];
        vid[x] = vid[y];
        prio[y] = tp;
        vid[y] = tv;
    }

    void insert(int v, long long p)
    {
        prio[curnode] = p;
        vid[curnode] = v;
        int cur = curnode++;
        while(cur > 1)
        {
            int j = parent(cur);
            if(cmp(j,cur))
                break;
            swap(cur,j);            
            cur = j;
        }
    }
    void pop()
    {
        curnode -= 1;
        swap(1,curnode);
        vid[curnode] = 0;
        prio[curnode] = MAX;
        int cur = 1;
        int j;
        while(cur != (j = properparent(cur)))
        {
            swap(cur,j);
            cur = j;
        }
    }
    int properparent(int i)
    {
        int re = i;
        if (vid[lc(i)] && cmp(lc(i), re))
            re = lc(i);
        if (vid[rc(i)] && cmp(rc(i), re))
            re = rc(i);
        return re;
    }
    //堆顶的节点序号
    int topvid()
    {
        return vid[1];
    }
    //堆顶的优先级
    long long topprio()
    {
        return prio[1];
    }
};

struct graph
{
    long long priority[nmax];
    list edge[nmax];
    char status[nmax];
    heap dijkheap;

    // 并查集
    int zero[nmax];
    int find(int v)
    {
        int cur = v;
        while (zero[cur] != cur)
            cur = (zero[cur] = find(zero[cur]));
        return zero[v];
    }
    void makeunion(int from, int to)
    {
        zero[find(from)] = find(to);
    }

    graph()
    {
        for(int i = 0; i < nmax; ++i)
            zero[i] = i;
    }

    // 下面的函数都是在并查集意义下进行
    // 插入边
    void insertEdge(int v, int u, long long weight)
    {
        if(find(v) == find(u))
            return;
        edge[find(v)].insert(find(u), weight);
        edge[find(u)].insert(find(v), weight);
    }

    void dijkstra(int s, long long *spc, long long *dis)
    {
        dijkheap.init();
        s = find(s);
        priority[s] = 0;
        status[s] = 1;
        while(1)
        {
            for(node* e = edge[s].first; e; e = e->next)
            {
                int w = e->succ;
                if (status[w])
                { // v的最短路径长度已经确定
                    if(priority[w] == priority[s] + e->weight)// 但它的最短路有可能更新
                        spc[w] = (spc[w] + spc[s]) % MOD;
                    continue;
                }
                if (priority[w] > priority[s] + e->weight)
                {
                    priority[w] = priority[s] + e->weight;  // 作松弛
                    dijkheap.insert(w, priority[w]);
                    spc[w] = spc[s];
                } 
                else if (priority[w] == priority[s] + e->weight)
                {
                    spc[w] = (spc[w] + spc[s]) % MOD;
                }
            }
            
            if(dijkheap.curnode <= 1) break;
            s = dijkheap.topvid();
            while(status[s] && dijkheap.curnode > 1)
            {
                dijkheap.pop();
                if(dijkheap.curnode <= 1)
                    break;
                s = dijkheap.topvid();
            }
            if(dijkheap.curnode <= 1 || status[s])
                break;
            
            long long minprio = dijkheap.topprio();
            while(dijkheap.curnode > 1 && dijkheap.topvid() == s)
            {
                dijkheap.pop();
            }
            if (status[s]) break;
            status[s] = 1;
            dis[s] = priority[s];
        }
    }

    long long query(int v, int u, long long w)
    {
        v = find(v);
        u = find(u);
        long long end = dis1[find(n)];          // 原本的距离
        long long new_dis1 = dis1[v] + disn[u] + w; // 新距离1
        long long new_dis2 = disn[v] + dis1[u] + w; // 新距离2
        long long ans = spc1[find(n)];          // 原本的最短距离对应路径数
        if(new_dis1 < end || new_dis2 < end)    // 最短距离更新了
        {
            if (new_dis1 == new_dis2)
            {
                return ((spc1[v] * spcn[u]) % MOD + (spcn[v] * spc1[u]) % MOD) % MOD;
            }
            else if(new_dis1 < new_dis2)
                return (spc1[v] * spcn[u]) % MOD;
            else
                return (spcn[v] * spc1[u]) % MOD;
        }
        if (new_dis1 == end)                    // 最短路径数被第一条新路径更新
            ans = (ans + (spc1[v] * spcn[u]) % MOD) % MOD;
        if (new_dis2 == end)                    // 最短路径数被第二条新路径更新
            ans = (ans + (spcn[v] * spc1[u]) % MOD) % MOD;
        return ans;
    }

    void priority_flush()   // 清空状态
    {
        for(int i = 0; i < nmax; ++i)
        {
            priority[i] = MAX;
            status[i] = 0;
        }
    }
};

int q;
long long tv, tu, tw;
graph G;

int main()
{
    scanf("%d %d", &n,&m);
    for(int i = 1; i <= n; i++)
    {
        dis1[i] = disn[i] = MAX;
    }
    
    for(int i = 0; i < m; i++)
    {
        scanf("%lld %lld %lld", &edges[i][0], &edges[i][1], &edges[i][2]);
        if(!edges[i][2])    // 若发现零边
            G.makeunion(edges[i][0],edges[i][1]);   // 将零边连接的点并入同一集合（并查集）
    }
    for(int i = 0; i < m; ++i)  // 建图，不再插入零边
        if (edges[i][2])
            G.insertEdge(edges[i][0], edges[i][1], edges[i][2]);    

    // 进行dijkstra
    spc1[G.find(1)] = 1;
    spcn[G.find(n)] = 1;
    dis1[G.find(1)] = 0;
    disn[G.find(n)] = 0;
    G.priority_flush(); 
    G.dijkstra(1,spc1,dis1);    // 从起点开始的Dijkstra
    
    G.priority_flush();
    G.dijkstra(n,spcn,disn);    // 从终点开始的Dijkstra

    scanf("%d", &q);            // 询问环节
    while(q--)
    {
        scanf("%lld %lld %lld", &tv, &tu, &tw);
        printf("%lld\n", G.query(tv, tu, tw));
    }
    return 0;
}