#pragma once

#include <string>

using namespace std;

// type for inserting to copy BST
struct copystruct
{
    int idfile;
    string isbnfile;
};
//

template <typename Type>
struct TreeNode
{
    Type val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(nullptr), left(nullptr), right(nullptr) {}
    TreeNode(Type x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(Type x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};