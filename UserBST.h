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
    void findUser(struct node *node, string testUsername, string testPassword, User *result);
    void findUserType(struct node *node, string testUsername, string testPassword, string &userType);
    User *returnUser(struct node *node, string testUsername, string testPassword);
    bool userExists(struct node *node, string testUsername, string testPassword);
    void printInOrder(struct node *node);
    void printDetailsAboutUser(struct node *node, User *val);

public:
    // Parameters //
    struct node *root;

    // Functions //
    // Constructor
    UserBST();
    // Getter
    int size();
    // Binary Search Tree
    void addUser(User *toInsert);
    void deleteUser(User *toDelete);
    void findUser(string testUsername, string testPassword, User *result);
    void findUserType(string testUsername, string testPassword, string &userType);
    User *returnUser(string testUsername, string testPassword);
    void printInOrder();
    bool userExists(string testUsername, string testPassword);
    void printDetailsAboutUser(User *val);
};

UserBST::UserBST()
{
    this->root = NULL;
    this->treeSize = 0;
}

int UserBST::size()
{
    return this->treeSize;
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

node *getSuccessor(node *curr)
{
    while (curr->left != nullptr)
    {
        curr = curr->left;
    }
    return curr;
}

void findParent(node **current, User *toDelete, node **parent)
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

void UserBST::findUser(string testUsername, string testPassword, User *result)
{
    findUser(this->root, testUsername, testPassword, result);
}

void UserBST::findUser(struct node *node, string testUsername, string testPassword, User *result)
{
    if (node == NULL)
    {
        return;
    }
    else
    {
        if (testUsername == node->value->getUsername() && testPassword == node->value->getPassword())
        {
            result = node->value;
        }

        if (testUsername > node->value->getUsername())
        {
            findUser(node->right, testUsername, testPassword, result);
        }
        else
        {
            findUser(node->left, testUsername, testPassword, result);
        }
    }
}

User *UserBST::returnUser(string testUsername, string testPassword)
{
    return returnUser(this->root, testUsername, testPassword);
}

User *UserBST::returnUser(struct node *node, string testUsername, string testPassword)
{
    struct node *current = node;
    while (testUsername != current->value->getUsername() && testPassword != current->value->getPassword())
    {
        if (current == nullptr)
        {
            return nullptr;
        }

        if (testUsername > current->value->getUsername())
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    return current->value;
}

void UserBST::findUserType(string testUsername, string testPassword, string &userType)
{
    findUserType(this->root, testUsername, testPassword, userType);
}

void UserBST::findUserType(struct node *node, string testUsername, string testPassword, string &userType)
{
    if (node == NULL)
    {
        return;
    }
    else
    {
        if (testUsername == node->value->getUsername() && testPassword == node->value->getPassword())
        {
            userType = node->value->getType();
        }

        if (testUsername > node->value->getUsername())
        {
            findUserType(node->right, testUsername, testPassword, userType);
        }
        else
        {
            findUserType(node->left, testUsername, testPassword, userType);
        }
    }
}

void UserBST::printDetailsAboutUser(User *userToPrint) // Main Call
{
    /*
     * A librarian can search users by their usernames. Requirements:
     * If the target is a librarian, show his username and password only.
     * If the target is a reader, show his/her name, password, reader type (student or teacher) as well as the copies he/she is keeping currently.
     */

    printDetailsAboutUser(this->root, userToPrint);
}

void UserBST::printDetailsAboutUser(struct node *node, User *userToPrint) // Recursive
{
    if (node == NULL)
    {
        return;
    }
    else
    {
        if (userToPrint->getUsername() == node->value->getUsername())
        {
            // TODO - If target is a librarian, print the username and password

            // TODO - If target is a reader, print username, password, type, and copiesList
        }

        if (userToPrint->getUsername() > node->value->getPassword())
        {
            printDetailsAboutUser(node->right, userToPrint);
        }
        else
        {
            printDetailsAboutUser(node->left, userToPrint);
        }
    }
}

// Unnecessary

bool UserBST::userExists(string testUsername, string testPassword)
{
    return userExists(this->root, testUsername, testPassword);
}

bool UserBST::userExists(struct node *node, string testUsername, string testPassword)
{
    if (node == NULL)
    {
        return false;
    }
    else
    {
        if (testUsername == node->value->getUsername() && testPassword == node->value->getPassword())
        {
            return true;
        }

        if (testUsername > node->value->getUsername())
        {
            return userExists(node->right, testUsername, testPassword);
        }
        else
        {
            return userExists(node->left, testUsername, testPassword);
        }
    }
}
