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
    friend ostream &operator<<(ostream &output, Reader &reader);
    friend istream &operator>>(istream &input, Reader &reader);
    // Main functions //
    void searchBook(vector<Book> &bookCatalog);
    void borrowBook(vector<Book> &bookCatalog, time_t &zeroTime);
    void returnBook(vector<Book> &bookCatalog, time_t zer);
    void renewBook(vector<Book> &bookCatalog);
    void reserveBook(vector<Book> &bookCatalog);
    void cancelBook(vector<Book> &bookCatalog);
    void feelingLucky(vector<Book> &bookCatalog);
    void printMyInfo(vector<Book> &bookCatalog);
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

void Reader::searchBook(vector<Book> &bookCatalog)
{
    int searchChoice;
    cout << "What do you want to search:" << endl;
    cout << "(1) - ISBN" << endl;
    cout << "(2) - Title" << endl;
    cout << "(3) - Category" << endl;
    cout << "(4) - ID" << endl;
    cin >> searchChoice;

    vector<Book> searchMatches;
    searchMatches.clear();

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
            // At least a partial match on isbn
            string s = bookCatalog.at(i).getIsbn();
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            transform(inputISBN.begin(), inputISBN.end(), inputISBN.begin(), ::tolower);
            if (s.find(inputISBN) != string::npos)
            {
                // Books with matching criteria get pushed to search results vector
                searchMatches.push_back(bookCatalog.at(i));
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
            // At least a partial match on title
            string s = bookCatalog.at(i).getTitle();
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            transform(inputTitle.begin(), inputTitle.end(), inputTitle.begin(), ::tolower);
            if (s.find(inputTitle) != string::npos)
            {
                // Books with matching criteria get pushed to search results vector
                searchMatches.push_back(bookCatalog.at(i));
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
            // At least a partial match on category
            string s = bookCatalog.at(i).getCategory();
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            transform(inputCategory.begin(), inputCategory.end(), inputCategory.begin(), ::tolower);
            if (s.find(inputCategory) != string::npos)
            {
                // Books with matching criteria get pushed to search results vector
                searchMatches.push_back(bookCatalog.at(i));
            }
        }
        break;
    }
    case 4:
    {
        int inputID;
        cout << "What's your book's ID?: ";
        cin >> inputID;

        for (int i = 0; i < bookCatalog.size(); i++)
        {
            for (int j = 0; j < bookCatalog.at(i).copies.size(); j++)
            {
                if (bookCatalog.at(i).copies.at(j).getID() == inputID)
                {
                    searchMatches.push_back(bookCatalog.at(i));
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

    // Sort searchMatches
    // sorting by title
    if (searchMatches.size() >= 2)
    {
        for (int i = 0; i < searchMatches.size() - 1; i++)
        {
            for (int j = 0; j < (searchMatches.size() - i - 1); j++)
            {
                int titleCompare = searchMatches.at(j).getTitle().compare(searchMatches.at(j + 1).getTitle());
                if (titleCompare > 0)
                {
                    swap(searchMatches.at(j), searchMatches.at(j + 1));
                }
            }
        }
    }

    // Print searchMatches
    if (searchMatches.size() > 0)
    {
        cout << endl
             << "Books that match your search critera:" << endl
             << endl;
        for (Book searchResult : searchMatches)
        {
            cout << searchResult;
        }
    }
    else
    {
        cout << endl
             << "There were no books that match that search critera, try again with a different search." << endl
             << endl;
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
    toBeBorrowed.setID(-1);
    for (int i = 0; i < bookCatalog.size(); i++)
    {
        for (int j = 0; j < bookCatalog.at(i).copies.size(); j++)
        {
            if (bookCatalog.at(i).copies.at(j).getID() == inputID)
            {
                exists = true;
                matchedBook = bookCatalog.at(i);
                toBeBorrowed = bookCatalog.at(i).copies.at(j);
                break;
            }
        }
    }

    if (toBeBorrowed.getReaderName() == "")
    {
        available = true;
    }

    // Now check if someone else is on the reserved linked list
    bool goodToContinue = false;

    for (int i = 0; i < bookCatalog.size(); i++)
    {
        if (bookCatalog.at(i).getIsbn() == matchedBook.getIsbn())
        {
            if (bookCatalog.at(i).getReservers() == NULL)
            {
                break;
            }
            while (bookCatalog.at(i).getReservers()->borrowBy < currentTime)
            {
                if (bookCatalog.at(i).getReservers()->username != this->getUsername())
                {
                    cerr << "Hey... this is awkward... you can't do that... sorry." << endl;
                    exit(3);
                }
                for (int i = 0; i < booksReserved.size(); i++)
                {
                    if (this->booksReserved.at(i).getIsbn() == matchedBook.getIsbn())
                    {
                        this->booksReserved.erase(booksReserved.begin() + i);
                    }
                }
                bookCatalog.at(i).deleteFirst();
                if (bookCatalog.at(i).getReservers() == NULL)
                {
                    break;
                }
            }
            break;
        }
    }

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

    string tempISBN;

    // Deleting reader from linked list
    for (int i = 0; i < bookCatalog.size(); i++)
    {
        for (int j = 0; j < bookCatalog.at(i).copies.size(); j++)
        {
            if (bookCatalog.at(i).copies.at(j).getID() == inputID)
            {
                bookCatalog.at(i).deleteReader(this->getUsername());
                tempISBN = bookCatalog.at(i).getIsbn();
            }
        }
    }

    // Deletes the reserved book from reader's vector of reserved books
    for (int i = 0; i < booksReserved.size(); i++)
    {
        if (booksReserved.at(i).getIsbn() == tempISBN)
        {
            booksReserved.erase(booksReserved.begin() + i);
        }
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
        for (int j = 0; j < bookCatalog.at(i).copies.size(); j++)
        {
            if (bookCatalog.at(i).copies.at(j).getID() == inputID)
            {
                bookCatalog.at(i).copies.at(j).setReaderName(this->getUsername());
                bookCatalog.at(i).copies.at(j).setStartDate(currentTime);
                bookCatalog.at(i).copies.at(j).setExpirationDate(currentTime + this->getMaxLoanTime());
                cout << "Book Successfully Borrowed!" << endl;
                cout << bookCatalog.at(i).copies.at(j) << endl;
                break;
            }
        }
    }

    return;
}

void Reader::returnBook(vector<Book> &bookCatalog, time_t zerotime)
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
            cout << "Book with id " << idin << " is being returned" << endl;
            isreturned = true;
            int currenttime = date(zerotime);
            if (currenttime > this->copiesBorrowed.at(i).getExpirationDate())
            {
                this->penalties++;
            }
            this->copiesBorrowed.erase(this->copiesBorrowed.begin() + i);
        }
    }
    if (!isreturned)
    {
        cout << "The book has not been found in your possesion, please try again..." << endl;
        return;
    }
    for (int i = 0; i < bookCatalog.size(); i++)
    {
        for (int j = 0; j < bookCatalog.at(i).copies.size(); j++)
        {
            if (bookCatalog.at(i).copies.at(j).getID() == idin)
            {
                bookCatalog.at(i).copies.at(j).setExpirationDate(-1);
                bookCatalog.at(i).copies.at(j).setStartDate(-1);
                bookCatalog.at(i).copies.at(j).setReaderName("");
                cout << "Did you like the book?(y/n)" << endl;
                char response;
                cin >> response;
                if (response == 'y')
                {
                    bookCatalog.at(i).favorite();
                    cout << "Thank you for your response!" << endl;
                }
                int borrowbycount = 1;
                int currdate = date(zerotime);

                LLNode *temp = bookCatalog.at(i).getReservers();
                while (temp != NULL)
                {
                    temp->borrowBy = (5 * borrowbycount) + currdate;
                    borrowbycount++;
                    temp = temp->next;
                }
            }
        }
    }
}

void Reader::renewBook(vector<Book> &bookCatalog)
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
        cout << "ID: " << book.getID() << ", "
             << "Title: ";
        for (int i = 0; i < bookCatalog.size(); i++)
        {
            for (int j = 0; j < bookCatalog.at(i).copies.size(); j++)
            {
                if (bookCatalog.at(i).copies.at(j).getID() == book.getID())
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

    if (renewed)
    {
        for (int i = 0; i < bookCatalog.size(); i++)
        {
            for (int j = 0; j < bookCatalog.at(i).copies.size(); j++)
            {
                if (bookCatalog.at(i).copies.at(j).getID() == id)
                {
                    bookCatalog.at(i).copies.at(j).setExpirationDate(bookCatalog.at(i).copies.at(j).getExpirationDate() + this->getMaxLoanTime());
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
    for (int i = 0; i < bookCatalog.size(); i++)
    {
        if (bookCatalog.at(i).getIsbn() == inputISBN)
        {
            exists = true;
            toBeBorrowed = bookCatalog.at(i);
        }
    }

    // Checks if the Book is available (if a BookCopy has a reader name that is empty)
    for (int i = 0; i < toBeBorrowed.copies.size(); i++)
    {
        if (toBeBorrowed.copies.at(i).getReaderName() == "")
        {
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
        int temp;
        // Finds the book to reserve if it is not available
        for (int i = 0; i < bookCatalog.size(); i++)
        {
            if (bookCatalog.at(i).getIsbn() == inputISBN)
            {
                temp = i;
            }
        }

        if (bookCatalog.at(temp).getIsbn() == "-1")
        {
            cerr << "Couldnt find match";
            exit(1);
        }

        // Inserts the reader's name to the Book
        bookCatalog.at(temp).insertReader(this->getUsername());

        // Adds the book to the reader's vector of reserved books
        this->booksReserved.push_back(bookCatalog.at(temp));

        cout << "Your book has been reserved!" << endl;
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
            cout << "Your reservation has been cancelled!" << endl
                 << endl;
            return;
        }
    }

    // Find the book from the book catalog
    int lo = 0, hi = bookCatalog.size() - 1;
    int mid;
    while (hi - lo > 1)
    {
        int mid = (hi + lo) / 2;
        if (bookCatalog[mid].getIsbn() < isbnToCancel)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid;
        }
    }
    if (bookCatalog[lo].getIsbn() == isbnToCancel)
    {
        // Remove the user from the linked list of reservers on the book within the catalog
        bookCatalog.at(lo).deleteReader(this->getUsername());
    }
    else if (bookCatalog[hi].getIsbn() == isbnToCancel)
    {
        // Remove the user from the linked list of reservers on the book within the catalog
        bookCatalog.at(hi).deleteReader(this->getUsername());
    }
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
}

void Reader::printMyInfo(vector<Book> &bookCatalog)
{
    cout << "Username: " << this->getUsername() << endl;
    cout << "Password: " << this->getPassword() << endl;
    cout << "Borrowed Books: " << endl;
    for (int i = 0; i < this->getBooksBorrowed().size(); i++)
    {
        cout << "ID: " << this->getBooksBorrowed().at(i).getID() << ", "
             << "Expiration Date: " << this->getBooksBorrowed().at(i).getExpirationDate() << ", ";

        for (int j = 0; j < bookCatalog.size(); j++)
        {
            for (int k = 0; k < bookCatalog.at(j).copies.size(); k++)
            {
                if (bookCatalog.at(j).copies.at(k).getID() == this->getBooksBorrowed().at(i).getID())
                {
                    cout << "ISBN: " << bookCatalog.at(j).getIsbn() << ", "
                         << "Title: " << bookCatalog.at(j).getTitle() << endl;
                    break;
                }
            }
        }
    }
    cout << "Reserved Books: " << endl;
    for (int i = 0; i < this->booksReserved.size(); i++)
    {
        cout << "ISBN: " << this->booksReserved.at(i).getIsbn() << ", "
             << "Title: " << this->booksReserved.at(i).getTitle() << endl;
    }
    cout << endl;
}

ostream &operator<<(ostream &output, Reader &reader)
{
    output << "Type: " << reader.getType() << endl
           << "Username: " << reader.getUsername() << endl
           << "Password: " << reader.getPassword() << endl
           << "ID's of books currently being borrowed: ";

    for (BookCopy bkcpy : reader.copiesBorrowed)
    {
        cout << bkcpy.getID() << " ";
    }
    cout << endl;

    return output;
}
