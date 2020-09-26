#pragma once

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val = 0) : val(val), left(nullptr), right(nullptr) {}
};