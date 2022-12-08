#pragma once

#include "BookCopy.h"
#include "DateFunction.h" //
#include "User.h"
#include "Book.h" //
#include "Structs.h"

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
    vector<Book> booksReserved;
    int penalties; // Number of times a book has been returned late

public:
    // Getters //
    int getMaxCopies();
    int getMaxLoanTime();
    vector<BookCopy> getBooksBorrowed();
    // Operator Overloading //
    friend ostream &operator<<(ostream &output, Book &book);
    friend istream &operator>>(istream &input, Book &book);
    // Main functions //
    void sortExpiration(vector<BookCopy> &copyList, int low, int high);
    void getBookInfo(Book book);
    void searchBook(vector<Book> bookCatalog);
    void borrowBook(vector<Book> &bookCatalog, time_t &zeroTime);
    void returnBook(vector<Book> &bookCatalog);
    void renewBook(vector<Book> &bookCatalog);
    void reserveBook(vector<Book> &bookCatalog);
    void cancelBook(vector<Book> &bookCatalog);
    void feelingLucky(vector<Book> &bookCatalog);
    void printMyInfo();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

// Casting //
Reader *userToReader(User *toCast)
{
    return dynamic_cast<Reader *>(toCast);
}

// Getters //
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

int partition(vector<BookCopy> lib, int low, int high)
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

void quickSort(vector<BookCopy> lib, int low, int high)
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

int expPartition(vector<BookCopy> &copyList, int low, int high)
{
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (copyList.at(j).getExpirationDate() <= copyList.at(high).getExpirationDate())
        {
            i++;
            swap(copyList.at(i), copyList.at(j));
        }
    }

    swap(copyList.at(high), copyList.at(i + 1));

    return i + 1;
}

void Reader::sortExpiration(vector<BookCopy> &copyList, int low, int high)
{
    if (low < high)
    {
        int pi = expPartition(copyList, low, high);

        // recursive call on the left of pivot
        sortExpiration(copyList, low, pi - 1);

        // recursive call on the right of pivot
        sortExpiration(copyList, pi + 1, high);
    }
}

void Reader::getBookInfo(Book book)
{
    cout << "ISBN: " << book.getIsbn() << endl
         << "Title: " << book.getTitle() << endl
         << "Author: " << book.getAuthor() << endl
         << "Category: " << book.getCategory() << endl
         << "Copy IDs: " << endl;
    vector<BookCopy> copies = book.getCopies();
    sortExpiration(copies, 0, copies.size() - 1);
    for (int i = 0; i < copies.size(); i++)
    {
        cout << "ID: " << copies.at(i).getID() << ", ";
        if (copies.at(i).getExpirationDate() == -1)
        {
            cout << "AVAILABLE" << endl;
        }
        else
        {
            cout << "Expires " << copies.at(i).getExpirationDate() << endl;
        }
    }
}

void Reader::searchBook(vector<Book> bookCatalog)
{
    int searchChoice;
    cout << "What do you want to search:" << endl;
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
        for (int i = 0; i < bookCatalog.size(); i++)
        {
            if (bookCatalog.at(i).getIsbn() == inputISBN)
            {
                getBookInfo(bookCatalog.at(i));
                cout << endl;
            }
        }

        break;
    }
    case 2:
    {
        string inputTitle;
        cout << "What's your book's title?: ";
        cin >> inputTitle;

        // Search for matching titles and print them
        for (int i = 0; i < bookCatalog.size(); i++)
        {
            if (bookCatalog.at(i).getTitle() == inputTitle)
            {
                getBookInfo(bookCatalog.at(i));
                cout << endl;
            }
        }

        break;
    }
    case 3:
    {
        string inputCategory;
        cout << "What's your book's category?: ";
        cin >> inputCategory;

        // Search for matching category and print them
        for (int i = 0; i < bookCatalog.size(); i++)
        {
            if (bookCatalog.at(i).getCategory() == inputCategory)
            {
                getBookInfo(bookCatalog.at(i));
                cout << endl;
            }
        }
        break;
    }
    case 4:
    {
        int inputID;
        cout << "What's your book's ID?: ";
        cin >> inputID;
        vector<BookCopy> copies;

        for (int i = 0; i < bookCatalog.size(); i++)
        {
            copies = bookCatalog.at(i).getCopies();
            for (int j = 0; j < copies.size(); j++)
            {
                if (copies.at(j).getID() == inputID)
                {
                    getBookInfo(bookCatalog.at(i));
                    cout << endl;
                    break;
                }
            }
        }
        break;
    }
    default:
    {
        cout << "That's not a valid option! Try again!" << endl;
        break;
    }
    }
}

void Reader::borrowBook(vector<Book> &bookCatalog, time_t &zeroTime)
{
    // Check if there are overdue books
    int currentTime = date(zeroTime);
    vector<BookCopy> expiredBooks;
    vector<Book> temp = bookCatalog;
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
    BookCopy toBeBorrowed;
    Book matchedBook;
    vector<BookCopy> copies;
    toBeBorrowed.setID(-1);
    for (int i = 0; i < bookCatalog.size(); i++)
    {
        copies = bookCatalog.at(i).getCopies();
        for (int j = 0; j < copies.size(); j++)
        {
            if (copies.at(j).getID() == inputID)
            {
                matchedBook = bookCatalog.at(i);
                toBeBorrowed = copies.at(j);
                break;
            }
        }
    }

    if (toBeBorrowed.getID() != -1)
    {
        exists = true;
        if (toBeBorrowed.getReaderName() == "")
        {
            available = true;
        }
    }

    // Now check if someone else is on the reserved linked list
    bool goodToContinue;

    // Check the first entry of the linked list to see if it exists
    if (matchedBook.getReservers() == nullptr)
    {
        // If the linked list is empty then the user can borrow the book
        goodToContinue = true;
    }
    else
    {
        goodToContinue = ((matchedBook.getReservers()->username == this->getUsername()) ? true : false);
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
    toBeBorrowed.setReaderName(this->getUsername());
    this->copiesBorrowed.push_back(toBeBorrowed);

    // Change the attributes of the book
    for (int i = 0; i < bookCatalog.size(); i++)
    {
        copies = bookCatalog.at(i).getCopies();
        for (int j = 0; j < copies.size(); j++)
        {
            if (copies.at(j).getID() == inputID)
            {
                copies.at(j).setReaderName(this->getUsername());
                copies.at(j).setStartDate(currentTime);
                copies.at(j).setExpirationDate(currentTime + this->getMaxLoanTime());
                break;
            }
        }
    }
    return;
}

void Reader::returnBook(vector<Book> &bookCatalog)
{
}

void Reader::renewBook(vector<Book> &bookCatalog)
{
}

void Reader::reserveBook(vector<Book> &bookCatalog)
{
}

void Reader::cancelBook(vector<Book> &bookCatalog)
{
    // Print the books that the current user has reserved

    // Ask for the isbn of the book that the user wants to cancel the reservation of
}

void Reader::feelingLucky(vector<Book> &bookCatalog)
{
    vector<Book> mostFavorited;
    // Go through the catalog and add books that have a number of favorites > 0 to the vector

    if (mostFavorited.size() == 0)
    {
        cout << "It seems like there are no favorited books so far, go and favorite some of them first." << endl
             << endl;
        return;
    }

    // Sort mostFavorited vector by number of favorites

    cout << "The top 10 most liked books are:" << endl;

    // Print out the vector
}

void Reader::printMyInfo()
{
    cout << (*this);
}
