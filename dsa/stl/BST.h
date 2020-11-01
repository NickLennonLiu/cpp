#pragma once 
#include "binTree.h"

template <typename T>
class BST : public binTree<T>
{ //由binTree派生BST模板类
protected:
    binNodePosi(T) _hot;      //“命中”节点的父亲
    binNodePosi(T) connect34( //按照“3 + 4”结构，联接3个节点及四棵子树
        binNodePosi(T), binNodePosi(T), binNodePosi(T),
        binNodePosi(T), binNodePosi(T), binNodePosi(T), binNodePosi(T));
    binNodePosi(T) rotateAt(binNodePosi(T) x);             //对x及其父亲、祖父做统一旋转调整
public:                                                    //基本接口：以virtual修饰，强制要求所有派生类（BST变种）根据各自的规则对其重写
    virtual binNodePosi(T) & search(const T &e);           //查找
    virtual binNodePosi(T) insert(const T &e);             //插入
    virtual bool remove(const T &e);                       //删除
                                                           /*DSA*/
    /*DSA*/ void stretchToLPath() { stretchByZag(_root); } //借助zag旋转，转化为左向单链
    /*DSA*/ void stretchToRPath() { stretchByZig(_root); } //借助zig旋转，转化为右向单链
    /*DSA*/ void stretch();
};

template <typename T>
binNodePosi(T) BST<T>::connect34(
    binNodePosi(T) a, binNodePosi(T) b, binNodePosi(T) c,
    binNodePosi(T) t0, binNodePosi(T) t1, binNodePosi(T) t2, binNodePosi(T) t3)
{
    a->lc = t0; t0->parent = a;
    a->rc = t1; t1->parent = a;
    c->lc = t2; t2->parent = c;
    c->rc = t3; t3->parent = c;
    b->lc = a; a->parent = b;
    b->rc = c; c->parent = b;
    updateHeight(a);
    updateHeight(c);
    updateHeight(b);
    return b;
}

template <typename T>
binNodePosi(T)  BST<T>::rotateAt(binNodePosi(T) v)
{
    binNodePosi(T) p = v->parent;
    binNodePosi(T) g = p->parent;
    if(isLChild(*p))
    {
        if(isLChild(*v)) {
            p->parent = g->parent;
            return connect34(v,p,g,v->lc,v->rc,p->rc, g->rc);
        } else {
            v->parent = g->parent;
            return connect34(p,v,g,p->lc,v->lc,v->rc,g->rc);
        }
    } else {
        if (isLChild(*v)) {
            v->parent = g->parent;
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
        else {
            p->parent = g->parent;
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        }
    }
}

template <typename T>
binNodePosi(T) & search(const T &e)
{

}