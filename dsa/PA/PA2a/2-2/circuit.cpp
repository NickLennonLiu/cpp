#include <iostream>
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
    queue()
    {
        header = new listnode();
        last = header;
    }
    void enqueue(int e)
    {
        last->next = new listnode(e);
        last = last->next;
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
};

struct Node
{
    Node()
    : //childs(0)
     zero(-1)
    , one(-1)
    //, cirs(nullptr)
    , queueid(0)
    {}
    //queue *cirs;
    int queueid;
    //int childs;
    //Node *zero, *one;
    int zero, one;
};

int hasChild[23000000];

Node memory[23000000];
int applied = 0;

//queue *leafs[5000010];
queue leafs[500010];
int leaf_cnt = 0;

class Trie
{
    int root;
public:
    Trie()
    {
        root = applied++;
    }
    void insert(int id, char *a)
    {
        Node* cur = memory + root;
        for(int i = 0; i < 64; ++i)
        {
            //cur->childs += 1;
            hasChild[cur - memory] += 1;
            if(a[i] - '0')
            {
                if(-1 == cur->one)
                {
                    cur->one = applied++;
                }
                cur = memory + cur->one;
            } else {
                if(-1 == cur->zero)
                {
                    cur->zero = applied++;
                }
                cur = memory + cur->zero;
            }
        }
        if(!cur->queueid)
        {
            //leafs[++leaf_cnt] = new queue();
            cur->queueid = ++leaf_cnt;
        }
        //cur->cirs->enqueue(id);
        leafs[cur->queueid].enqueue(id);
    }
    void remove(char *a)
    {
        Node *cur = memory + root;
        for (int i = 0; i < 64; ++i)
        {
            //cur->childs--;
            hasChild[cur - memory] --;
            if (a[i] - '0')
                cur = memory + cur->one;
            else
                cur = memory + cur->zero;
        }
        //cur->cirs->dequeue();
        leafs[cur->queueid].dequeue();
    }
    int find(int i, char *a)
    {
        Node *cur = memory + root;
        for(int i = 0; i < 64; ++i)
        {
            if(a[i] - '0')
            {
                if(-1 != cur->zero && (hasChild[cur->zero]|| i==63))
                    cur = memory + cur->zero;
                else
                    cur = memory + cur->one;   
            } else {
                if(-1 != cur->one && (hasChild[cur->one]|| i==63))
                    cur = memory + cur->one;
                else
                    cur = memory + cur->zero;
            }
        }
        //return (cur->cirs->front() == i) ? cur->cirs->header->next->next->val : cur->cirs->front();
        return (leafs[cur->queueid].front() == i) 
                ? leafs[cur->queueid].header->next->next->val 
                : leafs[cur->queueid].front();
    }
};

char cir[500001][70];
int n,k;
Trie trie;

int main()
{
    cin >> n >> k;
    cin.getline(cir[0],64);
    for(int i = 0; i < n; ++i)
        cin.getline(cir[i],80);
    
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