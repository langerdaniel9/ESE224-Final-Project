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
                cout << "Book Successfully Borrowed!" << endl;
                cout << copies.at(j) << endl;
                break;
            }
        }
    }

    return;
}

void Reader::returnBook(vector<Book> &bookCatalog)
{
    if (this->getBooksBorrowed().size() == 0)
    {
        cout << "You are not borrowing any books..." << endl;
        return;
    }
    cout << "The books you are currently borrowing are: " << endl;
    for (BookCopy book : this->getBooksBorrowed())
    {
        // possible todo
        cout << book;
    }
    int idin;
    cout << "Please input the id of the book to be returned: " << endl;
    cin >> idin;
    bool isreturned = false;
    for (int i = 0; i < this->copiesBorrowed.size(); i++)
    {
        if (this->copiesBorrowed.at(i).getID() == idin)
        {
            cout << "Book with id:" << idin << "is being renewed" << endl;
            isreturned = true;
            this->copiesBorrowed.erase(this->copiesBorrowed.begin() + i);
        }
    }
    if (!isreturned)
    {
        cout << "The book has nto been found in your possesion, please try again..." << endl;
        return;
    }
    for (int i = 0; i < bookCatalog.size(); i++)
    {
        for (int j = 0; i < bookCatalog.at(i).getCopies().size(); i++)
        {
            if (bookCatalog.at(i).getCopies().at(j).getID() == idin)
            {
                bookCatalog.at(i).getCopies().at(j).setExpirationDate(-1);
                bookCatalog.at(i).getCopies().at(j).setStartDate(-1);
                bookCatalog.at(i).getCopies().at(j).setReaderName("");
                cout << "Did you like the book?(y/n)" << endl;
                char response;
                cin >> response;
                if (response == 'y')
                {
                    bookCatalog.at(i).favorite();
                    cout << "Thank you for your response!" << endl;
                }
            }
        }
    }
}

void Reader::renewBook(vector<Book> &bookCatalog) {

    if (this->getBooksBorrowed().size() == 0)
    {
        cout << "You are not currently borrowing any books." << endl
            << endl;
        return;
    }

    cout << "Here are all the books you are currently borrowing:" << endl
        << endl;

    vector<BookCopy> copies;
    for (BookCopy book : this->getBooksBorrowed())
    {
        cout << "ID: " << book.getID() << ", "
            << "Title: ";
        for (int i = 0; i < bookCatalog.size(); i++)
        {
            copies = bookCatalog.at(i).getCopies();
            for (int j = 0; j < copies.size(); j++)
            {
                if (copies.at(j).getID() == book.getID())
                {
                    cout << bookCatalog.at(i).getTitle() << endl;
                    break;
                }
            }
        }
    }
    cout << endl;

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

    vector<BookCopy> copies;
    if (renewed)
    {
        for (int i = 0; i < bookCatalog.size(); i++)
        {
            copies = bookCatalog.at(i).getCopies();
            for (int j = 0; j < copies.size(); j++)
            {
                if (copies.at(j).getID() == id)
                {
                    copies.at(j).setExpirationDate(copies.at(j).getExpirationDate() + this->getMaxLoanTime());
                    break;
                }
            }
        }
    }

    if (!renewed)
    {
        cout << endl
            << "Cant renew that book since you dont have it checked out" << endl
            << endl;
        return;
    }
}

void Reader::reserveBook(vector<Book> &bookCatalog)
{
    string inputISBN;
    cout << "What is the ISBN of the book you wish to reserve? ";
    cin >> inputISBN;

    // Check if that ISBN exists in bookCatalog and that there are available copies
    bool exists = false;
    bool available = false;
    Book toBeBorrowed;

    // Finds specific Book given the ISBN; also signifies that the Book exists
    for (int i = 0; i < bookCatalog.size(); i++) {
        if (bookCatalog.at(i).getIsbn() == inputISBN) {
            exists = true;
            toBeBorrowed = bookCatalog.at(i);
        }
    }

    // Checks if the Book is available (if a BookCopy has a reader name that is empty)
    for (int i = 0; i < toBeBorrowed.copies.size(); i++) {
        if (toBeBorrowed.copies.at(i).getReaderName() == "") {
            available = true;
        }
    }

    if (!exists)
    {
        cout << "That ISBN does not exist in the library, double check the ISBN and try again" << endl;
        return;
    }
    if (!available)
    {
        Book book;
        // Finds the book to reserve if it is not available
        for (int i = 0; i < bookCatalog.size(); i++) {
            if (bookCatalog.at(i).getIsbn() == inputISBN) {
                book = bookCatalog.at(i);
            }
        }

        if (book.getIsbn() == "-1")
        {
            cerr << "Couldnt find match";
            exit(1);
        }

        // Inserts the reader's name to the Book 
        book.insertReader(this->getUsername());
        
        // Adds the book to the reader's vector of reserved books
        this->booksReserved.push_back(book);
        return;
    }
    else
    {
        cout << "This book is currently available, try borrowing this book." << endl;
        return;
    }
}

void Reader::cancelBook(vector<Book> &bookCatalog)
{
    if (this->booksReserved.size() == 0)
    {
        cout << "You do not currently have any books reserved, so you cannot cancel any reservations." << endl
             << endl;
        return;
    }
    // Print the books that the current user has reserved
    cout << "These are the books that you currently have reserved:" << endl;

    for (Book bk : this->booksReserved)
    {
        cout << "Title: " << bk.getTitle() << endl
             << "ISBN: " << bk.getIsbn() << endl;
    }

    // Ask for the isbn of the book that the user wants to cancel the reservation of
    cout << "What is the ISBN of the book you want to cancel the reservation of? ";
    string isbnToCancel;
    cin >> isbnToCancel;

    // Remove that book from the reserved books vector of the user
    for (int i = 0; i < this->booksReserved.size(); i++)
    {
        if (this->booksReserved.at(i).getIsbn() == isbnToCancel)
        {
            this->booksReserved.erase(this->booksReserved.begin() + i);
            return;
        }
    }

    // Remove the user from the linked list of reservers on the book within the catalog

    struct node *current;
}

int favPartition(vector<Book> lib, int low, int high)
{
    // partition starting from first element;
    // then comparing each element by the last element in the array

    int i = low - 1; // i => index of first array (array lower than "high" value)

    for (int j = low; j < high; j++)
    { // j => index of second array (array greater than "high" value)
        if (lib.at(j).getTimesFavorited() <= lib.at(high).getTimesFavorited())
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

void favQS(vector<Book> lib, int low, int high)
{
    if (low < high)
    {
        int pi = favPartition(lib, low, high);

        // recursive call on the left of pivot
        favQS(lib, low, pi - 1);

        // recursive call on the right of pivot
        favQS(lib, pi + 1, high);
    }
}

void mostFavoritesSort(vector<Book> &mostFavorited)
{
    favQS(mostFavorited, 0, mostFavorited.size() - 1);
}

void Reader::feelingLucky(vector<Book> &bookCatalog)
{
    vector<Book> mostFavorited;

    // Go through the catalog and add books that have a number of favorites > 0 to the vector
    for (int i = 0; i < bookCatalog.size(); i++)
    {
        if (bookCatalog.at(i).getTimesFavorited() > 0)
        {
            mostFavorited.push_back(bookCatalog.at(i));
        }
    }

    if (mostFavorited.size() == 0)
    {
        cout << "It seems like there are no favorited books so far, go and favorite some of them first." << endl
             << endl;
        return;
    }

    // Sort mostFavorited vector by number of favorites
    mostFavoritesSort(mostFavorited);

    cout << "The top 10 most liked books are:" << endl;

    // Print out the vector
    for (Book bk : mostFavorited)
    {
        cout << bk;
    }
}

void Reader::printMyInfo()
{
    cout << "Username: " << this->getUsername() << endl;
    cout << "Password: " << this->getPassword() << endl;
    for (int i = 0; i < this->)
}
