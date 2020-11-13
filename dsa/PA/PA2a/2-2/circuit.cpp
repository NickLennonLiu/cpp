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
    : childs(0)
    //, zero(nullptr)
    //, one(nullptr)
    , zero(-1)
    , one(-1)
    , cirs(nullptr)
    {}
    queue *cirs;
    int childs;
    //Node *zero, *one;
    int zero, one;
};

Node memory[23000000];
int applied = 0;

class Trie
{
    int root;
public:
    Trie()
    {
        //root = new Node();
        //root = &memory[applied++];
        root = applied++;
    }
    void insert(int id, char *a)
    {
        Node* cur = memory + root;
        for(int i = 0; i < 64; ++i)
        {
            cur->childs += 1;
            if(a[i] - '0')
            {
                if(-1 == cur->one)
                {
                    //cur->one = new Node();
                    //cur->one = &memory[applied++];
                    cur->one = applied++;
                }
                //cur = cur->one;
                cur = memory + cur->one;
            } else {
                if(-1 == cur->zero)
                {
                    //cur->zero = new Node();
                    //cur->zero = &memory[applied++];
                    cur->zero = applied++;
                }
                // cur = cur->zero;
                cur = memory + cur->zero;
            }
        }
        if(!cur->cirs)
            cur->cirs = new queue();
        cur->cirs->enqueue(id);
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
        cur->cirs->dequeue();
    }
    int find(char *a)
    {
        Node *cur = memory + root;
        for(int i = 0; i < 64; ++i)
        {
            if(a[i] - '0')
            {
                if(-1 != cur->zero && (memory[cur->zero].childs || i==63))
                    cur = memory + cur->zero;
                else
                    cur = memory + cur->one;   
            } else {
                if(-1 != cur->one && (memory[cur->one].childs || i==63))
                    cur = memory + cur->one;
                else
                    cur = memory + cur->zero;
            }
        }
        return cur->cirs->front();
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
        printf("%d\n", trie.find(cir[i]));
    }
    return 0;
}