#pragma once
#include "BST.h"

#define Balanced(x) (stature((x).lc) == stature((x).rc))
#define BalFac(x) (stature((x).lc) - stature((x).rc))
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))

#define tallerChild(x) ( \
   stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /*左高*/ \
   stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( /*右高*/ \
   isLChild( * (x) ) ? (x)->lc : (x)->rc /*等高：与父亲x同侧者（zIg-zIg或zAg-zAg）优先*/ \
   ) \
   ) \
)

template <typename T>
class AVL : public BST<T>
{
public:
    binNodePosi(T) insert(const T& e) override
    {
        binNodePosi(T) & v = BST<T>::search(e);
        if(v) return v;
        binNodePosi(T) vv = v = new binNode<T>(e, BST<T>::_hot); ++binTree<T>::_size;
        for(binNodePosi(T) g = BST<T>::_hot; g; g = g->parent) 
        {
            if(!AvlBalanced(*g))
            {
                FromParentTo(*g) = BST<T>::rotateAt(tallerChild(tallerChild(g)));
                break;
            }
            else
                binTree<T>::updateHeight(g);
        }
        return vv;
    }
    bool remove(const T& e) override
    {
        binNodePosi(T) & v = BST<T>::search(e);
        if(!v) return false;
        removeAt(v,BST<T>::_hot); binTree<T>::_size--;
        for(binNodePosi(T) g = BST<T>::_hot; g; g = g->parent)
        {
            if(!AvlBalanced(*g))
            {
                g = FromParentTo(*g) = BST<T>::rotateAt(tallerChild(tallerChild(g)));
            }
            binTree<T>::updateHeight(g);
        }
        return true;
    }

};