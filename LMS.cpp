// Local Files //
#include "User.h"
#include "DateFunction.h"
#include "BookCopy.h"
#include "Structs.h"
#include "Book.h"
#include "Reader.h"
#include "UserBST.h"
#include "Student.h"
#include "Teacher.h"
#include "FileManagement.h"
#include "Librarian.h"

// Standard Files //
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>

/**
 * IMPORTANT
 * - None of the text files can have an empty line at the end, as that will cause an extra element to be created
 */

using namespace std;

void getUsers(UserBST &users);
void getBooks(vector<Book> &catalog);
void getCopies(vector<Book> &catalog);

User *login(UserBST &users);

void readerLoop(Reader *user, vector<Book> &catalog, UserBST users, time_t &zeroTime);
void librarianLoop(Librarian *user, vector<Book> &catalog, UserBST users, time_t &zeroTime, int idCount);

int main()
{
    // Data to be read in from text files
    vector<Book> catalog;
    UserBST users;
    int idCount;

    // Read in data from text files
    getUsers(users);
    getBooks(catalog);
    getCopies(catalog);

    // Login system, multiple users can login in and out on the same execution of the program
    while (true)
    {
        User *currentUser = login(users);
        time_t zeroTime = time(NULL);

        if (currentUser->getType() == "Librarian")
        {
            librarianLoop(userToLibrarian(currentUser), catalog, users, zeroTime, idCount);
        }
        else if (currentUser->getType() == "Student")
        {
            readerLoop(userToReader(currentUser), catalog, users, zeroTime);
        }
        else if (currentUser->getType() == "Teacher")
        {
            readerLoop(userToReader(currentUser), catalog, users, zeroTime);
        }
        else
        {
            cerr << "userType is invalid" << endl;
            exit(5);
        }
    }

    return 0;
}

void getUsers(UserBST &users)
{
    // File I/O using the users file (usersList.txt)
    fstream userFile("usersList.txt");
    if (userFile.fail())
    {
        cerr << "Error opening usersList.txt" << endl;
        exit(1);
    }

    /* It will be done variable by variable since each Person has 3 fields that need to be read.
     *
     * The format will be
     * Role(0=student, 1=teacher, 2=librarian)  user_name   password
     */

    // Check what type of user it is (student, teacher, librarian) and push to the BST
    int rolein;
    string userin;
    string passwordin;
    while (!(userFile.eof()))
    {
        // Get important fields
        userFile >> rolein >> userin >> passwordin;
        // Clear the rest of the line
        string temp;
        getline(userFile, temp);

        if (rolein == 0) // for student
        {
            // assign values and attributes to temp student
            Student *temp = new Student(userin, passwordin);
            // push to BST
            users.addUser(temp);
        }
        if (rolein == 1) // for teacher
        {
            // assign values and attributes to temp teacher
            Teacher *temp = new Teacher(userin, passwordin);
            // push to BST
            users.addUser(temp);
        }
        if (rolein == 2) // for librarian
        {
            // assign values and attributes to temp teacher
            Librarian *temp = new Librarian(userin, passwordin);
            // push to BST
            users.addUser(temp);
        }
    }
    // When finished reading in from file, close it
    userFile.close();
}

void getBooks(vector<Book> &catalog)
{
    // File I/O using the users file (booksList.txt)
    fstream bookFile("booksList.txt");
    if (bookFile.fail())
    {
        cerr << "Error opening booksList.txt" << endl;
        exit(1);
    }

    string isbn;
    string title;
    string author;
    string catagory;
    while (!bookFile.eof())
    {
        // For each line push a new Book object to the vector
        bookFile >> isbn >> title >> author >> catagory;
        string temp;
        getline(bookFile, temp);
        Book toInsert(isbn, title, author, catagory);
        catalog.push_back(toInsert);
    }

    // Sort catalog
    sortCatalog(catalog);

    bookFile.close();
}

void getCopies(vector<Book> &catalog)
{
    fstream copyFile("copiesList.txt");
    if (copyFile.fail())
    {
        cerr << "Error opening copiesList.txt" << endl;
        exit(1);
    }

    string isbn;
    int id;
    while (!copyFile.eof())
    {
        // Get data from a single line
        copyFile >> isbn >> id;
        // Search through the vector to find the matching Book
        int indexResult = getIndexOfBook(catalog, isbn);
        // Make new BookCopy
        BookCopy *temp = new BookCopy(id);

        // Insert the copy
        if (indexResult != -1)
        {
            catalog.at(indexResult).copies.push_back(*temp);
        }
    }

    copyFile.close();
}

User *login(UserBST &users)
{
    while (true)
    {
        string usernameIn;
        string passwordIn;
        // Prompt for username/ ask if they want to shutdown system
        cout << "Please enter a user name or type 'shutdown' to shut down LMS:" << endl;
        cin >> usernameIn;

        // If shutdown system, exit
        if (usernameIn == "shutdown")
        {
            cout << "Shutting Down..." << endl
                 << endl;
            exit(0);
        }
        else
        {
            // Else prompt for password
            cout << "Please enter a password:" << endl;
            cin >> passwordIn;

            // Search for a user with the entered username and password
            string userType = "nonexistant";
            users.findUserType(usernameIn, passwordIn, userType);

            if (userType == "Student" || userType == "Teacher" || userType == "Librarian")
            {
                return users.returnUser(usernameIn, passwordIn);
            }
            else
            {
                cout << "Account with those credentials was not found. Please try again" << endl
                     << endl;
            }
        }
    }
}

void readerLoop(Reader *user, vector<Book> &catalog, UserBST users, time_t &zeroTime)
{
    while (true)
    {
        int currentDate = date(zeroTime);
        cout << "Welcome back,\n"
             << "It is currently day " << currentDate << "\n\n"
             << "Please choose:\n"
             << "1 -- Search Book\n"
             << "2 -- Borrow Book\n"
             << "3 -- Return Book\n"
             << "4 -- Renew Book\n"
             << "5 -- Reserve Book\n"
             << "6 -- Cancel Book\n"
             << "7 -- My Information\n"
             << "8 -- Change Password\n"
             << "9 -- I'm Feeling Lucky\n"
             << "0 -- Log Out\n"
             << endl;

        int choice;
        cin >> choice;
        if (cin.fail())
        {
            cout << "Invalid input" << endl
                 << endl;
            // Reset cin and clear the failbit
            cin.clear();
            cin.ignore();
            continue;
        }

        switch (choice)
        {
        case 0:
        {
            // writing back to text files
            writeOutUsersFile(users);
            writeOutBooksFile(catalog);
            writeOutCopiesFile(catalog);
            return;
        }
        case 1:
        {
            // TODO Search Book
            cout << "Entered search book function" << endl;
            break;
        }
        case 2:
        {
            // TODO Borrow Book
            cout << "Entered borrow book function" << endl;
            break;
        }
        case 3:
        {
            // TODO Return Book
            cout << "Entered return book function" << endl;
            break;
        }
        case 4:
        {
            // TODO Renew Book
            cout << "Entered renew book function" << endl;
            break;
        }
        case 5:
        {
            // TODO Reserve Book
            cout << "Entered reserve book function" << endl;
            break;
        }
        case 6:
        {
            // TODO Cancel Book
            cout << "Entered cancel book function" << endl;
            break;
        }
        case 7:
        {
            // TODO Printout Information
            cout << "Entered printout info function" << endl;
            break;
        }
        case 8:
        {
            // Change Password
            user->changePassword();
            break;
        }
        case 9:
        {
            // TODO I'm Feeling Lucky
            cout << "Entered feeling lucky function" << endl;
            break;
        }
        default:
        {
            cout << "Something went wrong, please try again" << endl;
            break;
        }
        }
    }
}

void librarianLoop(Librarian *user, vector<Book> &catalog, UserBST users, time_t &zeroTime, int idCount)
{
    while (true)
    {
        int currentDate = date(zeroTime);
        cout << "Welcome back,\n"
             << "It is currently day " << currentDate << "\n\n"
             << "Please choose:\n"
             << "2 -- Add Book\n"
             << "3 -- Delete Book\n"
             << "4 -- Search User\n"
             << "5 -- Add User\n"
             << "6 -- Delete User\n"
             << "7 -- My Information\n"
             << "8 -- Change Password\n"
             << "0 -- Log Out\n"
             << endl;

        int choice;
        cin >> choice;
        if (cin.fail())
        {
            cout << "Invalid input" << endl
                 << endl;
            // Reset cin and clear the failbit
            cin.clear();
            cin.ignore();
            continue;
        }

        switch (choice)
        {
        case 0:
        {
            // writing back to text files
            writeOutUsersFile(users);
            writeOutBooksFile(catalog);
            writeOutCopiesFile(catalog);
            return;
        }
        case 2:
        {
            // TODO Add Book
            cout << "Entered add book function" << endl;
            break;
        }
        case 3:
        {
            // TODO Delete Book
            cout << "Entered delete book function" << endl;
            break;
        }
        case 4:
        {
            // TODO Search User
            cout << "Entered search user function" << endl;
            // string toSearch;
            // cout << "What username to search for? ";
            // cin >> toSearch;
            // user->searchUser(usersList->root, toSearch);
            break;
        }
        case 5:
        {
            // TODO Add User
            cout << "Entered add user function" << endl;
            break;
        }
        case 6:
        {
            // TODO Delete User
            cout << "Entered delete user function" << endl;
            break;
        }
        case 7:
        {
            // TODO My Information
            cout << "Entered my info function" << endl;
            break;
        }
        case 8:
        {
            // Change Password
            user->changePassword();
            break;
        }
        default:
        {
            cout << "Something went wrong, please try again" << endl;
            break;
        }
        }
    }
}