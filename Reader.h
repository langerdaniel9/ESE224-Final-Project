#pragma once

#include "BookCopy.h"
#include "DateFunction.h"
#include "User.h"
#include "Book.h"
#include "Structs.h"
#include "BST.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>

using namespace std;

class Reader : public User
{
protected:
    int maxCopies;
    int maxLoanTime;
    vector<BookCopy> copiesBorrowed;
    vector<Book> BooksReserved;
    int penalties;
    string type();

public:
    // Getters //
    int getMaxCopies();
    int getMaxLoanTime();
    vector<BookCopy> getBooksBorrowed();
    // Operator Overloading //
    friend ostream &operator<<(ostream &output, Book &book);
    friend istream &operator>>(istream &input, Book &book);
    // Main functions //
    void searchBook(BST<Book> *bookCatalog, BST<copystruct> *copyList);
    void borrowBook(BST<Book> *&bookCatalog, time_t &zeroTime);
    void returnBook(BST<Book> *&bookCatalog);
    void renewBook(BST<Book> *&bookCatalog);
    void reserveBook(BST<Book> *&bookCatalog);
    void cancelBook(BST<Book> *&bookCatalog);
    void feelingLucky(BST<Book> *&bookCatalog);
    void myInformation(BST<Book> *&bookCatalog);
    string type();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

int Reader::getMaxCopies()
{
    return this->maxCopies;
}

int Reader::getMaxLoanTime()
{
    return this->maxLoanTime;
}

vector<BookCopy> Reader::getBooksBorrowed()
{
    return this->copiesBorrowed;
}

int partition(vector<BookCopy> lib, int low, int high) // FIXME - might not be needed
{
    // partition starting from first element;
    // then comparing each element by the last element in the array

    int i = low - 1; // i => index of first array (array lower than "high" value)

    for (int j = low; j < high; j++)
    { // j => index of second array (array greater than "high" value)
        if (lib.at(j).getID() <= lib.at(high).getID())
        {
            i++;
            swap(lib.at(i), lib.at(j));
        }
    }

    // Swapping the "high" value to where it needs to be
    swap(lib.at(high), lib.at(i + 1));

    // returns the index of where the "high" value is
    return i + 1;
}

void quickSort(vector<BookCopy> lib, int low, int high) // FIXME - this one too
{
    if (low < high)
    {
        int pi = partition(lib, low, high);

        // recursive call on the left of pivot
        quickSort(lib, low, pi - 1);

        // recursive call on the right of pivot
        quickSort(lib, pi + 1, high);
    }
}

// TODO - when fixed move to Book.h
BookCopy IDInOrderTraversal(TreeNode<Book> *node, int inputID)
{
    if (node == nullptr)
    {
        BookCopy defaultBook(-1);
        return defaultBook;
    }

    // visit left child
    IDInOrderTraversal(node->left, inputID);

    // What to do at current node
    for (int i = 0; i < node->val.copiesVector.size(); i++)
    {
        if (node->val.copiesVector.at(i).getID() == inputID)
        {
            return node->val.copiesVector.at(i);
        }
    }
    // visit right child
    IDInOrderTraversal(node->right, inputID);
}

// TODO - move to Book.h
Book returnBookGivenID(TreeNode<Book> *node, int inputID)
{
    if (node == nullptr)
    {
        return; // FIXME
    }

    // visit left child
    return returnBookGivenID(node->left, inputID);

    // What to do at current node
    // Check through bookCopies vector for an id that matches inputID
    for (int i = 0; i < node->val.copiesVector.size(); i++)
    {
        if (node->val.copiesVector.at(i).getID() == inputID)
        {
            return node->val;
        }
    }

    // visit right child
    return returnBookGivenID(node->right, inputID);
}

// TODO - Move to Book.h
void checkOutBookInCatalog(TreeNode<Book> *inputBST, int bookID, int startLoanTime, int endLoanTime, string readerUsername)
{
    if (inputBST == nullptr)
    {
        return;
    }

    // visit left child
    checkOutBookInCatalog(inputBST->left, bookID, startLoanTime, endLoanTime, readerUsername);

    /**************************/
    for (int i = 0; i < inputBST->val.copiesVector.size(); i++)
    {
        if (inputBST->val.copiesVector.at(i).getID() == bookID)
        {
            inputBST->val.copiesVector.at(i).setStartDate(startLoanTime);
            inputBST->val.copiesVector.at(i).setExpirationDate(endLoanTime);
            inputBST->val.copiesVector.at(i).setReaderName(readerUsername);
            return;
        }
    }
    /**************************/

    // visit right child
    checkOutBookInCatalog(inputBST->right, bookID, startLoanTime, endLoanTime, readerUsername);
}

void renewBookInCatalog(TreeNode<Book> *inputBST, int inputID, int maxLoanTime)
{
    if (inputBST == NULL)
    {
        return;
    }

    // visit left child
    renewBookInCatalog(inputBST->left, inputID, maxLoanTime);

    /**************************/
    for (int i = 0; i < inputBST->val.copiesVector.size(); i++)
    {
        if (inputBST->val.copiesVector.at(i).getID() == inputID)
        {
            inputBST->val.copiesVector.at(i).setExpirationDate(inputBST->val.copiesVector.at(i).getExpirationDate() + maxLoanTime);
            return;
        }
    }
    /**************************/

    // visit right child
    renewBookInCatalog(inputBST->right, inputID, maxLoanTime); // visit right child
}

string copiesInOrderTraversal(TreeNode<copystruct> *inputBST, int inputID)
{
    if (inputBST == NULL)
    {
        return "";
    }

    // visit left child
    copiesInOrderTraversal(inputBST->left, inputID);

    /**************************/
    if (inputBST->val.idfile == inputID)
    {
        return inputBST->val.isbnfile;
    }
    /**************************/

    // visit right child
    copiesInOrderTraversal(inputBST->right, inputID);
}

void Reader::searchBook(BST<Book> *bookCatalog, BST<copystruct> *copyList)
{
    int searchChoice;
    cout << "What category do you want to search by:" << endl;
    cout << "(1) - ISBN" << endl;
    cout << "(2) - Title" << endl;
    cout << "(3) - Category" << endl;
    cout << "(4) - ID" << endl;
    cin >> searchChoice;

    switch (searchChoice)
    {
    case 1:
    {
        string inputISBN;
        cout << "What's your book's ISBN value?: ";
        cin >> inputISBN;

        // Search for matching isbn and print if found
        bookCatalog->binarySearch(inputISBN);

        break;
    }
    case 2:
    {
        string inputTitle;
        cout << "What's your book's title?: ";
        cin >> inputTitle;

        // Search for matching titles and print them
        bookCatalog->search(bookCatalog->root, inputTitle, true);

        break;
    }
    case 3:
    {
        string inputCategory;
        cout << "What's your book's category?: ";
        cin >> inputCategory;

        // Search for matching category and print them
        bookCatalog->search(bookCatalog->root, inputCategory, false);
        break;
    }
    case 4:
    {
        int inputID;
        cout << "What's your book's ID?: ";
        cin >> inputID;

        // Get corresponding ISBN
        string correspondingISBN = copiesInOrderTraversal(copyList->root, inputID); // gets the corresponding ISBN

        // Print details about the book using ISBN
        bookCatalog->binarySearch(correspondingISBN);
        break;
    }
    default:
    {
        cout << "That's not a valid option! Try again!" << endl;
        break;
    }
    }
}

void Reader::borrowBook(BST<Book> *&bookCatalog, time_t &zeroTime)
{
    // Check if there are overdue books
    int currentTime = date(zeroTime);
    vector<BookCopy> expiredBooks;
    BST<Book> *temp = bookCatalog;
    bool expired = false;

    for (int i = 0; i < this->getBooksBorrowed().size(); i++)
    {
        if (this->getBooksBorrowed().at(i).getExpirationDate() < currentTime)
        {
            expired = true;
            expiredBooks.push_back(this->getBooksBorrowed().at(i));
        }
    }
    if (expired)
    {
        cout << "You have books that are already past due, return those before borrowing more. Your expired books are:" << endl;
        for (BookCopy book : expiredBooks)
        {
            cout << book;
        }
        return;
    }

    // Ask for the ID of the book copy to borrow
    int inputID;
    cout << "What is the ID of the book you wish to borrow: ";
    cin >> inputID;

    // Check if that ID exists in bookCatalog and that there are available copies
    bool exists = false;
    bool available = false;
    BookCopy toBeBorrowed = IDInOrderTraversal(bookCatalog->root, inputID);
    if (toBeBorrowed.getID() != -1)
    {
        exists = true;
        if (toBeBorrowed.getReaderName() == "")
        {
            available = true;
        }
    }

    // Now check if someone else is on the reserved linked list
    // Match the ID given to a Book
    Book matchedBook = returnBookGivenID(bookCatalog->root, inputID);

    bool goodToContinue;

    // Check the first entry of the linked list to see if it exists
    if (matchedBook.getReservers() == nullptr)
    {
        // If the linked list is empty then the user can borrow the book
        goodToContinue = true;
    }
    else
    {
        goodToContinue = ((matchedBook.getReservers()->data == this->getUserName()) ? true : false);
    }

    if (!goodToContinue)
    {
        cout << "It seems someone has already reserved this book, please wait for the reservation to free up" << endl;
        return;
    }

    if (!exists)
    {
        cout << "That ID does not exist in the library, double check the ID and try again" << endl;
        return;
    }
    if (!available)
    {
        cout << "There are no more copies of this book left, try reserving this book.";
        return;
    }

    // Next check if the user is over their maxCopies limit
    if (this->getBooksBorrowed().size() > this->getMaxCopies())
    {
        cout << "You cannot borrow any more books, since you are already at your limit" << endl;
        return;
    }

    // If all of the conditions are met, add the book to copiesBorrowed
    toBeBorrowed.setStartDate(currentTime);
    toBeBorrowed.setExpirationDate(currentTime + this->getMaxLoanTime());
    toBeBorrowed.setReaderName(this->getUserName());
    this->copiesBorrowed.push_back(toBeBorrowed);

    // Change the attributes of the book
    checkOutBookInCatalog(bookCatalog->root, inputID, currentTime, (currentTime + this->getMaxLoanTime()), this->getUserName());
    return;
}

void Reader::returnBook(BST<Book> *&bookCatalog) // FIXME
{
    if (this->getBooksBorrowed().size() == 0)
    {
        cout << "You are not currently borrowing any books." << endl
             << endl;
        return;
    }

    cout << "Here are all the books you are currently borrowing:" << endl;

    for (BookCopy book : this->getBooksBorrowed())
    {
        cout << book;
    }

    cout << "What is the ID of the book you would like to return?" << endl;
    int id;
    cin >> id;

    // Remove book from users 'borrowed books' list
    bool returned = false;
    for (int i = 0; i < this->copiesBorrowed.size(); i++)
    {
        if (this->copiesBorrowed.at(i).getID() == id)
        {
            cout << "Returning book" << endl
                 << endl;
            returned = true;
            this->copiesBorrowed.erase(this->copiesBorrowed.begin() + i);
        }
    }

    if (!returned)
    {
        cout << endl
             << "You dont have that book checked out, try again" << endl
             << endl;
        return;
    }

    // Change the properties of the returned book to reflect that it is available
    checkOutBookInCatalog(bookCatalog->root, id, -1, -1, "");

    // TODO - start 5 day timer here somehow

    return;
}

void Reader::renewBook(BST<Book> *&bookCatalog) // FIXME
{
    if (this->getBooksBorrowed().size() == 0)
    {
        cout << "You are not currently borrowing any books." << endl
             << endl;
        return;
    }

    cout << "Here are all the books you are currently borrowing:" << endl
         << endl;

    for (BookCopy book : this->getBooksBorrowed())
    {
        cout << book;
    }

    cout << "What is the ID of the book you would like to renew?" << endl;
    int id;
    cin >> id;

    bool renewed = false;
    for (int i = 0; i < this->getBooksBorrowed().size(); i++)
    {
        if (this->getBooksBorrowed().at(i).getID() == id)
        {
            renewed = true;
            cout << "Renewing book" << endl
                 << endl;

            copiesBorrowed.at(i).setExpirationDate(copiesBorrowed.at(i).getExpirationDate() + this->getMaxLoanTime());
        }
    }

    if (renewed)
    {
        renewBookInCatalog(bookCatalog->root, id, this->getMaxLoanTime());
    }

    if (!renewed)
    {
        cout << endl
             << "Cant renew that book since you dont have it checked out" << endl
             << endl;
        return;
    }
}

void Reader::reserveBook(BST<Book> *&bookCatalog) // FIXME
{
    int inputID;
    cout << "What is an ID of the book you wish to reserve? ";
    cin >> inputID;

    // Check if that ID exists in bookCatalog and that there are available copies
    bool exists = false;
    bool available = false;
    BookCopy toBeBorrowed = IDInOrderTraversal(bookCatalog->root, inputID);
    if (toBeBorrowed.getID() != -1)
    {
        exists = true;
        if (toBeBorrowed.getReaderName() == "")
        {
            available = true;
        }
    }

    if (!exists)
    {
        cout << "That ID does not exist in the library, double check the ID and try again" << endl;
        return;
    }
    if (!available)
    {
        Book book = returnBookGivenID(bookCatalog->root, inputID);
        book.insertReader(this->getUserName());
        BooksReserved.push_back(book);
        return;
    }
    else
    {
        cout << "This book is currently available, try borrowing this book." << endl;
        return;
    }
}

void Reader::cancelBook(BST<Book> *&bookCatalog) // FIXME
{
    // Check that reader currently is reserving book
    int inputID;
    cout << "What is an ID of the book you wish to cancel? ";
    cin >> inputID;

    bool reserved = false;

    Book book = returnBookGivenID(bookCatalog->root, inputID);
    for (int i = 0; i < BooksReserved.size(); i++)
    {
        if (BooksReserved.at(i).getIsbn() == book.getIsbn())
        {
            book.deleteReader(this->getUserName());
            BooksReserved.erase(BooksReserved.begin() + i);
            reserved = true;
            return;
        }
    }
    if (!reserved)
    {
        cout << "You are not currently reserving this book." << endl;
        return;
    }
}

void Reader::feelingLucky(BST<Book> *&bookCatalog)
{
    // TODO - maybe if we have time
}

void Reader::myInformation(BST<Book> *&bookCatalog)
{
    cout << "Username: " << this->getUserName() << endl;
    cout << "Password: " << this->getPassword() << endl
         << endl;

    cout << "Books currently borrowed:" << endl;
    for (int i = 0; i < copiesBorrowed.size(); i++)
    {
        Book book = returnBookGivenID(bookCatalog->root, copiesBorrowed.at(i).getID());
        cout << "ID:\t" << copiesBorrowed.at(i).getID() << endl;
        cout << book << endl;
    }

    cout << "Books currently reserved:" << endl;
    for (int i = 0; i < BooksReserved.size(); i++)
    {
        cout << BooksReserved.at(i) << endl;
    }
}

string Reader::type()
{
    return "Reader";
}

// Casting //
Reader *userToReader(User *toCast)
{
    return dynamic_cast<Reader *>(toCast);
}