#pragma once

#include <string>

using namespace std;

///////////////////////////////////////////////////
// type for inserting to copy BST
struct copystruct
{
    int idfile;
    string isbnfile;
};

bool operator<(copystruct &cs1, copystruct cs2)
{
    return cs1.idfile < cs2.idfile;
}

bool operator>(copystruct &cs1, copystruct &cs2)
{
    return cs1.idfile > cs2.idfile;
}

///////////////////////////////////////////////////

bool operator<(string &s1, string s2)
{
    int val = s1.compare(s2);
    return (val == -1) ? true : false;
}

bool operator>(string &s1, string &s2)
{
    int val = s1.compare(s2);
    return (val == 1) ? true : false;
}

///////////////////////////////////////////////////

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