#pragma once

#include "User.h"
#include "Book.h" // Might be unnecessary

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Librarian : public User
{
public:
    Librarian();
    Librarian(string initUserName, string initPassword);
    void addBook(BST<Book> &bookCatalog);
    void deleteBook(BST<Book> &bookCatalog);
    void searchUser(BST<User *> usersList);
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

void Librarian::addBook(BST<Book> &bookCatalog)
{
    // TODO - (Ethan)
    string input;
    Book *temp;
    cout << "Adding new book..." << endl;
    cout << "Please type the isbn of the new book: ";
    cin >> input;

    temp.setIsbn(input);
    cout << "Please type the title of the new book: ";
    cin >> input;
    temp.setTitle(input);
    cout << "Please type the catagory of the new book: ";
    cin >> input;
    temp.setCategory(input);

    //bookCatalog.nodeInsert(temp);

    //
    // may need further modification for copies data struct
    //
}

void Librarian::deleteBook(BST<Book *> &bookCatalog)
{
    // TODO - (Ethan)
    cout << "Please input the book id to be removed: ";
    int idin;
    cin >> idin;

}

User Librarian::searchUser(BST<User *> usersList)
{
        if ((root->val.getUserName() == user) && (root->val.getPassword() == pass))
        {
            return root->val;
        }
        else
        {
            false;
        }
        /* Traverse left*/
        verifytype(root, user, pass);
        /* Traverse right */
        verifytype(root, user, pass);
}

void Librarian::addUsers(BST<User *> usersList)
{
    int typein;
    string userin;
    string passwordin;
    cout << "What kind of user would you like to add? 1 for Student, 2 for Teacher, 3 for Librarian: ";
    cin >> typein;
    if (typein == 1) {
        cout << "Please input the desired username of the new user: ";
        cin >> userin;
        cout << "Please input the desired password of the new user: ";
        cin >> passwordin;
        Student temp(userin, passwordin);
        usersList.nodeInsert(temp);
    }
    if (typein == 2) {
        cout << "Please input the desired username of the new user: ";
        cin >> userin;
        cout << "Please input the desired password of the new user: ";
        cin >> passwordin;
        Teacher temp(userin, passwordin);
        usersList.nodeInsert(temp);
    }
    if (typein == 3) {
        cout << "Please input the desired username of the new user: ";
        cin >> userin;
        cout << "Please input the desired password of the new user: ";
        cin >> passwordin;
        Librarian temp(userin, passwordin);
        usersList.nodeInsert(temp);
    }
}

void Librarian::deleteUser(BST<User *> usersList)
{
    // TODO - (Ethan)
}

string Librarian::type()
{
    return "Librarian";
}
