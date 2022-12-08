#pragma once

#include "User.h"

#include <string>

using namespace std;

///////////////////////////////////////////////////

// TODO - Check if this is actually necessary, since string already has overloading
// bool operator<(string &s1, string s2)
// {
//     int val = s1.compare(s2);
//     return (val == -1) ? true : false;
// }

// bool operator>(string &s1, string &s2)
// {
//     int val = s1.compare(s2);
//     return (val == 1) ? true : false;
// }

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

///////////////////////////////////////////////////

struct LLNode
{
    string username;
    LLNode *next;
    LLNode() : next(nullptr) {}
    LLNode(string x) : username(x), next(nullptr) {}
    LLNode(string x, LLNode *next) : username(x), next(next) {}
};

///////////////////////////////////////////////////

struct node
{
    User *value;
    struct node *left;
    struct node *right;

    node() {}
};

///////////////////////////////////////////////////