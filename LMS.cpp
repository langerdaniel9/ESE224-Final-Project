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
void librarianLoop(Librarian *user, vector<Book> &catalog, UserBST users, time_t &zeroTime, int &copycount);



int main()
{
    // Data to be read in from text files
    vector<Book> catalog;
    UserBST users;
    int copycount = 0;
    // Read in data from text files
    getUsers(users);
    getBooks(catalog);
    getCopies(catalog,copycount);

    // Print Welcome message
    cout << "-----------------------------------" << endl
         << "-      Welcome to My Library      -" << endl
         << "-----------------------------------" << endl
         << endl;

    // Login system, multiple users can login in and out on the same execution of the program
    while (true)
    {
        User *currentUser = login(users);
        time_t zeroTime = time(NULL);

        if (currentUser->getType() == "Librarian")
        {
            librarianLoop(userToLibrarian(currentUser), catalog, users, zeroTime);
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

void getCopies(vector<Book> &catalog, int& copyin)
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
        copyin++;
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
            User *resultUser = users.returnUser(usernameIn, passwordIn);

            if (resultUser != nullptr)
            {
                return resultUser;
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
        cout << endl
             << "Welcome back, " << user->getType() << "\n"
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
            // Search Book
            user->searchBook(catalog);
            break;
        }
        case 2:
        {
            // Borrow Book
            user->borrowBook(catalog, zeroTime);
            break;
        }
        case 3:
        {
            // Return Book
            user->returnBook(catalog);
            break;
        }
        case 4:
        {
            // Renew Book
            user->renewBook(catalog);
            break;
        }
        case 5:
        {
            // Reserve Book
            user->reserveBook(catalog);
            break;
        }
        case 6:
        {
            // Cancel Book
            user->cancelBook(catalog);
            break;
        }
        case 7:
        {
            // Printout Information
            user->printMyInfo();
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
            // I'm Feeling Lucky
            user->feelingLucky(catalog);
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

void librarianLoop(Librarian *user, vector<Book> &catalog, UserBST users, time_t &zeroTime,int &copycount)
{
    while (true)
    {
        int currentDate = date(zeroTime);
        cout << endl
             << "Welcome back, " << user->getType() << "\n"
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
            // Add Book
            user->addBook(catalog);
            break;
        }
        case 3:
        {
            // Delete Book
            user->deleteBook(catalog);
            break;
        }
        case 4:
        {
            // Search User
            user->searchUser(users);
            break;
        }
        case 5:
        {
            // Add User
            user->addUser(users);
            break;
        }
        case 6:
        {
            // Delete User
            user->deleteUser(users);
            break;
        }
        case 7:
        {
            // My Information
            user->printMyInfo();
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