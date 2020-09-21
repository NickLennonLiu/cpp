#define MAX_LEN 10000

/* 状态结构体 包含状态转移函数 */
struct ptype
{
    int x, y;
    ptype();
    ptype(int x, int y)
        : x(x), y(y)
    {
    }
    ptype operator+(ptype b)
    {
        return ptype(x + b.x, y + b.y);
    }
};

ptype queue[MAX_LEN];
int head, back;

void BFS(ptype start)
{

}