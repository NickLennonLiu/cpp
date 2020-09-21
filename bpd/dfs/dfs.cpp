#include <iostream>

#define MAX_LEN 10000

int map[MAX_LEN][MAX_LEN];

/* 状态结构体 包含状态转移函数 */
struct ptype
{
    int x,y;
    ptype();
    ptype(int x,int y)
        : x(x)
        , y(y)
    {}
    ptype operator+(ptype b)
    {
        return ptype(x+b.x,y+b.y);
    }
};

ptype dir[4] = {ptype(1,0),ptype(0,1),ptype(-1,0),ptype(0,-1)};

ptype stack[MAX_LEN];

int DFS(ptype start)
{
    int top = 0, cnt = 0;
    stack[top++] = start;
    map[start.x][start.y] = -1;
    while(top)
    {
        ptype cur = stack[--top];
        cnt++;
        for(int i = 0; i < 4; i++){
            ptype np = cur + dir[i];
            if(validate(np))
            {
                map[np.x][np.y] = -1;
                stack[top++] = np;
            }
        }
    }
    return cnt;
}

/* 剪枝 */
bool validate(ptype p)
{
    /*
    if(p.x < 0 || p.x >= n || p.y < 0 || p.y >= m) return false;
    if(map[p.x][p.y] == 0) return true;
    return false; 
    */
}