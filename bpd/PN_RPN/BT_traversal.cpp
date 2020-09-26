#include "TreeNode.h"
#include <stack>
#include <queue>
#include <iostream>

// https://blog.csdn.net/My_Jobs/article/details/43451187
// https://en.wikipedia.org/wiki/Tree_traversal

TreeNode* genTree()
{
    TreeNode* root = new TreeNode();
    return root;
}

void visit(TreeNode* node)
{
    // Do something
    std::cout << node -> val << std::endl;
    return;
}

// Pre-order 先序遍历
void NLR(TreeNode* root)
{
    std::stack<TreeNode*> stack;
    TreeNode* cur = root;
    while(cur || !stack.empty())
    {
        if(cur)
        {
            visit(cur);
            stack.push(cur);
            cur = cur->left;
        } else {
            cur = stack.top();
            stack.pop();
            cur = cur->right;
        }
    }
}

// In-order 中序遍历
void LNR(TreeNode* root)
{
    std::stack<TreeNode *> stack;
    TreeNode *cur = root;
    while (cur || !stack.empty())
    {
        if (cur)
        {
            stack.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = stack.top();
            visit(cur);
            stack.pop();
            cur = cur->right;
        }
    }
}

// Post-order 后序遍历
void LRN(TreeNode* root)
{
    std::queue<TreeNode*> queue;
    TreeNode* cur = root;
    while(true)
    {
        if(cur)
        {
            
        }
    }
}