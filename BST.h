#pragma once
#include <iostream>
#include <fstream>
#include "User.h"
#include "Book.h"
#include "BookCopies.h"

using namespace std;

template <typename Type>
struct TreeNode {
    Type val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(Type x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(Type x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

bool operator<(string& lhs, string rhs)
{
    int val = lhs.compare(rhs);
    if (val == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator>(string& lhs, string& rhs)
{
    int val = lhs.compare(rhs);
    if (val == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator<(User& u1, User& u2)
{
    int val = u1.getUserName().compare(u2.getUserName());

    if (val == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator>(User& u1, User& u2)
{
    int val = u1.getUserName().compare(u2.getUserName());
    if (val == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator<(Book& b1, Book& b2)
{
    int val = b1.getIsbn().compare(b2.getIsbn());

    if (val == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator>(Book& b1, Book& b2)
{
    int val = b1.getIsbn().compare(b2.getIsbn());
    if (val == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator<(BookCopy& bc1, BookCopy& bc2)
{
    return bc1.getID() < bc2.getID();
}

bool operator>(BookCopy& bc1, BookCopy& bc2)
{
    return bc1.getID() > bc2.getID();
}

template <typename Type>
class BST {
public:
    BST<Type>() {};

    // Binary Tree Functions
    TreeNode<Type>* root = NULL;

    // Adding an element in Binary Search Tree
    TreeNode<Type>* nodeInsert(TreeNode<Type>* root, Type element) {
        if (root == NULL) {
            root = new TreeNode<Type>(element);
            return root;
        }

        if (element < root->val) {
            root->left = nodeInsert(root->left, element);
        }
        else if (element > root->val) {
            root->right = nodeInsert(root->right, element);
        }

        return root;
    }

    void nodeInsert(Type element) {
        root = nodeInsert(root, element);
    }

    // Deleting an element from Binary Search Tree
    TreeNode<Type>* deleteNode(TreeNode<Type>* root, Type element) {
        if (root == NULL) {                             // Base case => deleting the root
            return root;
        }

        if (element < root->val) {                      // Finding which node to delete
            root->left = deleteNode(root->left, element);
        }
        else if (element > root->val) {
            root->right = deleteNode(root->right, element);
        }
        else {
            if (root->left == NULL) {
                TreeNode<Type>* aux = root->right;
                delete(root);
                return aux;
            }
            else if (root->right == NULL) {
                TreeNode<Type>* aux = root->left;
                delete(root);
                return aux;
            }

            TreeNode<Type>* toGetDeleted = inOrderSuccessor(root->right);                     // The deleting here does not work!
            root->val = toGetDeleted->val;
            root->right = deleteNode(root->right, toGetDeleted->val);
        }

        return root;
    }

    void deleteNode(Type element) {
        root = deleteNode(root, element);
    }

    TreeNode<Type>* inOrderSuccessor(TreeNode<Type>* root) {
        TreeNode<Type>* successor = root;
        while ((successor && successor->left) != NULL) {
            successor = successor->left;
        }

        return successor;
    }

    void binarySearch(TreeNode<Type>* root, Type element) {
        if (root == NULL) {
            cout << root->val << endl;
        }

        if (element < root->val) {
            root->left = nodeInsert(root->left, element);
        }
        else if (element > root->val) {
            root->right = nodeInsert(root->right, element);
        }
    }

    void inorderTraversal(TreeNode* root) {
        TreeNode* temp = root;
        if (temp == NULL) {
            return;
        }

        inorderTraversal(temp->left);               // visit left child
        cout << temp->val << " ";                   // visit current node
        inorderTraversal(temp->right);              // visit right child
    }

    void inOrderSearchRecursive(TreeNode<Book>* root, string searchTerm, vector<Book>& matches, bool TorC) {
        if (root == NULL) {
            return;
        }

        inOrderSearchRecursive(root->left, searchTerm, matches, TorC);               // visit left child
        if (TorC) {
            string s = root->val.getTitle();
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);
            if (s.find(searchTerm) != string::npos) {
                matches.push_back(root->val);
            }
        }
        else {
        
        }
        inOrderSearchRecursive(root->right, searchTerm, matches, TorC);              // visit right child
    }

    void inOrderSearchMain(TreeNode<Type>* root, string element) {                    // used for each cause (either title or category from searchBook)
        vector<Type> matches;
        string searchTerm;
        inOrderSearchRecursive(root, searchTerm, matches);


    }
};