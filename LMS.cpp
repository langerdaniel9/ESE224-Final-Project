// Local Files //
#include "DateFunction.h"
#include "Structs.h"
#include "BookCopy.h"
#include "Book.h"
#include "User.h"
#include "BST.h"
#include "Librarian.h"
#include "Reader.h"
#include "Student.h"
#include "Teacher.h"
#include "FileManagement.h"

// Standard Files //
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

// Function Declarations //
void getUsers(BST<User *> *usersList);
void getBooks(BST<Book> *&bookCatalog);
void getCopies(BST<copystruct> *&copyCatalog);
void addCopiesToBook(BST<Book> *&bookCatalog, BST<BookCopy> *&copyCatalog);
User *login(BST<User *> *usersList);
void librarianLoop(Librarian *user, BST<Book> bookCatalog, BST<User *> usersList, time_t &zeroTime);
void readerLoop(Reader *user, BST<Book> *bookCatalog, time_t &zeroTime, BST<copystruct> *copyList);
///////////////////////////

// Main Function //
int main()
{
    // Data to be read in from text files
    BST<Book> *bookCatalog;
    BST<User *> *usersList;
    BST<copystruct> *copyList;

    // Read in data from student.txt and book.txt
    getUsers(usersList);
    getBooks(bookCatalog);
    getCopies(copyList);
    addCopiesToBook(bookCatalog, copyList);

    // Login system, can log in and log out on the same run

    while (true)
    {
        User *currentUser = login(usersList);
        time_t zeroTime = time(NULL);

        if (currentUser->type() == "Librarian")
        {
            librarianLoop(userToLibrarian(currentUser), bookCatalog, usersList, zeroTime);
        }
        else if (currentUser->type() == "Student")
        {
            readerLoop(userToReader(currentUser), bookCatalog, zeroTime, copyList);
        }
        else if (currentUser->type() == "Teacher")
        {
            readerLoop(userToReader(currentUser), bookCatalog, zeroTime, copyList);
        }
        else
        {
            cerr << "userType is invalid" << endl;
            exit(5);
        }
    }
}

void getUsers(BST<User *> usersList)
{
    // Do file I/O, filename is usersList.txt
    fstream fin("usersList.txt");
    if (fin.fail())
    {
        cerr << "error opening userList" << endl;
        exit(1);
    }

    /* It will be done variable by variable since each Person has 3 fields that need to be read.
     *
     * The format will be
     * Role(0=student, 1=teacher, 2=librarian)  user_name   password
     */
    // Check what type of user it is (student, teacher, librarian) and push to the vector

    int rolein;
    string userin;
    string passwordin;
    while (!(fin.eof()))
    {
        fin >> rolein >> userin >> passwordin;
        string temp;
        getline(fin, temp);
        if (rolein == 0) // for student
        {
            // assign values and attributes to temp student
            Student *temp = new Student(userin, passwordin);
            // push to vector
            usersList.nodeInsert(temp);
        }
        if (rolein == 1) // for teacher
        {
            // assign values and attributes to temp teacher
            Teacher *temp = new Teacher(userin, passwordin);
            // push to vector
            usersList.nodeInsert(temp);
        }
        if (rolein == 2) // for librarian
        {
            // assign values and attributes to temp teacher
            Librarian *temp = new Librarian(userin, passwordin);
            // push to vector
            usersList.nodeInsert(temp);
        }
    }
    // When finished reading in from file, close it
    fin.close();
}

void getBooks(BST<Book> &bookCatalog)
{
    // Do file I/O, filename is booksList.txt
    fstream books("booksList.txt");
    if (books.fail())
    {
        cerr << "error opening file" << endl;
        exit(1);
    }
    string isbnin;
    string titlein;
    string authorin;
    string catagoryin;
    while (!books.eof())
    {
        // For each line push a new Book object to the vector with the correct attributes
        books >> isbnin >> titlein >> authorin >> catagoryin;
        string temp;
        getline(books, temp);
        Book toinsert(isbnin, titlein, authorin, catagoryin); // FIXME - does this need a new?
        bookCatalog.nodeInsert(toinsert);
    }
    books.close();
}

void getCopies(BST<copystruct> &copyList)
{
    fstream copyfin("copiesList.txt");
    if (copyfin.fail())
    {
        cerr << "error opening file" << endl;
        exit(1);
    }
    string isbn;
    int id;
    while (!copyfin.eof())
    {
        copyfin >> isbn;
        copyfin >> id;
        copystruct temp;
        temp.isbnfile = isbn;
        temp.idfile = id;
        copyList.nodeInsert(temp);
    }
    copyfin.close();
}

void traverseToInsert(copystruct toInsert, TreeNode<Book> *bookNode)
{
    bookNode;
    if (bookNode == nullptr)
    {
        return;
    }

    if (bookNode->val.getIsbn() == toInsert.isbnfile)
    {
        BookCopy newBookCopy(toInsert.idfile); // FIXME - might not work since its not a pointer
        bookNode->val.copiesVector.push_back(newBookCopy);
        return;
    }

    /* Traverse left*/
    traverseToInsert(toInsert, bookNode->left);

    /* Traverse right */
    traverseToInsert(toInsert, bookNode->right);
}

void traverse(TreeNode<copystruct> *node, BST<Book> &bookCatalog)
{
    node;
    bookCatalog;
    if (node == nullptr)
    {
        return;
    }

    /* Traverse left*/
    traverse(node->left, bookCatalog);

    /* Thing to do */
    traverseToInsert(node->val, bookCatalog.root);

    /* Traverse right */
    traverse(node->right, bookCatalog);
}

void addCopiesToBook(BST<Book> &bookCatalog, BST<copystruct> &copyCatalog)
{
    traverse(copyCatalog.root, bookCatalog);
}

int verifytype(TreeNode<User *> *root, string user, string pass)
{
    if ((root->val.getUserName() == user) && (root->val.getPassword() == pass))
    {
        if (root->val.type() == "Student")
        {
            return 1;
        }
        if (root->val.type() == "Teacher")
        {
            return 2;
        }
        if (root->val.type() == "Librarian")
        {
            return 3;
        }
    }
    else
    {
        return 4;
    }
    /* Traverse left*/
    verifytype(root, user, pass);
    /* Traverse right */
    verifytype(root, user, pass);
}

Student *verifypersonS(TreeNode<User *> *root, string user, string pass)
{
    /* Traverse left*/
    verifypersonS(root, user, pass);
    if ((root->val->getUserName() == user) && (root->val->getPassword() == pass))
    {
        return userToStudent(root->val);
    }
    /* Traverse right */
    verifypersonS(root, user, pass);
}

Teacher *verifypersonT(TreeNode<User *> *root, string user, string pass)
{
    /* Traverse left*/
    verifypersonT(root, user, pass);
    if ((root->val->getUserName() == user) && (root->val->getPassword() == pass))
    {
        return userToTeacher(root->val);
    }
    /* Traverse right */
    verifypersonT(root, user, pass);
}

Librarian *verifypersonL(TreeNode<User *> *root, string user, string pass)
{
    /* Traverse left*/
    verifypersonL(root, user, pass);
    if ((root->val->getUserName() == user) && (root->val->getPassword() == pass))
    {
        return userToLibrarian(root->val);
    }
    /* Traverse right */
    verifypersonL(root, user, pass);
}

User *login(BST<User *> usersList)
{
    while (true)
    {
        // Prompt for username/ ask if they want to shutdown system
        cout << "Please enter a user name or type 'shutdown' to shut down LMS:" << endl;
        string userin;
        string passwordin;
        cin >> userin;

        // If shutdown system, exit
        if (userin == "shutdown")
        {
            cout << "Shutting Down..." << endl
                 << endl;
            exit(0);
        }
        else
        {
            // Else prompt for password
            cout << "Please enter a password:" << endl;
            cin >> passwordin;
            //
            //
            int type = verifytype(usersList.root, userin, passwordin);
            if (type == 1)
            {
                return verifypersonS(usersList.root, userin, passwordin);
            }
            if (type == 2)
            {
                return verifypersonT(usersList.root, userin, passwordin);
            }
            if (type == 3)
            {
                return verifypersonL(usersList.root, userin, passwordin);
            }
            if (type == 4)
            {
                // If not, print an error and say try again
                cout << "Account with those credentials was not found. Please try again" << endl
                     << endl;
            }
        }
    }
}

// TODO - (Daniel)
void readerLoop(Reader *user, BST<Book> *bookCatalog, time_t &zeroTime, BST<copystruct> *copyList)
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
            writeBackToBookFile(bookCatalog); // writing back to book text file
            writeBackToBCFile(bookCatalog);   // writing back to book copy text file
            return;
        }
        case 1:
        {
            // Search Book
            user->searchBook(bookCatalog, copyList);
            break;
        }
        case 2:
        {
            // Borrow Book
            user->borrowBook(bookCatalog, zeroTime);
            break;
        }
        case 3:
        {
            // Return Book
            user->returnBook(bookCatalog);
            break;
        }
        case 4:
        {
            // Renew Book
            user->renewBook(bookCatalog);
            break;
        }
        case 5:
        {
            // Reserve Book
            user->reserveBook(bookCatalog);
            break;
        }
        case 6:
        {
            // Cancel Book
            user->cancelBook(bookCatalog);
            break;
        }
        case 7:
        {
            // Printout Information
            cout << user;
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
            user->feelingLucky(bookCatalog);
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

// TODO - (Ethan)
void librarianLoop(Librarian *user, BST<Book> *bookCatalog, BST<User *> *usersList, time_t &zeroTime, int &idCount)
{
    while (true)
    {
        int currentDate = date(zeroTime);
        cout << "Welcome back, " << user->type() << "\n"
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
            writeBackToUserFile(usersList); // writing back to user text file
            return;
        }
        case 2:
        {
            // Add Book
            user->addBook(bookCatalog);
            break;
        }
        case 3:
        {
            // Delete Book
            user->deleteBook(bookCatalog);
            break;
        }
        case 4:
        {
            // Search User
            user->searchUser(usersList);
            break;
        }
        case 5:
        {
            // Add User
            user->addUser(usersList);
            break;
        }
        case 6:
        {
            // Delete User
            user->deleteUser(usersList);
            break;
        }
        case 7:
        {
            // My Information
            cout << user;
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
