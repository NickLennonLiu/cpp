#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;

struct Node
{
    int index;
};

Node nodes[14400000];
Node *pre[14400000],*nex[14400000];
char node_val[14400000];

struct List
{
    static int _index;
    Node *header, *trailer;
};

char a[100], b[100];

int main()
{
    cout << sizeof(Node) << " " << sizeof(Node*);
    return 0;
}