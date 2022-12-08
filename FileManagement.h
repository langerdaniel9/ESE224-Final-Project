#pragma once

#include "UserBST.h"
#include "Book.h"
#include "BookCopy.h"
#include "User.h"
#include "Structs.h"

#include <fstream>
#include <iostream>
#include <vector>

void traverseBSTandWriteToFile(ofstream &output, node *node)
{
    if (node == nullptr)
    {
        return;
    }
    traverseBSTandWriteToFile(output, node->left);
    /************************/
    int type;
    if (node->value->getType() == "Student")
    {
        type = 0;
    }
    else if (node->value->getType() == "Teacher")
    {
        type = 1;
    }
    else if (node->value->getType() == "Librarian")
    {
        type = 2;
    }
    output << type << "\t"
           << node->value->getUsername() << "\t"
           << node->value->getPassword() << endl;
    /************************/
    traverseBSTandWriteToFile(output, node->right);
}

void writeOutUsersFile(UserBST users)
{
    ofstream userOutput;
    userOutput.open("outputUsers.txt");
    traverseBSTandWriteToFile(userOutput, users.root);
    userOutput.close();
}

void writeOutBooksFile(vector<Book> catalog)
{
    ofstream bookOutput;
    bookOutput.open("outputBooks.txt");

    // Traverse and print
    for (Book bk : catalog)
    {
        bookOutput << bk.getIsbn() << "\t"
                   << bk.getTitle() << "\t"
                   << bk.getAuthor() << "\t"
                   << bk.getCategory()
                   << endl;
    }

    bookOutput.close();
}

void writeOutCopiesFile(vector<Book> catalog)
{
    ofstream copiesOutput;
    copiesOutput.open("outputCopies.txt");

    // Traverse and print
    for (Book bk : catalog)
    {

        for (BookCopy bkcpy : bk.copies)
        {
            copiesOutput << bk.getIsbn() << "\t"
                         << bkcpy.getID() << endl;
        }
    }

    copiesOutput.close();
}
