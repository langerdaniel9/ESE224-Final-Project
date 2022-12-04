#pragma once

#include "BST.h"
#include "BookCopy.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct LLNode
{
    string data;
    LLNode *next;
    LLNode() : next(nullptr) {}
    LLNode(string x) : data(x), next(nullptr) {}
    LLNode(string x, LLNode *next) : data(x), next(next) {}
};

class Book
{
private:
    string isbn;
    string title;
    string author;
    string category;
    LLNode *rrHead;
    int timesFavorited;

public:
    vector<BookCopy> copiesVector;
    Book(string isbn, string title, string author, string category);

    // ********** ACCESSORS **********
    string getIsbn();
    string getTitle();
    string getAuthor();
    string getCategory();
    vector<BookCopy> getCopiesVector();
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
    void insertReader(string newReaderUsername);
    void deleteReader();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

Book::Book(string isbn, string title, string author, string category)
{
    this->isbn = isbn;
    this->title = title;
    this->author = author;
    this->category = category;
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

vector<BookCopy> Book::getCopiesVector()
{
    return copiesVector;
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
    // FIXME
    output << "ISBN:\t" << book.getIsbn() << endl
           << "Title:\t" << book.getTitle() << endl
           << "Author:\t" << book.getAuthor() << endl
           << "Category:\t" << book.getCategory() << endl
           << "Copies:\t" << endl;
    // TODO - Print the id of each copy within copy binary tree

    // Print linked list
    output << "Reservers: " << endl;
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

void Book::insertReader(string newReaderUsername)
{
    LLNode *head = rrHead;
    while (head->next != nullptr)
    {
        head = head->next;
    }
    head->next = new LLNode(newReaderUsername);
}

void Book::deleteFirst()
{
    LLNode *temp = rrHead;
    rrHead = rrHead->next;
    delete (temp);
}

void Book::deleteReader(Reader r1)
{
    LLNode* temp = rrHead;
    while (temp != NULL) {
        if (temp->data == r1) {
            break;
        }
        temp = temp->next;
    }
    while (temp->next != NULL) {
        temp->data = temp->next->data;
        temp = temp->next;
    }
    delete (temp);
}