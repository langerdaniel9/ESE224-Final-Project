#pragma once

#include "User.h"

#include <string>

using namespace std;

///////////////////////////////////////////////////

struct LLNode // TODO maybe use a template here??
{
    string username;
    string isbnReserved;
    int borrowBy;
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