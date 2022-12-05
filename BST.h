#pragma once

#include "Structs.h"
#include "User.h"
#include "Book.h"
// #include "Reader.h"

#include <vector>
#include <iostream>
#include <string>

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
    void binarySearch(string element);
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
        root = new TreeNode<Type>(element); // Comes from creating a new TreeNode from Structs.h
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

TreeNode<Book> *deleteNode(TreeNode<Book> *root, Book element) // deleteNode for Books BST
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

TreeNode<User *> *deleteNode(TreeNode<User *> *root, User *element) // deleteNode for User BST
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
            TreeNode<User *> *aux = root->right;
            delete (root);
            return aux;
        }
        else if (root->right == NULL)
        {
            TreeNode<User *> *aux = root->left;
            delete (root);
            return aux;
        }

        TreeNode<User *> *toGetDeleted = inOrderSuccessor(root->right); // The deleting here does not work!
        root->val = toGetDeleted->val;
        root->right = deleteNode(root->right, toGetDeleted->val);
    }

    return root;
}

template <typename Type>
void BST<Type>::deleteNode(Type element)
{
    root = deleteNode(root, element); // Assuming this works?? (Going to either Book or User types)
}
////////////////////////////////////

////////////////////////////////////
// Binary Search
void binarySearch(TreeNode<Book> *root, string isbn)
{
    // Used for users (by username), books (by ISBN), and book copies (by ID)
    if (root == NULL)
    {
        return;
    }
    if (root->val.getIsbn() == isbn)
    {
        // Should be used to print out info about a book through operator overloading (<<)
        cout << root->val << endl;
        cout << "Copies Available: " << endl;
        for (BookCopy copy : root->val.copiesVector)
        {
            if (copy.getReaderName() == "")
            {
                cout << copy.getID() << " ";
            }
        }
        cout << endl;
        return;
    }

    if (isbn < root->val.getIsbn())
    {
        binarySearch(root->left, isbn);
    }
    else if (isbn > root->val.getIsbn())
    {
        binarySearch(root->right, isbn);
    }
}

template <typename Type>
void BST<Type>::binarySearch(string element)
{
    root = binarySearch(root, element); // Assuming this works?? (Going to either Book or User types)
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

int partitionForUnavailableCopies(vector<BookCopy> lib, int low, int high)
{
    // partition starting from first element
    // then comparing each element by the last element in the array

    int i = low - 1; // i => index of first array (array lower than "high" value)

    for (int j = low; j < high; j++)
    { // j => index of second array (array greater than "high" value)
        if (lib.at(j).getExpirationDate() <= lib.at(high).getExpirationDate())
        {
            i++;
            swap(lib.at(i), lib.at(j));
        }
    }

    // Swapping the "high" value to where it needs to be
    swap(lib.at(high), lib.at(i + 1));

    // returns the index of where the "high" value is
    return i + 1;
}

void quickSortForUnavailableCopies(vector<BookCopy> lib, int low, int high)
{
    if (low < high)
    {
        int pi = partitionForUnavailableCopies(lib, low, high);

        // recursive call on the left of pivot
        quickSortForUnavailableCopies(lib, low, pi - 1);

        // recursive call on the right of pivot
        quickSortForUnavailableCopies(lib, pi + 1, high);
    }
}

int partitionForMatches(vector<Book> lib, int low, int high)
{
    // partition starting from first element
    // then comparing each element by the last element in the array

    int i = low - 1; // i => index of first array (array lower than "high" value)

    for (int j = low; j < high; j++)
    { // j => index of second array (array greater than "high" value)
        int result = lib.at(j).getTitle().compare(lib.at(high).getTitle());

        if (result <= 0)
        {
            i++;
            swap(lib.at(i), lib.at(j));
        }
    }

    // Swapping the "high" value to where it needs to be
    swap(lib.at(high), lib.at(i + 1));

    // returns the index of where the "high" value is
    return i + 1;
}

void quickSortForMatches(vector<Book> lib, int low, int high)
{
    if (low < high)
    {
        int pi = partitionForMatches(lib, low, high);

        // recursive call on the left of pivot
        quickSortForMatches(lib, low, pi - 1);

        // recursive call on the right of pivot
        quickSortForMatches(lib, pi + 1, high);
    }
}

void BST<Book>::search(TreeNode<Book> *root, string searchTerm, bool TitleOrCategory)
{
    //// Make array for result of search
    vector<Book> matches;
    matches.clear();

    //// Search for matches and add them to the array
    searchRecursive(root, searchTerm, matches, TitleOrCategory);

    if (matches.size() == 0)
    {
        cout << endl
             << "There were no books that match that search critera, try again with a different search." << endl
             << endl;
        return;
    }

    // Sort matches by title
    quickSortForMatches(matches, 0, matches.size() - 1);

    //// Compiling the results
    for (int i = 0; i < matches.size(); i++)
    {
        vector<BookCopy> unavailable;
        vector<int> available;
        unavailable.clear();
        available.clear();
        for (int j = 0; j < matches.at(i).copiesVector.size(); j++)
        {
            if (matches.at(i).copiesVector.at(j).getReaderName() == "")
            {
                available.push_back(matches.at(i).copiesVector.at(j).getID());
            }
            else
            {
                unavailable.push_back(matches.at(i).copiesVector.at(j));
            }
        }

        // Print the Book
        cout << matches.at(i);

        // Print available ID's
        cout << "Available ID's: ";

        for (int avail : available)
        {
            cout << avail << " ";
        }
        cout << endl;

        // Sort unavailable BookCopies
        quickSortForUnavailableCopies(unavailable, 0, unavailable.size() - 1);

        // Print unavailable ID's
        for (int j = 0; j < unavailable.size(); j++)
        {
            cout << unavailable.at(j).getID() << " ";
        }
        cout << endl;
    }
}
////////////////////////////////////