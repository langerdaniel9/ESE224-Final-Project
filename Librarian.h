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
    void addBook(BST<Book> &bookCatalog);
    void deleteBook(BST<Book> &bookCatalog);
    User *searchUser(BST<User *> usersList);
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

    // TODO - search for book, if it exists, add a copy with a unique id.else create a new book and add it

    temp->setIsbn(input);
    cout << "Please type the title of the new book: ";
    cin >> input;
    temp->setTitle(input);
    cout << "Please type the catagory of the new book: ";
    cin >> input;
    temp->setCategory(input);

    // bookCatalog.nodeInsert(temp);

    //
    // may need further modification for copies data struct
    //
}

void Librarian::deleteBook(BST<Book> &bookCatalog)
{
    // TODO - (Ethan)
    cout << "Please input the book id to be removed: ";
    int idin;
    cin >> idin;
}

User *Librarian::searchUser(BST<User *> usersList)
{
    usersList.root->val->getUserName();

   

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

//TODO - Fix up searhcing for users
//void binarySearch(TreeNode<User*>* root, User* element)                                   // maybe specifiy this??
//{
//    // Used for users (by username), books (by ISBN), and book copies (by ID)
//    if (root == NULL)
//    {
//        return;                                         // I think this works??
//    }
//
//    if (root->val->getUserName() == element->getUserName()) {
//        string type = root->val->type();
//
//        if (type == "Student" || type == "Teacher") {
//            type = "Reader";
//        }
//
//        switch (type)
//        {
//        case "Reader": {
//
//            cout << "Username: " << root->val->getUserName() << endl
//                << "Password: " << root->val->getPassword() << endl
//                << "Reader Type: " << root->val->type() << endl;
//
//            Reader* tempForPrint = userToReader(root->val);
//
//            cout << "Copies: " << endl;
//            tempForPrint.printCopies();
//
//            //            cout << root->val << endl;
//
//            break;
//        }
//        case "Librarian": {
//
//            cout << "Username: " << root->val->getUserName() << endl
//                << "Password: " << root->val->getPassword() << endl;
//
//            break;
//        }
//        }
//
//    }
//
//
//    if (element < root->val)
//    {
//        root->left = binarySearch(root->left, element);
//    }
//    else if (element > root->val)
//    {
//        root->right = binarySearch(root->right, element);
//    }
//}

void Librarian::addUsers(BST<User *> usersList)
{
    int typein;
    string userin;
    string passwordin;
    cout << "What kind of user would you like to add? 1 for Student, 2 for Teacher, 3 for Librarian: ";
    cin >> typein;
    if (typein == 1)
    {
        cout << "Please input the desired username of the new user: ";
        cin >> userin;
        cout << "Please input the desired password of the new user: ";
        cin >> passwordin;
        Student temp(userin, passwordin);
        usersList.nodeInsert(temp);
    }
    if (typein == 2)
    {
        cout << "Please input the desired username of the new user: ";
        cin >> userin;
        cout << "Please input the desired password of the new user: ";
        cin >> passwordin;
        Teacher temp(userin, passwordin);
        usersList.nodeInsert(temp);
    }
    if (typein == 3)
    {
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
    cout << "please enter the username of the user you wish to delete: ";
    string userin;
    cin >> userin;
}

string Librarian::type()
{
    return "Librarian";
}

// Casting //
Librarian *userToLibrarian(User *toCast)
{
    return dynamic_cast<Librarian *>(toCast);
}