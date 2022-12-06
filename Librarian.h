#pragma once

#include "User.h"
#include "Book.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Librarian : public User
{
public:
    // ********** CONSTRUCTORS **********
    Librarian();
    Librarian(string initUserName, string initPassword);

    // ********** FUNCTIONS **********
    void addBook(BST<Book> *&bookCatalog, int &copycount);
    void deleteBook(BST<Book> *&bookCatalog);
    void searchUser(TreeNode<User *> *&usersList, string user);
    void addUsers(BST<User *> usersList);
    void deleteUser(BST<User *> usersList);
    string type();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

Librarian::Librarian()
{
}

Librarian::Librarian(string initUserName, string initPassword)
{
    userName = initUserName;
    password = initPassword;
}

void Librarian::addBook(BST<Book> *&bookCatalog, int &copycount)
{
    // TODO - (Ethan)
    string input;
    Book temp;
    BookCopy tempcopy(copycount++);
    copycount++;
    cout << "Adding new book..." << endl;
    cout << "Please type the isbn of the new book: ";
    cin >> input;
    temp.setIsbn(input);
    cout << "Please type the title of the new book: ";
    cin >> input;
    temp.setTitle(input);
    cout << "Please type the Author of the new book: ";
    temp.setAuthor(input);
    cout << "Please type the catagory of the new book: ";
    cin >> input;
    temp.setCategory(input);
    temp.copiesVector.push_back(tempcopy);
    // bookCatalog.nodeInsert(temp);
    bookCatalog->nodeInsert(temp);
    //
    // may need further modification for copies data struct
    //
}

void bookremoveInOrderTraversal(TreeNode<Book> *node, int inputID, Book &bookResult)
{
    if (node == nullptr)
    {
        return;
    }

    // visit left child
    bookremoveInOrderTraversal(node->left, inputID, bookResult);

    // What to do at current node
    for (int i = 0; i < node->val.copiesVector.size(); i++)
    {
        if (node->val.copiesVector.at(i).getID() == inputID)
        {
            bookResult = node->val;
        }
    }
    // visit right child
    bookremoveInOrderTraversal(node->right, inputID, bookResult);
}

void Librarian::deleteBook(BST<Book> *&bookCatalog)
{
    // TODO - (Ethan)
    cout << "Please input the book id to be removed: ";
    int idin;
    cin >> idin;

    BookCopy randomnameidgaf;
    randomnameidgaf.setID(-1);
    returnBookCopyGivenID(bookCatalog->root, idin, randomnameidgaf);

    if (randomnameidgaf.getID() == -1)
    {
        cout << "Id specified has not been found...";
        return;
    }
    else
    {
        // returnbook, then check if it has any copies
        Book bookTest;
        bookTest.setIsbn("-1");
        bookremoveInOrderTraversal(bookCatalog->root, idin, bookTest);
        string toremovetitle = bookTest.getTitle();
        vector<BookCopy> b1 = bookTest.getCopiesVector();
        for (int i = 0; i < b1.size(); i++)
        {
            if (b1.at(i).getID() == idin)
            {
                b1.erase(b1.begin() + 0); // check if work
            }
        }
        if (b1.empty())
        {
            // if array is now empty remove book
            // TODO create deletenode for book title
            bookCatalog->deleteNode(bookTest);
        }
        bookTest.getCopiesVector() = b1;
    }
}

void Librarian::searchUser(TreeNode<User *> *&usersList, string user)
{
    if ((usersList->val->getUserName() == user))
    {
        if (usersList->val->type() == "Librarian")
        {
            cout << "User's username is " << usersList->val->getUserName() << endl
                 << "User's password is " << usersList->val->getPassword() << endl;
        }
        else
        {
            cout << "The User is a " << usersList->val->type() << endl;
            cout << "User's username is " << usersList->val->getUserName() << endl
                 << "User's password is " << usersList->val->getPassword() << endl;
            // cout << "The user has "<< userToReader(usersList->val).copiesBorrowed()
        }
    }
    else
    {
        return;
    }
    /* Traverse left*/
    searchUser(usersList->left, user);
    /* Traverse right */
    searchUser(usersList->right, user);
}

void returnUserGivenUsername(TreeNode<User *> *&usersList, string user, User *&result)
{
    if ((usersList->val->getUserName() == user))
    {
        result = usersList->val;
    }
    else
    {
        return;
    }
    /* Traverse left*/
    returnUserGivenUsername(usersList->left, user, result);
    /* Traverse right */
    returnUserGivenUsername(usersList->right, user, result);
}

void Librarian::addUsers(BST<User *> usersList)
{
    int typein;
    string userin;
    string passwordin;
    cout << "What kind of user would you like to add? 1 for Student, 2 for Teacher, 3 for Librarian: ";
    cin >> typein;
    if (typein == 0)
    {
        cout << "Please input the desired username of the new user: ";
        cin >> userin;
        cout << "Please input the desired password of the new user: ";
        cin >> passwordin;
        User *temp;
        temp->setUserName(userin);
        temp->setPassword(passwordin);
        usersList.nodeInsert(temp);
    }
    if (typein == 1)
    {
        cout << "Please input the desired username of the new user: ";
        cin >> userin;
        cout << "Please input the desired password of the new user: ";
        cin >> passwordin;
        User *temp;
        temp->setUserName(userin);
        temp->setPassword(passwordin);
        usersList.nodeInsert(temp);
    }
    if (typein == 2)
    {
        cout << "Please input the desired username of the new user: ";
        cin >> userin;
        cout << "Please input the desired password of the new user: ";
        cin >> passwordin;
        User *temp;
        temp->setUserName(userin);
        temp->setPassword(passwordin);
        usersList.nodeInsert(temp);
    }
}

void Librarian::deleteUser(BST<User *> usersList)
{
    cout << "please enter the username of the user you wish to delete: ";
    string userin;
    cin >> userin;

    // Search user using string username
    User *toSearch;
    toSearch->setUserName("-1");

    returnUserGivenUsername(usersList.root, userin, toSearch);

    usersList.deleteNode(toSearch);
}

////////////////////////////////////

string Librarian::type()
{
    return "Librarian";
}

// Casting //
Librarian *userToLibrarian(User *toCast)
{
    return dynamic_cast<Librarian *>(toCast);
}