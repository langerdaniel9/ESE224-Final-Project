#pragma once

#include "User.h"
#include "Book.h"
#include "DateFunction.h"
#include "BST.h"
#include "BookCopy.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Reader : public User
{
protected:
    int maxCopies;
    int maxLoanTime;
    vector<BookCopy>* copiesBorrowed;
    vector<BookCopy>* BooksReserved;
    int penalties;
    string type();

public:
    // Getters //
    int getMaxCopies();
    int getMaxLoanTime();
    vector<Book>* getBooksBorrowed();
    // Operator Overloading //
    friend ostream &operator<<(ostream &output, Book &book);
    friend istream &operator>>(istream &input, Book &book);
    // Main functions //
    void searchBook(BST<Book>* &bookCatalog);
    void borrowBook(BST<Book>* &bookCatalog, time_t &zeroTime);
    void returnBook(BST<Book>* &bookCatalog);
    void renewBook(BST<Book>* &bookCatalog);
    void cancelBook(BST<Book>* &bookCatalog);
    void feelingLucky(BST<Book>* &bookCatalog);
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

int Reader::getMaxCopies()
{
    return this->maxCopies;
}

int Reader::getMaxLoanTime()
{
    return maxLoanTime;
}

BST<Book>* Reader::getBooksBorrowed()
{
    return this->copiesBorrowed;
}

int partition(vector<Book>* lib, int low, int high)
{
    // partition starting from first element;
    // then comparing each element by the last element in the array

    int i = low - 1; // i => index of first array (array lower than "high" value)

    Book temp;
    for (int j = low; j < high; j++)
    { // j => index of second array (array greater than "high" value)
        if (lib.at(j).getId() <= lib.at(high).getId())
        {
            i++;

            swap(lib.at(i), lib.at(j));
        }
    }

    // Swapping the "high" value to where it needs to be
    temp = lib.at(high);
    lib.at(high) = lib.at(i + 1);
    lib.at(i + 1) = temp;

    // returns the index of where the "high" value is
    return i + 1;
}

void quickSort(vector<Book>* lib, int low, int high)
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


BookCopy IDInOrderTraversal(BST<Book> *inputBST, int inputID)
{ // not working either???
    if (inputBST == NULL)
    {
        return;
    }

    IDInOrderTraversal(inputBST->left, inputID); // visit left child
//    inputBST->val->binarySearch(inputID);
//    forLoopforBook(inputBST, inputID);            // visit current child
    for (int i = 0; i < inputBST->val.copiesVector.size(); i++) {
        if (inputBST->val.copiesVector.at(i).ID == inputID) {
            return inputBST->val.copiesVector.at(i);
        }
    }

    IDInOrderTraversal(inputBST->right, inputID); // visit right child
}

//BookCopy forLoopforBook(BST<Book>* inputBST, int inputID) {
//    for (int i = 0; i < inputBST->val.copiesVector.size(); i++) {
//        if (inputBST->val.copiesVector.at(i).ID == inputID) {
//            return inputBST->val.copiesVector.at(i);
//        }
//    }
//
//    return NULL;
//}

void QSInOrderTraversal(BST<Book> *inputBST, string inputStr, vector<Book> matches)
{ // not working either???
    if (inputBST == NULL)
    {
        return;
    }

    QSInOrderTraversal(inputBST->left, inputStr, matches); // visit left child
                                                           //    inputBST->val->binarySearch(inputID);
    matches.push_back(inputBST->val);
    QSInOrderTraversal(inputBST->right, inputStr, matches); // visit right child
}

string copiesInOrderTraversal(BST<copystruct>* inputBST, int inputID) {
    if (inputBST == NULL)
    {
        return;
    }

    copiesInOrderTraversal(inputBST->left, inputID); // visit left child
//    forLoopforBook(inputBST, inputID);            // visit current child
//    checkForIDfromCopyList(inputBST, inputID);
    if (inputBST->val.ID == inputID) {
        return inputBST->val.ISBN;
    }

    copiesInOrderTraversal(inputBST->right, inputID); // visit right child
}

//string checkForIDfromCopyList(BST<copystruct>* inputBST, int inputID) {
//    if (inputBST->val.ID == inputID) {
//        return inputBST->val.ISBN;
//    }
//}

void Reader::searchBook(BST<Book> *bookCatalog)
{
    // FIXME - (Daniel)
    int searchChoice;
    cout << "What category do you want to search by:" << endl;
    cout << "(1) - ISBN" << endl;
    cout << "(2) - Title" << endl;
    cout << "(3) - Category" << endl;
    cout << "(4) - ID" << endl;
    cin >> searchChoice;

    Book* searchMatches = NULL;

    switch (searchChoice)
    {
    case 1:                                                         // DONE...maybe
    {
        string inputISBN;
        cout << "What's your book's ISBN value?: ";
        cin >> inputISBN;

//        BST<Book> *bookCatalog;
        bookCatalog->binarySearch(inputISBN);

        break;
    }
    case 2:
    {
        string inputTitle;
        cout << "What's your book's title?: ";
        cin >> inputTitle;

        inOrderSearch(bookCatalog, inputTitle, true);

//        QSInOrderTraversal(bookCatalog, inputTitle, searchMatches);
//        quickSort(searchMatches, 0, searchMatches.size() - 1);
        break;
    }
    case 3:
    {
        string inputCategory;
        cout << "What's your book's category?: ";
        cin >> inputCategory;

        inOrderSearch(bookCatalog, inputCategory, false);

//        QSInOrderTraversal(bookCatalog, inputCategory, searchMatches);
//        quickSort(searchMatches, 0, searchMatches.size() - 1);
        break;
    }
    case 4:
    {
        int inputID;
        cout << "What's your book's ID?: ";
        cin >> inputID;

        // NEEDS TO BE FIXED?!?!?!?!
        string correspondingISBN = copiesInOrderTraversal(copyList, inputID);                      // gets the corresponding ISBN
        bookCatalog->binarySearch(correspondingISBN);

//        IDInOrderTraversal(bookCatalog, inputID);

        break;
    }
    default:
    {
        cout << "That's not a valid option! Try again!" << endl;
        break;
    }
    }

    // Is this even needed anymore?
    // Separate searchMatches into two separate vectors, one for available books and one for unavailable
    vector<Book> availableMatches;
    vector<Book> unavailableMatches;
    availableMatches.clear();
    unavailableMatches.clear();

    for (int i = 0; i < searchMatches.size(); i++)
    {
        if (searchMatches.at(i).getReaderName() == "")
        {
            // If nobody has checked out this book -> it is available
            availableMatches.push_back(searchMatches.at(i));
        }
        else
        {
            unavailableMatches.push_back(searchMatches.at(i));
        }
    }

    // Sort availableMatches
    // sorting by title
    if (availableMatches.size() >= 2)
    {
        for (int i = 0; i < availableMatches.size() - 1; i++)
        {
            for (int j = 0; j < (availableMatches.size() - i - 1); j++)
            {
                int titleCompare = availableMatches.at(j).getTitle().compare(availableMatches.at(j + 1).getTitle());
                if (titleCompare > 0)
                {
                    swap(availableMatches.at(j), availableMatches.at(j + 1));
                }
            }
        }

        // sorting by ID
        quickSort(availableMatches, 0, availableMatches.size() - 1);
    }

    // Sort unavailableMatches
    for (int i = 0; i < unavailableMatches.size(); i++)
    {
        for (int j = 0; j < unavailableMatches.size() - i; j++)
        {
            if (unavailableMatches.at(i).getExpDate() > unavailableMatches.at(j).getExpDate())
            {
                swap(unavailableMatches.at(i), unavailableMatches.at(j));
            }
        }
    }

    // Combine the two back together into one finished, sorted vector
    searchMatches.clear();
    for (int i = 0; i < availableMatches.size(); i++)
    {
        searchMatches.push_back(availableMatches.at(i));
    }
    for (int i = 0; i < unavailableMatches.size(); i++)
    {
        searchMatches.push_back(unavailableMatches.at(i));
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

void Reader::borrowBook(BST<Book>* &bookCatalog, time_t &zeroTime)
{
    // FIXME - (Daniel)
    // Check if there are overdue books
    int currentTime = date(zeroTime);
    BST<Book>* expiredBooks;
    BST<Book>* temp = bookCatalog;
    bool expired = false;

    for (int i = 0; i < this->getBooksBorrowed().size(); i++)
    {
        if (this->getBooksBorrowed().at(i).getExpDate() < currentTime)
        {
            expired = true;
            expiredBooks.push_back(this->getBooksBorrowed().at(i));
        }
    }
    if (expired)
    {
        cout << "You have books that are already past due, return those before borrowing more. Your expired books are:" << endl;
        for (Book book : expiredBooks)
        {
            cout << book;
        }
        return;
    }

    int inputID;
    cout << "What is the ID of the book you wish to borrow: ";
    cin >> inputID;

    // Check if that ID exists in bookCatalog and that there are available copies
    bool exists = false;
    bool available = false;
    BookCopy toBeBorrowed;

    toBeBorrowed = IDInOrderTraversal(bookCatalog, inputID);
    if (toBeBorrowed) {
        exists = true;
        if (toBeBorrowed.getReaderName() == "") {
            available = true;
        }
    }
    /*for (int i = 0; i < bookCatalog.size(); i++) {
        if (bookCatalog.at(i).getId() == inputID)
        {
            exists = true;
            // If book exists in bookCatalog, check if it is already being borrowed by someone else
            if (bookCatalog.at(i).getReaderName() == "")
            {
                available = true;
                toBeBorrowed = bookCatalog.at(i);
            }
        }
    }*/
    if (!exists)
    {
        cout << "That ID does not exist in the library, double check the ID and try again" << endl;
        return;
    }
    if (!available)
    {
        cout << "There are no more copies of this book left, try again after some time has passed" << endl;
        return;
    }

    // Next check if the user is over their maxCopies limit
    if (this->getBooksBorrowed().size() > this->getMaxCopies())
    {
        cout << "You cannot borrow any more books, since you are already at your limit" << endl;
        return;
    }

    // If all of the conditions are met, add the book to copiesBorrowed and change the attributes of the book
    toBeBorrowed.setStartDate(currentTime);
    toBeBorrowed.setExpirationDate(currentTime + this->getMaxLoanTime());
    toBeBorrowed.setReaderName(this->getUserName());
    this->copiesBorrowed.push_back(toBeBorrowed);

    for (int i = 0; i < bookCatalog.size(); i++)
    {
        if (bookCatalog.at(i).getId() == toBeBorrowed.getId())
        {
            int currentTime = date(zeroTime);
            bookCatalog.at(i).setStartDate(currentTime);
            bookCatalog.at(i).setExpirationDate(currentTime + this->getMaxLoanTime());
            bookCatalog.at(i).setReaderName(this->getUserName());
        }
    }
}

void Reader::returnBook(vector<Book> &bookCatalog)
{
    // FIXME - (Daniel)
    if (this->getBooksBorrowed().size() == 0)
    {
        cout << "You are not currently borrowing any books." << endl
             << endl;
        return;
    }

    cout << "Here are all the books you are currently borrowing:" << endl;

    for (Book book : this->getBooksBorrowed())
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
        if (this->copiesBorrowed.at(i).getId() == id)
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
    for (int i = 0; i < bookCatalog.size(); i++)
    {
        if (bookCatalog.at(i).getId() == id)
        {
            bookCatalog.at(i).setStartDate(-1);
            bookCatalog.at(i).setExpDate(-1);
            bookCatalog.at(i).setReaderName("");
        }
    }
    cout << endl;
}

void Reader::renewBook(vector<Book> &bookCatalog)
{
    // FIXME - (Daniel)
    if (this->getBooksBorrowed().size() == 0)
    {
        cout << "You are not currently borrowing any books." << endl
             << endl;
        return;
    }

    cout << "Here are all the books you are currently borrowing:" << endl
         << endl;

    for (Book book : this->getBooksBorrowed())
    {
        cout << book;
    }

    cout << "What is the ID of the book you would like to renew?" << endl;
    int id;
    cin >> id;

    bool renewed = false;
    for (int i = 0; i < this->getBooksBorrowed().size(); i++)
    {
        if (this->getBooksBorrowed().at(i).getId() == id)
        {
            renewed = true;
            cout << "Renewing book" << endl
                 << endl;

            copiesBorrowed.at(i).setExpDate(copiesBorrowed.at(i).getExpDate() + this->getMaxLoanTime());
        }
    }

    if (renewed)
    {
        for (int i = 0; i < bookCatalog.size(); i++)
        {
            if (bookCatalog.at(i).getId() == id)
            {
                bookCatalog.at(i).setExpDate(bookCatalog.at(i).getExpDate() + this->getMaxLoanTime());
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

void Reader::cancelBook(vector<Book> &bookCatalog)
{
    // TODO - (Kenny)
}

void Reader::feelingLucky(vector<Book> &bookCatalog)
{
    // TODO - maybe if we have time (Daniel)
}

string Reader::type()
{
    return "Reader";
}
