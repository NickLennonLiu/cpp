#pragma once
#include "../Linear/Queue.h"
#include "../Linear/Stack.h"

#define binNodePosi(T) binNode<T>*
#define isRChild(x) (!isRoot(x) && (&(x) == (x).parent->rc))
#define isLChild(x) (!isRoot(x) && (&(x) == (x).parent->lc))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define isRoot(x) (!((x).parent))
#define stature(x) ((x) ? (x)->height : -1)

typedef int Rank;

template <typename T>
class binNode
{
    
public:
    T data;
    binNode<T> *parent, *lc, *rc;
    int height;
    int npl;

    binNode() : parent(NULL), lc(NULL), rc(NULL) ,height(0) {}
    binNode(T e, binNodePosi(T) parent = NULL, binNodePosi(T) lc = NULL, binNodePosi(T) rc = NULL, int h = 0)
    : parent(parent), lc(lc), rc(rc), height(h), data(e)    {}
    binNodePosi(T) insertAsLC(const T& e) 
    { return lc = new binNode(e, this); }
    binNodePosi(T) insertAsRC(const T& e) 
    { return rc = new binNode(e, this); }
    int size()
    {
        int s = 1;
        if(lc) s += lc->size();
        if(rc) s += rc->size();
        return s;
    }
    binNodePosi(T) succ()
    {
        binNodePosi(T) s = this;
        if( rc)
        {
            s = rc;
            while(s->lc) s = s->lc;
        } else {
            while(isRChild(*s)) s = s->parent;
            s = s->parent;
        }
        return s;
    }
    binNodePosi(T) pred()
    {
        binNodePosi(T) s = this;
        if( lc )
        {
            s = lc;
            while(s->rc) s = s->rc;
        } else {
            while(isLChild(*s)) s = s->parent;
            s = s->parent;
        }
        return s;
    }
    template <typename VST>
    void traversePre(VST& func)
    {   travPre(this, func);    }
    template <typename VST>
    void traverseIn(VST &func)
    {   travIn(this, func);     }
    template <typename VST>
    void traversePost(VST &func)
    {   travPost(this, func);   }
    template <typename VST>
    void travLevel(VST &func);
};

template <typename T> //在以S栈顶节点为根的子树中，找到最高左侧可见叶节点
static void gotoLeftmostLeaf(Stack<binNodePosi(T)> &S)
{                                      //沿途所遇节点依次入栈
    while (binNodePosi(T) x = S.top()) //自顶而下，反复检查当前节点（即栈顶）
        if (HasLChild(*x))
        { //尽可能向左
            if (HasRChild(*x))
                S.push(x->rc); //若有右孩子，优先入栈
            S.push(x->lc);     //然后才转至左孩子
        }
        else               //实不得已
            S.push(x->rc); //才向右
    S.pop();               //返回之前，弹出栈顶的空节点
}

template <typename T, typename VST>
void travPost(binNodePosi(T) x, VST &visit)
{                            //二叉树的后序遍历（迭代版）
    Stack<binNodePosi(T)> S; //辅助栈
    if (x)
        S.push(x); //根节点入栈
    while (!S.empty())
    {                             //x始终为当前节点
        if (S.top() != x->parent) ////若栈顶非x之父（而为右兄）
            gotoLeftmostLeaf(S);  //则在其右兄子树中找到HLVFL（相当于递归深入）
        x = S.pop();
        visit(x->data); //弹出栈顶（即前一节点之后继），并访问之
    }
}

template <typename T, typename VST> //元素类型、操作器
void travIn(binNodePosi(T) x, VST &visit)
{ //二叉树中序遍历（迭代版#4，无需栈或标志位）
    while (true)
        if (HasLChild(*x)) //若有左子树，则
            x = x->lc;     //深入遍历左子树
        else
        {                          //否则
            visit(x->data);        //访问当前节点，并
            while (!HasRChild(*x)) //不断地在无右分支处
                if (!(x = x->succ()))
                    return; //回溯至直接后继（在没有后继的末节点处，直接退出）
                else
                    visit(x->data); //访问新的当前节点
            x = x->rc;              //（直至有右分支处）转向非空的右子树
        }
}

//从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
template <typename T, typename VST> //元素类型、操作器
static void visitAlongVine(binNodePosi(T) x, VST &visit, Stack<binNodePosi(T)> &S)
{
    while (x)
    {
        visit(x->data); //访问当前节点
        S.push(x->rc);  //右孩子入栈暂存（可优化：通过判断，避免空的右孩子入栈）
        x = x->lc;      //沿左分支深入一层
    }
}

template <typename T, typename VST> //元素类型、操作器
void travPre(binNodePosi(T) x, VST &visit)
{                            //二叉树先序遍历算法（迭代版#2）
    Stack<binNodePosi(T)> S; //辅助栈
    while (true)
    {
        visitAlongVine(x, visit, S); //从当前节点出发，逐批访问
        if (S.empty())
            break;   //直到栈空
        x = S.pop(); //弹出下一批的起点
    }
}

template <typename T>
template <typename VST> //元素类型、操作器
void binNode<T>::travLevel(VST &visit)
{                            //二叉树层次遍历算法
    Queue<binNodePosi(T)> Q; //辅助队列
    Q.enqueue(this);         //根节点入队
    while (!Q.empty())
    { //在队列再次变空之前，反复迭代
        binNodePosi(T) x = Q.dequeue();
        visit(x->data); //取出队首节点并访问之
        if (HasLChild(*x))
            Q.enqueue(x->lc); //左孩子入队
        if (HasRChild(*x))
            Q.enqueue(x->rc); //右孩子入队
    }
}