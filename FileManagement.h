#pragma once

#include "BST.h"							// These includes needs to be checked again!
#include "Book.h"
#include "User.h"

#include <iostream>
#include <fstream>

using namespace std;

class File_Management {

public:
	void writeBackToBookFile();
    void writeBackToBCFile();
    void writeBackToUserFile();

};

void BookInOrderTraversal(TreeNode<Book>* inputBST, fstream output)
{ 
    if (inputBST == NULL)
    {
        return;
    }

    BookInOrderTraversal(inputBST->left, output); // visit left child

    output << inputBST->val.getIsbn() << " " << inputBST->val.getTitle() << " " << inputBST->val.getAuthor() << " " << inputBST->val.getCategory() << endl;
    
    BookInOrderTraversal(inputBST->right, output); // visit right child
}

void getRelevantBCInfo(TreeNode<Book>* inputBST, fstream output) {
    for (int i = 0; i < inputBST->val.copiesVector.size(); i++) {
        cout << inputBST->val.getIsbn() << " " << inputBST->val.copiesVector.at(i).getID();
    }

}

void BCInOrderTraversal(TreeNode<Book>* inputBST, fstream output)
{
    if (inputBST == NULL)
    {
        return;
    }

    BCInOrderTraversal(inputBST->left, output); // visit left child

    getRelevantBCInfo(inputBST, output);

    BCInOrderTraversal(inputBST->right, output); // visit right child
}

void UserInOrderTraversal(TreeNode<User*>* inputBST, fstream output)
{
    if (inputBST == NULL)
    {
        return;
    }

    UserInOrderTraversal(inputBST->left, output); // visit left child

    output << inputBST->val->type() << " " << inputBST->val->getUserName() << " " << inputBST->val->getPassword() << endl;

    UserInOrderTraversal(inputBST->right, output); // visit right child
}


void File_Management::writeBackToBookFile(BST<Book>* bookCatalog) {
    fstream outputBooks;
    outputBooks.open("outputBooks.txt");

    BookInOrderTraversal(bookCatalog->root, outputBooks);           // Writes into another outputBooks.txt file
}

void File_Management::writeBackToBCFile(BST<Book>* bookCatalog) {
    fstream outputBookCopy;
    outputBookCopy.open("outputBookCopy.txt");

    BCInOrderTraversal(bookCatalog->root, outputBookCopy);          // Writes into another outputBookCopy.txt file
}

void File_Management::writeBackToUserFile(BST<User*>* usersList) {
    fstream outputUsers;
    outputUsers.open("outputUsers.txt");

    UserInOrderTraversal(usersList->root, outputUsers);             // Writes into another outputUsers.txt file
}