#pragma once

#include "User.h"
#include "Student.h"
#include "Teacher.h"
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
    Librarian(string initUsername, string initPassword);

    // ********** FUNCTIONS **********
    void addBook(vector<Book> &catalog, int &copycount);
    void deleteBook(vector<Book> &catalog);
    void searchUser(UserBST &users);
    void addUser(UserBST &users);
    void deleteUser(UserBST &users);
    void printMyInfo();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

Librarian::Librarian()
{
    type = "Librarian";
}

Librarian::Librarian(string initUsername, string initPassword)
{
    username = initUsername;
    password = initPassword;
    type = "Librarian";
}

// Casting //
Librarian *userToLibrarian(User *toCast)
{
    return dynamic_cast<Librarian *>(toCast);
}

// Functions //

void Librarian::addBook(vector<Book> &catalog, int &copycount)
{
    string newISBN;
    int newID;
    cout << "What is the ISBN of the new book? ";
    cin >> newISBN;

    // Binary search through the catalog to see if there is a book with that ISBN
    int foundIndex = getIndexOfBook(catalog, newISBN);

    if (foundIndex != -1)
    {
       
        BookCopy newBookCopy(copycount);
        copycount++;
        catalog.at(foundIndex).copies.push_back(newBookCopy);
    }
    else
    {
        string newTitle, newAuthor, newCategory;

        cout << "A book with this ISBN does not exist yet, so a new book will be added to the library." << endl
             << "What is the title of this book? ";
        cin >> newTitle;
        cout << "What is the author of this book? ";
        cin >> newAuthor;
        cout << "What is the category of this book? ";
        cin >> newCategory;
        cout << "At least one copy of this book must be added, what is the ID of this copy? ";
        

        Book newBook(newISBN, newTitle, newAuthor, newCategory);
        BookCopy newBookCopy(copycount);
        copycount++;
        newBook.copies.push_back(newBookCopy);
        catalog.push_back(newBook);

        // Sort Catalog again since a new book was added
        sortCatalog(catalog);
    }

    cout << endl
         << "Book has been added" << endl
         << endl;
}

void Librarian::deleteBook(vector<Book> &catalog)
{
    int IDtoDelete;
    cout << "What is the ID of the book copy you want to delete? ";
    cin >> IDtoDelete;

    int indexOfBook = -1;
    int indexOfBookCopy = -1;

    // Search through catalog to find the matching Book
    // Needs to do a brute force search since the vector is sorted by ISBN, not by id
    for (int i = 0; i < catalog.size(); i++)
    {
        for (int j = 0; j < catalog.at(i).copies.size(); j++)
        {
            if (catalog.at(i).copies.at(j).getID() == IDtoDelete)
            {
                indexOfBook = i;
                indexOfBookCopy = j;
            }
        }
    }

    if (indexOfBook == -1)
    {
        cout << "This book doesnt exists in the library catalog, please try again." << endl;
        return;
    }

    catalog.at(indexOfBook).copies.erase(catalog.at(indexOfBook).copies.begin() + indexOfBookCopy);

    if (catalog.at(indexOfBook).copies.size() == 0)
    {
        cout << "This was the last copy of this book, so the book will also be deleted" << endl
             << endl;
        catalog.erase(catalog.begin() + indexOfBook);
    }
    else
    {
        cout << "This copy of the book has been deleted" << endl
             << endl;
    }
}

void Librarian::searchUser(UserBST &users)
{
    cout << "What is the username of the user you want to search for? ";
    string searchUsername;
    cin >> searchUsername;

    User *foundUser = users.returnUser(searchUsername);

    if (foundUser == nullptr)
    {
        cout << "User was not found, try again" << endl
             << endl;
        return;
    }

    cout << "User was found:" << endl
         << endl;

    if (foundUser->getType() == "Librarian")
    {
        // Uses << overload from User.h
        cout << userToLibrarian(foundUser);
    }
    else if (foundUser->getType() == "Student")
    {
        // TODO Uses << overload from Reader.h
        cout << userToStudent(foundUser);
    }
    else if (foundUser->getType() == "Teacher")
    {
        // TODO Uses << overload from Reader.h
        cout << userToTeacher(foundUser);
    }
}

void Librarian::addUser(UserBST &users)
{
    cout << "What is the type of user you want to add (Enter 's', 't', or 'l') ";
    char newUserType;
    cin >> newUserType;
    cout << "What is the username of the user you want to add? ";
    string newUsername;
    cin >> newUsername;
    cout << "What is the password of the user you want to add? ";
    string newPassword;
    cin >> newPassword;

    switch (newUserType)
    {
    case 's':
    {
        Student *newStudent = new Student(newUsername, newPassword);
        users.addUser(newStudent);
        break;
    }
    case 't':
    {
        Teacher *newTeacher = new Teacher(newUsername, newPassword);
        users.addUser(newTeacher);
        break;
    }
    case 'l':
    {
        Librarian *newLibrarian = new Librarian(newUsername, newPassword);
        users.addUser(newLibrarian);
        break;
    }
    default:
    {
        cout << "Something went wrong. User was not created." << endl
             << endl;
        break;
    }
    }
}

void Librarian::deleteUser(UserBST &users)
{
    cout << "What is the username of the user you want to delete? ";
    string deleteUsername;
    cin >> deleteUsername;

    User *foundUser = users.returnUser(deleteUsername);

    if (foundUser == nullptr)
    {
        cout << "User was not found, try again" << endl
             << endl;
        return;
    }

    if (foundUser->getType() == "Student" || foundUser->getType() == "Teacher")
    {
        // If user is a student or teacher (AKA reader), check if they have copies borrowed. If there are copies being borrowed, user cant be deleted
        if (userToReader(foundUser)->getBooksBorrowed().size() != 0)
        {
            cout << "This user has books current being borrowed, please have them return the books before deleting" << endl
                 << endl;
            return;
        }
    }

    users.deleteUser(foundUser);
    cout << "User has been deleted." << endl
         << endl;
}

void Librarian::printMyInfo()
{
    cout << (*this);
}
