#pragma once

#include "Structs.h"
#include "BookCopy.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book
{
private:
    // Properties //
    string isbn;
    string title;
    string author;
    string category;
    LLNode *rrHead;
    int timesFavorited;

public:
    // Properties //
    vector<BookCopy> copies;

    // ********** CONSTRUCTORS **********
    Book();
    Book(string isbn, string title, string author, string category);

    // ********** ACCESSORS **********
    string getIsbn();
    string getTitle();
    string getAuthor();
    string getCategory();
    vector<BookCopy> getCopies();
    LLNode *getReservers();
    int getTimesFavorited();

    // ********** FUNCTIONS **********
    void favorite();

    // ********** OPERATION OVERLOADING **********
    friend ostream &operator<<(ostream &output, Book &book);
    friend istream &operator>>(istream &input, Book &book);

    // ********** LINKED LIST **********
    void insertReader(string newReaderUsername);
    void deleteReader(string readerName);
    void deleteFirst();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

// ******************** CONSTRUCTORS ********************

Book::Book()
{
    this->rrHead = nullptr;
    this->copies.clear();
    this->timesFavorited = 0;
}

Book::Book(string isbn, string title, string author, string category)
{
    this->isbn = isbn;
    this->title = title;
    this->author = author;
    this->category = category;
    this->rrHead = nullptr;
    this->copies.clear();
    this->timesFavorited = 0;
}

// ******************** ACCESSORS ********************

string Book::getIsbn()
{
    return isbn;
}

string Book::getTitle()
{
    return title;
}

string Book::getAuthor()
{
    return author;
}

string Book::getCategory()
{
    return category;
}

vector<BookCopy> Book::getCopies()
{
    return copies;
}

LLNode *Book::getReservers()
{
    return rrHead;
}

int Book::getTimesFavorited()
{
    return timesFavorited;
}

// ******************** FUNCTIONS ********************

void Book::favorite()
{
    timesFavorited++;
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

void sortExpiration(vector<BookCopy> &copyList, int low, int high)
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

// ******************** OPERATION OVERLOADING ********************

ostream &operator<<(ostream &output, Book &book)
{
    output << "ISBN: " << book.getIsbn() << endl
           << "Title: " << book.getTitle() << endl
           << "Author: " << book.getAuthor() << endl
           << "Category: " << book.getCategory() << endl
           << "Number of Favorites: " << book.getTimesFavorited() << endl
           << "Copy IDs: " << endl;
    vector<BookCopy> copies = book.getCopies();
    sortExpiration(copies, 0, copies.size() - 1);
    for (int i = 0; i < copies.size(); i++)
    {
        output << "id: " << copies.at(i).getID() << ", ";
        if (copies.at(i).getExpirationDate() == -1)
        {
            output << "AVAILABLE" << endl;
        }
        else
        {
            output << "UNAVAILABLE " << endl;
        }
    }

    return output;
}

istream &operator>>(istream &input, Book &book)
{
    int id;
    string newIsbn, newTitle, newAuthor, newCategory;
    input >> newIsbn >> newTitle >> newAuthor >> newCategory;
    book.isbn = newIsbn;
    book.title = newTitle;
    book.author = newAuthor;
    book.category = newCategory;

    return input;
}

bool operator<(Book &b1, Book &b2)
{
    int val = b1.getIsbn().compare(b2.getIsbn());
    return (val == -1) ? true : false;
}

bool operator>(Book &b1, Book &b2)
{
    int val = b1.getIsbn().compare(b2.getIsbn());
    return (val == 1) ? true : false;
}

// ******************** LINKED LIST ********************

void Book::insertReader(string newReaderUsername)
{
    LLNode *newNode = new LLNode(newReaderUsername);
    LLNode *head = rrHead;

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    while (head->next != nullptr)
    {
        head = head->next;
    }
    head->next = newNode;
    return;
}

void Book::deleteFirst()
{
    LLNode *temp = rrHead;
    rrHead = rrHead->next;
    delete (temp);
}

void Book::deleteReader(string readerName)
{
    LLNode *head = rrHead;
    LLNode *prev = nullptr;

    if (head != nullptr && head->username == readerName)
    {
        rrHead = head->next;
        delete head;
        return;
    }

    while (head != nullptr && head->username != readerName)
    {
        prev = head;
        head = head->next;
    }

    if (head == nullptr)
    {
        return;
    }

    prev->next = head->next;
    delete head;
}

// ******************** OTHER BOOK FUNCTIONS ********************

int partitionCatalog(vector<Book> &catalog, int low, int high)
{
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        int result = catalog.at(j).getIsbn().compare(catalog.at(high).getIsbn());
        if (result <= 0)
        {
            i++;
            swap(catalog.at(i), catalog.at(j));
        }
    }
    swap(catalog.at(high), catalog.at(i + 1));
    return i + 1;
}

void sortCatalog(vector<Book> &catalog, int low, int high)
{
    if (low < high)
    {
        int pi = partitionCatalog(catalog, low, high);
        sortCatalog(catalog, low, pi - 1);
        sortCatalog(catalog, pi + 1, high);
    }
}

/**
 * @brief Quicksorts the catalog by isbn so that binary search functions can be called on it
 *
 * @param catalog Catalog to sort
 */
void sortCatalog(vector<Book> &catalog)
{
    sortCatalog(catalog, 0, catalog.size() - 1);
}

/**
 * @brief Get the index of a book within the catalog using its isbn and binary search
 *
 * @param catalog vector of books
 * @param isbn isbn of the book to search for
 * @return int index of the book with matching isbn
 */
int getIndexOfBook(vector<Book> &catalog, string isbn)
{
    int lo = 0, hi = catalog.size() - 1;
    int mid;

    while (hi - lo > 1)
    {
        int mid = (hi + lo) / 2;
        if (catalog[mid].getIsbn() < isbn)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid;
        }
    }
    if (catalog[lo].getIsbn() == isbn)
    {
        return lo;
    }
    else if (catalog[hi].getIsbn() == isbn)
    {
        return hi;
    }
    else
    {
        return -1;
    }
}