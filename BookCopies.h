#pragma once

#include <iostream>
#include <string>
#include "Book.h"


using namespace std;

class BookCopy
{
private:
    // ID, pointer to book it's a copy of, reader's name, reserver's name, reserve data, start date of borrowing periods, expiration date
    int ID;
    Book* parent;
    string readerName;
    string reserverName;
    int reserveDate;
    int startDate;
    int expirationDate;

public:
    BookCopy();
    BookCopy(int newId, Book* newP, string newReadName, string newReserveName, int newReserveD, int newStartD, int newExpirationD);

    // ********** ACCESSORS **********
    int getID();
    Book* getBookPointer();
    string getReaderName();
    string getReserverName();
    int getReserveDate();
    int getStartDate();
    int getExpirationDate();

    // ********** MUTATORS **********
    void setID(int id);
    void setBookPointer(Book* newP);
    void setReaderName(string newReadName);
    void setReserverName(string newReserveName);
    void setReserveDate(int newReserveD);
    void setStartDate(int newStartD);
    void setExpirationDate(int newExpirationD);

    // ********** OPERATION OVERLOADING **********
    friend ostream& operator<<(ostream& output, BookCopy& bc);
    friend istream& operator>>(istream& input, BookCopy& bc);
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

BookCopy::BookCopy(int newId, Book* newP, string newReadName, string newReserveName, int newReserveD, int newStartD, int newExpirationD)
{
    this->ID = newId;
    this->parent = newP;
    this->readerName = newReadName;
    this->reserverName = newReserveName;
    this->reserveDate = newReserveD;
    this->startDate = newStartD;
    this->expirationDate = newExpirationD;
}

// ******************** ACCESSORS ********************

int BookCopy::getID() {
    return ID;
};


Book* BookCopy::getBookPointer() {
    return parent;
};

string BookCopy::getReaderName() {
    return readerName;
};

string BookCopy::getReserverName() {
    return reserverName;
};

int BookCopy::getReserveDate() {
    return reserveDate;
};

int BookCopy::getStartDate() {
    return startDate;
};

int BookCopy::getExpirationDate() {
    return expirationDate;
};

// ******************** MUTATORS ********************

void BookCopy::setID(int newID)
{
    this->ID = ID;
}

void BookCopy::setBookPointer(Book* newP) {
    this->parent = newP;
};

void BookCopy::setReaderName(string newReadName) {
    this->readerName = newReadName;
};

void BookCopy::setReserverName(string newReserveName) {
    this->reserverName = newReserveName;
};

void BookCopy::setReserveDate(int newReserveD) {
    this->reserveDate = newReserveD;
};

void BookCopy::setStartDate(int newStartD) {
    this->startDate = newStartD;
};

void BookCopy::setExpirationDate(int newExpirationD) {
    this->expirationDate = newExpirationD;
};

// ******************** OPERATION OVERLOADING ********************

ostream& operator<<(ostream& output, BookCopy& book_copy)
{
    // If book doesnt exist
    if (book_copy.getID() == NULL)                                                          // Needs to be fixed??
    {
        return output;
    }
    // FIXME - change book.getReaderName to (current node of the linked list).name          // Needs to be fixed??
    //if ((book.getReaderName()) != "")
    //{
    //    studentname = book.getReaderName();
    //}

    output << book_copy.getBookPointer() << endl
        << "ID:\t" << book_copy.getID() << endl
        << "Reader Name:\t" << book_copy.getReaderName() << endl
        << "Reserver Name:\t" << book_copy.getReserverName() << endl
        << "Reservation Date:\t" << book_copy.getReserveDate() << endl
        << "Start Date:\t" << book_copy.getStartDate() << endl
        << "Expiration Date:\t" << book_copy.getExpirationDate() << endl
        << endl;

    return output;
}

istream& operator>>(istream& input, BookCopy& book_copy)
{
    int ID, reserveDate, startDate, expirationDate;
    Book* parent;
    string readerName;
    string reserverName;
    //    input >> ID >> parent >> readerName >> reserverName >> reserveDate >> startDate >> expirationDate;
    book_copy.setID(ID);
    book_copy.setBookPointer(parent);
    book_copy.setReaderName(readerName);
    book_copy.setReserverName(reserverName);
    book_copy.setReserveDate(reserveDate);
    book_copy.setStartDate(startDate);
    book_copy.setExpirationDate(expirationDate);


    return input;
}