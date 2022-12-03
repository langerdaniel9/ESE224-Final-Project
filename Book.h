#pragma once

#include "Reader.h"
#include "BST.h"
#include "BookCopy.h"

#include <iostream>
#include <string>

using namespace std;

struct LLNode
{
    Reader data;
    LLNode *next;
    LLNode() : next(nullptr) {}
    LLNode(Reader x) : data(x), next(nullptr) {}
    LLNode(Reader x, LLNode *next) : data(x), next(next) {}
};

class Book
{
private:
    string isbn;
    string title;
    string author;
    string category;
    BST<BookCopy> copiesList;
    LLNode *rrHead;
    int timesFavorited;

public:
    Book(string isbn, string title, string author, string category);

    // ********** ACCESSORS **********
    string getIsbn();
    string getTitle();
    string getAuthor();
    string getCategory();
    BST<BookCopy> getCopiesList();
    LLNode *getReservers();
    int getTimesFavorited();

    // ********** MUTATORS **********
    void setIsbn(string isbn);
    void setTitle(string title);
    void setAuthor(string author);
    void setCategory(string category);

    // ********** OPERATION OVERLOADING **********
    friend ostream &operator<<(ostream &output, Book &book);
    friend istream &operator>>(istream &input, Book &book);

    // ********** RESERVED READER LINKED LIST **********
    void insertReader(Reader newReader);
    void deleteReader();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

Book::Book(string isbn, string title, string author, string category)
{
    this->isbn = isbn;
    this->title = title;
    this->author = author;
    this->category = category;
    // TODO - initialization for copy list?
    rrHead = new LLNode;
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

BST<BookCopy> Book::getCopiesList()
{
    return copiesList;
}

LLNode *Book::getReservers()
{
    return rrHead;
}

int Book::getTimesFavorited()
{
    return timesFavorited;
}

// ******************** MUTATORS ********************

void Book::setIsbn(string isbn)
{
    this->isbn = isbn;
}

void Book::setTitle(string title)
{
    this->title = title;
}

void Book::setAuthor(string author)
{
    this->author = author;
}

void Book::setCategory(string category)
{
    this->category = category;
}

// ******************** OPERATION OVERLOADING ********************

ostream &operator<<(ostream &output, Book &book)
{
    output << "ISBN:\t" << book.getIsbn() << endl
           << "Title:\t" << book.getTitle() << endl
           << "Author:\t" << book.getAuthor() << endl
           << "Category:\t" << book.getCategory() << endl
           << "Copies:\t" << endl;
    // TODO - Print the id of each copy within copy binaary tree

    // Print linked list
    cout << "Reservers: " << endl;
    LLNode *head = book.getReservers();
    while (head != NULL)
    {
        output << head->data << " ";
        head = head->next;
    }
    output << endl;
    //
    output << "Number of Favorites: " << book.getTimesFavorited() << endl;

    return output;
}

istream &operator>>(istream &input, Book &book)
{
    int id, startDate, expDate;
    string isbn, title, author, category, readerName;
    input >> isbn >> title >> author >> category;
    book.setIsbn(isbn);
    book.setTitle(title);
    book.setAuthor(author);
    book.setCategory(category);

    return input;
}

// ******************** LINKED LIST ********************

void Book::insertReader(Reader newReader)
{
    LLNode *head = rrHead;
    while (head->next != nullptr)
    {
        head = head->next;
    }
    head->next = new LLNode(newReader);
}

void Book::deleteReader()
{
    LLNode *temp = rrHead;
    rrHead = rrHead->next;
    delete (temp);
}