#pragma once

#include "Structs.h"
#include "User.h"
#include "Book.h"

#include <vector>
#include <iostream>

using namespace std;

template <typename Type>
class BST
{

public:
    // Properties
    TreeNode<Type> *root;

    // Functions
    BST<Type>();
    void nodeInsert(Type element);
    void deleteNode(Type element);
    void binarySearch(Type element);
    void search(TreeNode<Type> *root, string searchTerm, bool TitleOrCategory);
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

////////////////////////////////////
// Constructor
template <typename Type>
BST<Type>::BST()
{
    root = nullptr;
}
////////////////////////////////////

////////////////////////////////////
// Insert Node
template <typename Type>
TreeNode<Type> *nodeInsert(TreeNode<Type> *root, Type element)
{
    if (root == nullptr)
    {
        root = new TreeNode<Type>(element);                                         // Comes from creating a new TreeNode from Structs.h
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

template <typename Type>
void BST<Type>::nodeInsert(Type element)
{
    root = nodeInsert(root, element);
}
////////////////////////////////////

////////////////////////////////////
// Delete Node
template <typename Type>
TreeNode<Type> *inOrderSuccessor(TreeNode<Type> *root)
{
    TreeNode<Type> *successor = root;
    while ((successor && successor->left) != NULL)
    {
        successor = successor->left;
    }

    return successor;
}

TreeNode<Book> *deleteNode(TreeNode<Book> *root, Book element)                                  // deleteNode for Books BST
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
            TreeNode<Book> *aux = root->right;
            delete (root);
            return aux;
        }
        else if (root->right == NULL)
        {
            TreeNode<Book> *aux = root->left;
            delete (root);
            return aux;
        }

        TreeNode<Book> *toGetDeleted = inOrderSuccessor(root->right); // The deleting here does not work!
        root->val = toGetDeleted->val;
        root->right = deleteNode(root->right, toGetDeleted->val);
    }

    return root;
}

TreeNode<User*> *deleteNode(TreeNode<User*> *root, User *element)                                  // deleteNode for User BST
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
            TreeNode<User*> *aux = root->right;
            delete (root);
            return aux;
        }
        else if (root->right == NULL)
        {
            TreeNode<User*> *aux = root->left;
            delete (root);
            return aux;
        }

        TreeNode<User*> *toGetDeleted = inOrderSuccessor(root->right); // The deleting here does not work!
        root->val = toGetDeleted->val;
        root->right = deleteNode(root->right, toGetDeleted->val);
    }

    return root;
}

template <typename Type>
void BST<Type>::deleteNode(Type element)
{
    root = deleteNode(root, element);                                                   // Assuming this works?? (Going to either Book or User types)
}
////////////////////////////////////

////////////////////////////////////
// Binary Search
void binarySearch(TreeNode<User *> *root, Type element)                                   // maybe specifiy this??
{
    // Used for users (by username), books (by ISBN), and book copies (by ID)
    if (root == NULL)
    {
        cout << root->val << endl;                                      // Should be used to print out info about a user through operator overloading (<<)
    }

    if (element < root->val)
    {
        root->left = binarySearch(root->left, element);
    }
    else if (element > root->val)
    {
        root->right = binarySearch(root->right, element);
    }
}           

void binarySearch(TreeNode<Book> *root, string isbn)
{
    // Used for users (by username), books (by ISBN), and book copies (by ID)
    if (root == NULL)
    {
        cout << root->val << endl;                                      // Should be used to print out info about a book through operator overloading (<<)
    }

    if (element < root->val)
    {
        root->left = binarySearch(root->left, isbn);
    }
    else if (element > root->val)
    {
        root->right = binarySearch(root->right, isbn);
    }
}

template <typename Type>
void BST<Type>::binarySearch(Type element)
{
    root = binarySearch(root, element);                                                   // Assuming this works?? (Going to either Book or User types)
}
////////////////////////////////////

////////////////////////////////////
// Brute Force (recursive) Search
void searchRecursive(TreeNode<Book> *root, string searchTerm, vector<Book> &matches, bool TorC)
{
    if (root == NULL)
    {
        return;
    }

    // visit left child
    searchRecursive(root->left, searchTerm, matches, TorC);

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
    searchRecursive(root->right, searchTerm, matches, TorC);
}

template <typename Type>
void BST<Type>::search(TreeNode<Type> *root, string searchTerm, bool TitleOrCategory)
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
        for (auto searchResult : matches)
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
////////////////////////////////////