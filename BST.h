#pragma once

#include "User.h"
#include "Book.h"
#include "BookCopy.h"

#include <iostream>
#include <fstream> // unnecessary?

using namespace std;

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

// Overload all comparison operators for string, user, book, and book copy //

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

bool operator<(User &u1, User &u2)
{
    int val = u1.getUserName().compare(u2.getUserName());
    return (val == -1) ? true : false;
}

bool operator>(User &u1, User &u2)
{
    int val = u1.getUserName().compare(u2.getUserName());
    return (val == 1) ? true : false;
}

bool operator<(Book &b1, Book &b2)
{
    int val = b1.getIsbn().compare(b2.getIsbn());
    return (val == -1) ? true : false;
}

bool operator>(Book &b1, Book &b2)
{
    int val = b1.getIsbn().compare(b2.getIsbn());
    return (val == 1) ? true : false;
}

bool operator<(BookCopy &bc1, BookCopy &bc2)
{
    return bc1.getID() < bc2.getID();
}

bool operator>(BookCopy &bc1, BookCopy &bc2)
{
    return bc1.getID() > bc2.getID();
}

/////////////////////////////////////////////////////////////////////////////

template <typename Type>
class BST
{
public:
    BST<Type>(){};

    // Binary Tree Functions
    TreeNode<Type> *root = NULL;

    // Adding an element in Binary Search Tree
    TreeNode<Type> *nodeInsert(TreeNode<Type> *root, Type element)
    {
        if (root == NULL)
        {
            root = new TreeNode<Type>(element);
            return root;
        }

        if (element < root->val)
        {
            root->left = nodeInsert(root->left, element);
        }
        else if (element > root->val)
        {
            root->right = nodeInsert(root->right, element);
        }

        return root;
    }

    void nodeInsert(Type element)
    {
        root = nodeInsert(root, element);
    }

    // Deleting an element from Binary Search Tree
    TreeNode<Type> *deleteNodeUser(TreeNode<Type> *root, Type element)
    {
        if (root == NULL)
        { // Base case => deleting the root
            return root;
        }

        if (element < root->val)
        { // Finding which node to delete
            root->left = deleteNode(root->left, element);
        }
        else if (element > root->val)
        {
            root->right = deleteNode(root->right, element);
        }
        else
        {
            if (root->left == NULL)
            {
                TreeNode<Type> *aux = root->right;
                delete (root);
                return aux;
            }
            else if (root->right == NULL)
            {
                TreeNode<Type> *aux = root->left;
                delete (root);
                return aux;
            }

            TreeNode<Type> *toGetDeleted = inOrderSuccessor(root->right); // The deleting here does not work!
            root->val = toGetDeleted->val;
            root->right = deleteNode(root->right, toGetDeleted->val);
        }

        return root;
    }
    TreeNode<Type> *deleteNodeBook(TreeNode<Type> *root, Type element)
    {
        if (root == NULL)
        { // Base case => deleting the root
            return root;
        }

        if (element < root->val)
        { // Finding which node to delete
            root->left = deleteNode(root->left, element);
        }
        else if (element > root->val)
        {
            root->right = deleteNode(root->right, element);
        }
        else
        {
            if (root->left == NULL)
            {
                TreeNode<Type> *aux = root->right;
                delete (root);
                return aux;
            }
            else if (root->right == NULL)
            {
                TreeNode<Type> *aux = root->left;
                delete (root);
                return aux;
            }

            TreeNode<Type> *toGetDeleted = inOrderSuccessor(root->right); // The deleting here does not work!
            root->val = toGetDeleted->val;
            root->right = deleteNode(root->right, toGetDeleted->val);
        }

        return root;
    }
    void deleteNode(Type element)
    {
        root = deleteNode(root, element);
    }

    TreeNode<Type> *inOrderSuccessor(TreeNode<Type> *root)
    {
        TreeNode<Type> *successor = root;
        while ((successor && successor->left) != NULL)
        {
            successor = successor->left;
        }

        return successor;
    }

    void binarySearch(TreeNode<Type> *root, Type element)
    {
        if (root == NULL)
        {
            cout << root->val << endl;
        }

        if (element < root->val)
        {
            root->left = nodeInsert(root->left, element);
        }
        else if (element > root->val)
        {
            root->right = nodeInsert(root->right, element);
        }
    }

    void inorderTraversal(TreeNode *root)
    {
        TreeNode *temp = root;
        if (temp == NULL)
        {
            return;
        }

        inorderTraversal(temp->left);  // visit left child
        cout << temp->val << " ";      // visit current node
        inorderTraversal(temp->right); // visit right child
    }

    void inOrderSearchRecursive(TreeNode<Book> *root, string searchTerm, vector<Book> &matches, bool TorC)
    {
        if (root == NULL)
        {
            return;
        }

        // visit left child
        inOrderSearchRecursive(root->left, searchTerm, matches, TorC);

        /********************************/
        string s;
        if (TorC)
        {
            s = root->val.getTitle();
        }
        else
        {
            s = root->val.getCategory();
        }

        transform(s.begin(), s.end(), s.begin(), ::tolower);
        transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);
        if (s.find(searchTerm) != string::npos)
        {
            matches.push_back(root->val);
        }
        /********************************/

        // visit right child
        inOrderSearchRecursive(root->right, searchTerm, matches, TorC);
    }

    void inOrderSearch(TreeNode<Type> *root, string searchTerm, bool TitleOrCategory)
    {
        //// Make array for result of search
        vector<Type> matches;
        matches.clear();

        //// Search for matches and add them to the array
        inOrderSearchRecursive(root, searchTerm, matches, TitleOrCategory);

        //// Compiling the results

        // Separate matches into two separate vectors, one for available books and one for unavailable
        vector<Book> availableMatches;
        vector<Book> unavailableMatches;
        availableMatches.clear();
        unavailableMatches.clear();

        for (int i = 0; i < matches.size(); i++)
        {
            // FIXME - replace this with correct logic
            if (matches.at(i).getReaderName() == "")
            {
                // If nobody has checked out this book -> it is available
                availableMatches.push_back(matches.at(i));
            }
            else
            {
                unavailableMatches.push_back(matches.at(i));
            }
        }

        // Sort availableMatches
        if (availableMatches.size() >= 2)
        {
            // sorting by title
            for (int i = 0; i < availableMatches.size() - 1; i++)
            {
                for (int j = 0; j < (availableMatches.size() - i - 1); j++)
                {
                    int titleCompare = availableMatches.at(j).getTitle().compare(availableMatches.at(j + 1).getTitle());
                    if (titleCompare > 0)
                    {
                        swap(availableMatches.at(j), availableMatches.at(j + 1));
                    }
                }
            }

            // sorting by ID
            quickSort(availableMatches, 0, availableMatches.size() - 1);
        }

        // Sort unavailableMatches
        for (int i = 0; i < unavailableMatches.size(); i++)
        {
            for (int j = 0; j < unavailableMatches.size() - i; j++)
            {
                if (unavailableMatches.at(i).getExpDate() > unavailableMatches.at(j).getExpDate())
                {
                    swap(unavailableMatches.at(i), unavailableMatches.at(j));
                }
            }
        }

        // Combine the two back together into one finished, sorted vector
        matches.clear();
        for (int i = 0; i < availableMatches.size(); i++)
        {
            matches.push_back(availableMatches.at(i));
        }
        for (int i = 0; i < unavailableMatches.size(); i++)
        {
            matches.push_back(unavailableMatches.at(i));
        }

        // Print matches
        if (matches.size() > 0)
        {
            cout << endl
                 << "Books that match your search critera:" << endl
                 << endl;
            for (BookCopy searchResult : matches)
            {
                cout << searchResult;
            }
        }
        else
        {
            cout << endl
                 << "There were no books that match that search critera, try again with a different search." << endl
                 << endl;
        }
    }
};
