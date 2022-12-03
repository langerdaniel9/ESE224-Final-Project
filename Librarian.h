#pragma once

#include "User.h"
#include "Book.h" // Might be unnecessary

#include <string>
#include <vector>

using namespace std;

class Librarian : public User
{
public:
    Librarian();
    Librarian(string initUserName, string initPassword);
    void addBook(BST<Book> &bookCatalog, );
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

void Librarian::addBook(BST<Book *> &bookCatalog)
{
    // TODO - (Ethan)
    string input;
    Book temp;
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




    bookCatalog.nodeInsert(temp);

    

    //
    //may need further modification for copies data struct
    //

    

}

void Librarian::deleteBook(BST<Book *> &bookCatalog)
{
    // TODO - (Ethan)
    cout << "Please input the "
}

void Librarian::searchUser(BST<User *> usersList)
{
    // TODO - (Ethan)
}

void Librarian::addUsers(BST<User *> usersList)
{
    // TODO - (Ethan)
}

void Librarian::deleteUser(BST<User *> usersList)
{
    // TODO - (Ethan)
}

string Librarian::type()
{
    return "Librarian";
}
