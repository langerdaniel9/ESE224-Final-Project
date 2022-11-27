#pragma once

#include <iostream>
#include <string>

using namespace std;

class Book
{
private:
    // isbn, title, author, category, id, readers name, start date, return date,
    string isbn;
    string title;
    string author;
    string category;
    // TODO - copy list
    // TODO - reserved reader linked list
    int timesFavorited;

public:
    Book();
    Book(int id, string isbn, string title, string author, string category);

    // ********** ACCESSORS **********
    string getIsbn();
    string getTitle();
    string getAuthor();
    string getCategory();
    // copy list
    // reserved reader linked list
    int getTimesFavorited();

    // ********** MUTATORS **********
    void setIsbn(string isbn);
    void setTitle(string title);
    void setAuthor(string author);
    void setCategory(string category);
    void setId(int id);
    void setReaderName(string readerName);
    void setStartDate(int startDate);
    void setExpDate(int expDate);

    // ********** OPERATION OVERLOADING **********
    friend ostream &operator<<(ostream &output, Book &book);
    friend istream &operator>>(istream &input, Book &book);
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished
Book::Book()
{
    isbn = "";
    title = "";
    author = "";
    category = "";
}

Book::Book(int id, string isbn, string title, string author, string category)
{
    this->isbn = isbn;
    this->title = title;
    this->author = author;
    this->category = category;
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
    string studentname = "NONE";
    // If book doesnt exist
    if (book.getTitle() == "")
    {
        return output;
    }
    // FIXME - change book.getReaderName to (current node of the linked list).name
    if ((book.getReaderName()) != "")
    {
        studentname = book.getReaderName();
    }
    output << "ISBN:\t" << book.getIsbn() << endl
           << "Title:\t" << book.getTitle() << endl
           << "Author:\t" << book.getAuthor() << endl
           << "Category:\t" << book.getCategory() << endl
           << "Reader:\t" << studentname << endl
           << endl;

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