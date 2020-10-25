#pragma once

struct ListNode
{
    ListNode *pre, *nex;
    char val;
};

struct List
{
    ListNode *header, *trailer;
    ListNode nodes[7200000];
    int index;

    List()
    : index(2)
    {
        header = nodes+0;  //创建头哨兵节点
        trailer = nodes+1; //创建尾哨兵节点
        header->nex = trailer;
        header->pre = nullptr;
        trailer->pre = header;
        trailer->nex = nullptr;
    }

    ListNode *first() const { return header->nex; }
    ListNode *last() const { return trailer->pre; }
    char remove(ListNode *pos)
    {
        pos->pre->nex = pos->nex;
        pos->nex->pre = pos->pre;
        char e = pos->val;
        return e;
    }
    ListNode *insertAsFirst(const char &e)
    {
        return insertAsNext(header, e);
    }
    ListNode *insertAsLast(const char &e)
    {
        return insertAsPre(trailer, e);
    }
    ListNode* insertAsPre(ListNode* pos, char const& e)
    {
        nodes[index].val = e;
        nodes[index].pre = pos->pre;
        nodes[index].nex = pos;

        pos->pre->nex = nodes + index;
        pos->pre = nodes + index;
        ++index;
        return nodes+index-1;
    }
    ListNode* insertAsNext(ListNode* pos, char const& e)
    {
        nodes[index].val = e;
        nodes[index].nex = pos->nex;
        nodes[index].pre = pos;

        pos->nex->pre = nodes+index;
        pos->nex = nodes+index;
        ++index;
        return nodes+index-1;
    }
};