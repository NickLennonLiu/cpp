#pragma once
#include <iostream>
using namespace std;

struct Node
{
    int index;
};

struct List
{
    Node *header, *trailer;

    static Node nodes[10000000];
    static char node_char[5000000];
    static Node *pre[10000000], *nex[10000000];

    static int _index;

    List()
    {
        nodes[_index].index = _index;
        header = nodes + _index++;  //创建头哨兵节点
        nodes[_index].index = _index;
        trailer = nodes + _index++; //创建尾哨兵节点
        nex[header->index] = trailer;
        pre[header->index] = nullptr;
        pre[trailer->index] = header;
        nex[trailer->index] = nullptr;
    }

    Node *first() { return nex[header->index]; }
    Node *last() { return pre[trailer->index]; }
    char remove(Node *pos)
    {
        //pos->pre->nex = pos->nex;
        nex[pre[pos->index]->index] = nex[pos->index];
        //pos->nex->pre = pos->pre;
        pre[nex[pos->index]->index] = pre[pos->index];
        char e = node_char[pos->index];
        return e;
    }
    Node *insertAsFirst(const char &e)
    {
        return insertAsNext(header, e);
    }
    Node *insertAsLast(const char &e)
    {
        return insertAsPre(trailer, e);
    }
    Node *insertAsPre(Node *pos, char const &e)
    {
        nodes[_index].index = _index;
        node_char[_index] = e;
        pre[_index] = pre[pos->index];
        nex[_index] = pos;

        //pos->pre->nex = nodes + _index;
        nex[pre[pos->index]->index] = nodes + _index;
        //pos->pre = nodes + _index;
        pre[pos->index] = nodes + _index;
        ++_index;
        return nodes + _index - 1;
    }
    Node *insertAsNext(Node *pos, char const &e)
    {
        nodes[_index].index = _index;
        node_char[nodes[_index].index] = e;
        nex[nodes[_index].index] = nex[pos->index];
        pre[nodes[_index].index] = pos;

        //pos->nex->pre = nodes + index;
        pre[nex[pos->index]->index] = nodes + _index;
        //pos->nex = nodes + _index;
        nex[pos->index] = nodes + _index;
        ++_index;
        return nodes + _index - 1;
    }
};