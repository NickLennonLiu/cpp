#pragma once

#include "binNode.h"
#include "Stack.h"
#include "Queue.h"

#define sibling(p) /*兄弟*/ \
    (isLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)

#define uncle(x) /*叔叔*/ \
    (isLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)

#define FromParentTo(x) /*来自父亲的引用*/ \
    (isRoot(x) ? _root : (isLChild(x) ? (x).parent->lc : (x).parent->rc))

template <typename T>
class binTree
{
protected:
    binNodePosi(T) _root;    // 树根节点
    int _size;
    int _height;
    virtual int updateHeight(binNodePosi(T) x)
    {
        int height = -1;
        if(lc) height = max(height, lc->height);
        if(rc) height = max(height, rc->height);
        return x->height = 1 + height;
    }
    void updateHeightAbove(binNodePosi(T) x)
    {
        while(x)
        {
            updateHeight(x);
            x = x->parent;
        }
    }
public:
    
    // 构造函数：空树
    binTree(): _size(0), _height(0), _root(nullptr) { }
    ~binTree() { if (0 < _size) remove(_root); }
    int size() const {return _size;}
    int height() const {return _height;}
    binNodePosi(T) root() const {return _root;}
    binNodePosi(T) insertAsRoot( T const & e)
    {
        _size = 1;
        return _root = new binNode<T>(e);
    }
    binNodePosi(T) insertAsRC(binNodePosi(T) x, T const& e)
    {
        _size++;
        x->insertAsRC(e);
        updateHeightAbove(x);
        return x->rc;
    }
    binNodePosi(T) insertAsLC(binNodePosi(T) x, T const &e)
    {
        _size++;
        x->insertAsLC(e);
        updateHeightAbove(x);
        return x->lc;
    }
    binNodePosi(T) attachAsRC(binNodePosi(T) x, binTree<T>* & S)
    {
        if(x->rc = S->_root)
            x->rc->parent = x;
        _size += S->_size;
        updateHeightAbove(x);
        S->_root = nullptr;
        S->_size = 0;
        delete S;
        return x;
    }
    binNodePosi(T) attachAsLC(binNodePosi(T) x, binTree<T> *&S)
    {
        if (x->lc = S->_root)
            x->lc->parent = x;
        _size += S->_size;
        updateHeightAbove(x);
        S->_root = nullptr;
        S->_size = 0;
        delete S;
        return x;
    }
    int remove( binNodePosi(T) x)
    {
        FromParentTo(*x) = nullptr;
        updateHeightAbove(x->parent);
        int n = removeAt(x);
        _size -= n;
        return n;
    }
    binTree<T>* secede(binNodePosi(T) x)
    {
        FromParentTo(*x) = nullptr;
        updateHeightAbove(x->parent);
        binTree<T>* S = new binTree<T>;
        S->_root = x;
        x->parent = nullptr;
        S->_size = x->size();
        _size -= S->_size;
        return S;
    }
    template <typename VST> //操作器
    void travLevel ( VST& visit ) { if ( _root ) _root->travLevel ( visit ); } //层次遍历
    template <typename VST> //操作器
    void travPre ( VST& visit ) { if ( _root ) _root->travPre ( visit ); } //先序遍历
    template <typename VST> //操作器
    void travIn ( VST& visit ) { if ( _root ) _root->travIn ( visit ); } //中序遍历
    template <typename VST> //操作器
    void travPost ( VST& visit ) { if ( _root ) _root->travPost ( visit ); } //后序遍历
protected:
   
};

template <typename T>
static int removeAt(binNodePosi(T) x)
{
    if (!x) return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    /* 此处需要释放 x->data和 x的空间*/
    return n;
}