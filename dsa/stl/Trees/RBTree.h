#include "binNode.h"
#include "binTree.h"
#include "BST.h"

template <typename T>
class RedBlack : public BST<T>
{
public:
    binNodePosi(T) insert(const T& e);
    bool remove(const T e);
protected:
    void solveDoubleRed(binNodePosi(T) x);
    void solveDoubleBlack(binNodePosi(T) x);
    int updateHeight(binNodePosi(T) x);
};

template <typename T>
int RedBlack<T>::updateHeight(binNodePosi(T) x)
{
    x->height = max(stature(x->lc), stature)
}
