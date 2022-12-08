#pragma once

#include "BST.h" // These includes needs to be checked again!
#include "Book.h"
#include "User.h"

#include <iostream>
#include <fstream>

using namespace std;

void BookInOrderTraversal(TreeNode<Book> *inputBST, ofstream &output)
{
    if (inputBST == NULL)
    {
        return;
    }

    BookInOrderTraversal(inputBST->left, output); // visit left child

    output << inputBST->val.getIsbn() << " " << inputBST->val.getTitle() << " " << inputBST->val.getAuthor() << " " << inputBST->val.getCategory() << endl;

    BookInOrderTraversal(inputBST->right, output); // visit right child
}

void getRelevantBCInfo(TreeNode<Book> *inputBST, ofstream &output)
{
    for (int i = 0; i < inputBST->val.copiesVector.size(); i++)
    {
        cout << inputBST->val.getIsbn() << " " << inputBST->val.copiesVector.at(i).getID();
    }
}

void BCInOrderTraversal(TreeNode<Book> *inputBST, ofstream &output)
{
    if (inputBST == NULL)
    {
        return;
    }

    BCInOrderTraversal(inputBST->left, output); // visit left child

    getRelevantBCInfo(inputBST, output);

    BCInOrderTraversal(inputBST->right, output); // visit right child
}

void UserInOrderTraversal(TreeNode<User *> *inputBST, ofstream &output)
{
    if (inputBST == NULL)
    {
        return;
    }

    UserInOrderTraversal(inputBST->left, output); // visit left child

    int type;
    string actualType = inputBST->val->type();
    if (actualType == "Student")
    {
        type = 0;
    }
    else if (actualType == "Teacher")
    {
        type = 1;
    }
    else if (actualType == "Librarian")
    {
        type = 2;
    }

    output << type << "\t" << inputBST->val->getUserName() << "\t" << inputBST->val->getPassword() << endl;

    UserInOrderTraversal(inputBST->right, output); // visit right child
}

void writeBackToBookFile(BST<Book> *bookCatalog)
{
    ofstream outputBooks;
    outputBooks.open("outputBooks.txt");

    BookInOrderTraversal(bookCatalog->root, outputBooks); // Writes into another outputBooks.txt file
    outputBooks.close();
}

void writeBackToBCFile(BST<Book> *bookCatalog)
{
    ofstream outputBookCopy;
    outputBookCopy.open("outputBookCopy.txt");

    BCInOrderTraversal(bookCatalog->root, outputBookCopy); // Writes into another outputBookCopy.txt file
}

void writeBackToUserFile(BST<User *> *usersList)
{
    ofstream outputUsers;
    outputUsers.open("outputUsers.txt");

    UserInOrderTraversal(usersList->root, outputUsers); // Writes into another outputUsers.txt file
}