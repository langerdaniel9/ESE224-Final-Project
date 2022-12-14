#pragma once

#include "Structs.h"
#include "User.h"
#include "Book.h"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class UserBST
{

private:
    // Parameters //
    int treeSize;

    // Functions //
    void addUser(struct node **node, User *val);
    void deleteUser(struct node **node, User *val);
    template <typename T>
    User *returnUser(struct node *node, T testUsername, T testPassword);
    template <typename T>
    User *returnUser(struct node *node, T testUsername);
    void printInOrder(struct node *node);

    // Helper Functions //
    node *getSuccessor(node *curr);
    void findParent(node **current, User *toDelete, node **parent);

public:
    // Parameters //
    struct node *root;

    // Functions //
    // Constructor
    UserBST();
    // Binary Search Tree
    void addUser(User *toInsert);
    void deleteUser(User *toDelete);
    template <typename T>
    User *returnUser(T testUsername);
    template <typename T>
    User *returnUser(T testUsername, T testPassword);
    void printInOrder();
};

UserBST::UserBST()
{
    this->root = NULL;
    this->treeSize = 0;
}

void UserBST::addUser(User *toInsert)
{
    addUser(&(this->root), toInsert);
}

void UserBST::addUser(struct node **node, User *toInsert)
{

    if (*node == NULL)
    {
        struct node *tmp = new struct node;
        tmp->value = toInsert;
        tmp->left = NULL;
        tmp->right = NULL;
        *node = tmp;

        this->treeSize++;
    }
    else
    {
        if (toInsert->getUsername() > (*node)->value->getUsername())
        {
            addUser(&(*node)->right, toInsert);
        }
        else
        {
            addUser(&(*node)->left, toInsert);
        }
    }
}

void UserBST::deleteUser(User *toDelete)
{
    deleteUser(&(this->root), toDelete);
}

node *UserBST::getSuccessor(node *curr)
{
    while (curr->left != nullptr)
    {
        curr = curr->left;
    }
    return curr;
}

void UserBST::findParent(node **current, User *toDelete, node **parent)
{
    // traverse the tree and search for the key
    while ((*current) != nullptr && (*current)->value->getUsername() != toDelete->getUsername())
    {
        // update the parent to the current node
        (*parent) = (*current);

        // if the given key is less than the current node, go to the left subtree
        // otherwise, go to the right subtree
        if (toDelete->getUsername() < (*current)->value->getUsername())
        {
            *current = (*current)->left;
        }
        else
        {
            *current = (*current)->right;
        }
    }
}

void UserBST::deleteUser(struct node **node, User *toDelete)
{
    struct node *parent = nullptr;
    struct node *current = (*node);

    findParent((&current), toDelete, (&parent));

    if (current == nullptr)
    {
        return;
    }

    // Three cases //
    // Case 1: The current node has no children
    if (current->left == nullptr && current->right == nullptr)
    {
        // if the node to be deleted is not a root node, then set its
        // parent left/right child to null
        if (current != (*node))
        {
            if (parent->left == current)
            {
                parent->left = nullptr;
            }
            else
            {
                parent->right = nullptr;
            }
        }
        // if the tree has only a root node, set it to null
        else
        {
            node = nullptr;
        }

        delete (current);
    }

    // Case 2: The current node has two children
    else if (current->left && current->right)
    {
        // find its inorder successor node
        struct node *successor = getSuccessor(current->right);

        // store successor value
        User *val = successor->value;

        // recursively delete the successor. Note that the successor
        // will have at most one child (right child)
        deleteUser(node, successor->value);

        // copy value of the successor to the current node
        current->value = val;
    }

    // Case 3: The current node has one child
    else
    {
        // choose a child node
        struct node *child = (current->left) ? current->left : current->right;

        // if the node to be deleted is not a root node, set its parent
        // to its child
        if (current != (*node))
        {
            if (current == parent->left)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
        }

        // if the node to be deleted is a root node, then set the root to the child
        else
        {
            (*node) = child;
        }

        delete (current);
    }

    this->treeSize--;
}

void UserBST::printInOrder()
{
    printInOrder(this->root);
    cout << endl;
}

void UserBST::printInOrder(struct node *node)
{
    if (node != NULL)
    {
        printInOrder(node->left);
        std::cout << "Username: " << node->value->getUsername()
                  << " Password: " << node->value->getPassword()
                  << " Usertype: " << node->value->getType() << endl;

        printInOrder(node->right);
    }
}

template <typename T>
User *UserBST::returnUser(T testUsername, T testPassword)
{
    return returnUser(this->root, testUsername, testPassword);
}

template <typename T>
User *UserBST::returnUser(struct node *node, T testUsername, T testPassword)
{
    struct node *current = node;
    if (current == nullptr)
    {
        return nullptr;
    }
    while (testUsername != current->value->getUsername() || testPassword != current->value->getPassword())
    {
        if (testUsername > current->value->getUsername())
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }

        if (current == nullptr)
        {
            return nullptr;
        }
    }
    return current->value;
}

template <typename T>
User *UserBST::returnUser(T testUsername)
{
    return returnUser(this->root, testUsername);
}

template <typename T>
User *UserBST::returnUser(struct node *node, T testUsername)
{
    struct node *current = node;
    if (current == nullptr)
    {
        return nullptr;
    }
    while (testUsername != current->value->getUsername())
    {
        if (testUsername > current->value->getUsername())
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }

        if (current == nullptr)
        {
            return nullptr;
        }
    }
    return current->value;
}
