#include <stdio.h>

#define nmax 100010
#define mmax 400010
#define INT_MAX 2147483647
#define MOD 998244353

int n,m;

enum VStatus {
    VISITED, DISCOVERED, UNDISCOVERED
};
enum EStatus
{
    
};

struct node
{
    node* next;
    int weight;
    int succ;
};

struct list
{
    node* root;
    int first()
    {
        return root->next->succ;
    }
    int next(int x)
    {
        node* cur = root->next;
        while(cur->succ != x)
            cur = cur->next;
        return cur->next->succ;
    }
    void insert(int x, int weight)
    {
        node* n = new node;
        n->succ = x;
        n->weight = weight;
        n->next = root->next;
        root->next = n;
    }
    int weightTo(int x)
    {
        node* cur = root->next;
        while(cur->succ != x)
            cur = cur->next;
        return cur->next->weight;
    }
};

struct graph
{
    int weight(int v, int u)
    {
        return edge[v].weightTo(u);
    }
    int insertEdge(int v, int u, int weight)
    {
        edge[v].insert(u,weight);
        edge[u].insert(v,weight);
    }
    int firstNbr(int s)
    {
        return edge[s].first();
    }
    int nextNbr(int s, int w)
    {
        return edge[s].next(w);
    }
    template <typename PU>
    void pfs(int s, PU prioUpdater)
    {
        priority[s] = 0;
        status[s] = VISITED;
        parent[s] = -1;
        while(1)
        {
            for(int w = firstNbr(s); -1 < w; w = nextNbr(s, w))
                prioUpdater(this, s, w);
            for(int shortest = INT_MAX, w = 0; w < n; w++)
            {
                if( UNDISCOVERED == status[w])
                    if(shortest > priority[w])
                    {
                        shortest = priority(w);
                        s = w;
                    }
            }
            if (VISITED == status[s]) break;
            status[s] = VISITED;
            // type(parent[s], s) = TREE; 对边的标记是否在这题中有必要？
        }
    }
    int query(int v, int u, int weight)
    {

    }
    void dijkstra()
    {

    }
    int priority[nmax];
    int parent[nmax];
    list edge[nmax];
    VStatus status[nmax];
};


struct DijkPU
{
    void operator()(graph* g, int uk, int v)
    {
        if (UNDISCOVERED != g->status[v]){  // v的最短路径长度已经确定
            // 但它的最短路有可能更新
        }
        if (g->priority[v] > g->priority[uk] + g->weight(uk, v))
        {
            g->priority[v] = g->priority[uk] + g->weight(uk, v);
            g->parent[v] = uk;
        }
    }
};

int q;
int tv, tu, tw;
graph G;

int main()
{
    scanf("%d %d", &n,&m);

    for(int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &tv, &tu, &tw);
        G.insertEdge(tv,tu,tw);
    }

    G.dijkstra();

    scanf("%d", &q);
    while(q--)
    {
        scanf("%d %d %d", &tv, &tu, &tw);
        printf("%d\n", G.query(tv, tu, tw));
    }
    return 0;
}