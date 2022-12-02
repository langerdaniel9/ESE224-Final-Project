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
    void addBook(vector<Book> &bookCatalog);
    void deleteBook(vector<Book> &bookCatalog);
    void searchUser(vector<User *> usersList);
    void addUsers(vector<User *> usersList);
    void deleteUser(vector<User *> usersList);
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

void Librarian::addBook(vector<Book> &bookCatalog)
{
    // TODO - (Ethan)
}

void Librarian::deleteBook(vector<Book> &bookCatalog)
{
    // TODO - (Ethan)
}

void Librarian::searchUser(vector<User *> usersList)
{
    // TODO - (Ethan)
}

void Librarian::addUsers(vector<User *> usersList)
{
    // TODO - (Ethan)
}

void Librarian::deleteUser(vector<User *> usersList)
{
    // TODO - (Ethan)
}

string Librarian::type()
{
    return "Librarian";
}
