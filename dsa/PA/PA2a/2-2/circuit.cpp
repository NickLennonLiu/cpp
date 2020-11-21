//#include <iostream>
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
    /*
    queue()
    {
        header = new listnode();
        last = header;
    }
    */
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
    /*
    Node()
    : zero(0)
    , one(0)
    , childs(0)
    {}
    */
    int zero, one;
    int childs;
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
    void insert(int id, char *a)
    {
        Node* cur = memory + root;
        for(int i = 0; i < 64; ++i)
        {
            cur->childs++;
            if(a[i] - '0')
            {
                if(0 == cur->one)
                {
                    cur->one = applied++;
                }
                cur = memory + cur->one;
            } else {
                if(0 == cur->zero)
                {
                    cur->zero = applied++;
                }
                cur = memory + cur->zero;
            }
        }
        if(0 == cur->one)
        {
            cur->one = ++leaf_cnt;
            leafs[cur->one].last = leafs[cur->one].header = new listnode();
        }
        leafs[cur->one].enqueue(id);
        cur->childs++;
    }
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
    int find(int i, char *a)
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
        
        return (leafs[cur->one].front() == i) 
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