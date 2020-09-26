#pragma once

#include "binNode.h"

template <typename T>
class binTree
{

public:
    binNodePosi(T) root;    // 树根节点

    binTree() : root(NULL){}
    ~binTree()
    {
        remove(root);
    }
protected:
    int remove(binNodePosi(T) curNode);
};