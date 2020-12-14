#include <stdio.h>
using namespace std;

struct listnode
{
    listnode *next;
    int val;
    listnode()
    : next(nullptr)
    {}
    listnode(int e)
    : val(e)
    , next(nullptr)
    {}
};

struct queue
{
    listnode *header, *last;
    void enqueue(int e)
    {
        last = last->next = new listnode(e);
    }
    int front()
    {
        return header->next->val;
    }
    void dequeue()
    {
        listnode* tmp = header;
        header = header->next;
        delete tmp;
    }
    bool empty()
    {
        return header == last;
    }
};

struct Node
{
    int zero, one;  // 对应左孩子lc与右孩子rc
    int childs;     // 终止节点数目
};

Node memory[28000000];
int applied = 1;

queue leafs[500010];
int leaf_cnt = 0;

class Trie
{
public:
    int root;
    Trie()
    {
        root = applied++;
    }
    // 插入元件
    void insert(int id, char *a)
    {
        Node* cur = memory + root;
        for(int i = 0; i < 64; ++i)
        {
            cur->childs++;
            if(a[i] - '0')
            {
                if(0 == cur->one)   // 若子节点尚未分配空间则分配位置
                {
                    cur->one = applied++;
                }
                cur = memory + cur->one;
            } else {
                if(0 == cur->zero)  // 若子节点尚未分配空间则分配位置
                {
                    cur->zero = applied++;
                }
                cur = memory + cur->zero;
            }
        }
        if(0 == cur->one)   // 生成叶子节点
        {
            cur->one = ++leaf_cnt;
            leafs[cur->one].last = leafs[cur->one].header = new listnode();
        }
        leafs[cur->one].enqueue(id);    // 元件编号入队（FIFO）
        cur->childs++;
    }
    // 删除元件
    void remove(char *a)
    {
        Node *cur = memory + root;
        for (int i = 0; i < 64; ++i)
        {
            cur->childs--;
            if (a[i] - '0')
                cur = memory + cur->one;
            else
                cur = memory + cur->zero;
        }
        leafs[cur->one].dequeue();
        cur->childs--;
    }
    //　查找符合条件的编号最小的元件
    int find(int j, char *a)
    {
        Node *cur = memory + root;
        for(int i = 0; i < 64; ++i)
        {
            if(a[i] - '0')
            {   
                if(0 != cur->zero && (memory + cur->zero)->childs)
                    cur = memory + cur->zero;
                else
                    cur = memory + cur->one;   
            } else {
                if(0 != cur->one && (memory + cur->one)->childs)
                    cur = memory + cur->one;
                else
                    cur = memory + cur->zero;
            }
        }
        
        return (leafs[cur->one].front() == j) 
                ? leafs[cur->one].header->next->next->val 
                : leafs[cur->one].front();
    }
};

char cir[500001][70];
int n,k;
Trie trie;

int main()
{
    scanf("%d %d",&n,&k);
    for(int i = 0; i < n; ++i)
        scanf("%s", cir[i]);
    
    for(int i = 0; i <= k && i < n; ++i) // 注意预插入的时候留最后一个节点，到遍历的时候再插入
        trie.insert(i, cir[i]);

    for(int i = 0; i < n; ++i)
    {
        if(i-k-2 >= 0)
            trie.remove(cir[i-k-2]);
        if(i+k+1 < n)
            trie.insert(i+k+1, cir[i+k+1]);
        printf("%d\n", trie.find(i,cir[i]));
    }
    return 0;
}