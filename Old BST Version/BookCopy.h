#pragma once

#include <iostream>
#include <string>

using namespace std;

class BookCopy
{
private:
    int ID;
    string readerName;
    string reserverName;
    int reserveDate;
    int startDate;
    int expirationDate;

public:
    // ********** CONSTRUCTORS **********
    BookCopy();
    BookCopy(int newId);

    // ********** ACCESSORS **********
    int getID();
    string getReaderName();
    string getReserverName();
    int getReserveDate();
    int getStartDate();
    int getExpirationDate();

    // ********** MUTATORS **********
    void setID(int id);
    void setReaderName(string newReadName);
    void setReserverName(string newReserveName);
    void setReserveDate(int newReserveD);
    void setStartDate(int newStartD);
    void setExpirationDate(int newExpirationD);

    // ********** OPERATION OVERLOADING **********
    friend ostream &operator<<(ostream &output, BookCopy &bc);
    friend istream &operator>>(istream &input, BookCopy &bc);
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

BookCopy::BookCopy()
{
    this->ID = -1;
}

BookCopy::BookCopy(int newId)
{
    this->ID = newId;
}

// ******************** ACCESSORS ********************

int BookCopy::getID()
{
    return ID;
};

string BookCopy::getReaderName()
{
    return readerName;
};

string BookCopy::getReserverName()
{
    return reserverName;
};

int BookCopy::getReserveDate()
{
    return reserveDate;
};

int BookCopy::getStartDate()
{
    return startDate;
};

int BookCopy::getExpirationDate()
{
    return expirationDate;
};

// ******************** MUTATORS ********************

void BookCopy::setID(int newID)
{
    this->ID = ID;
}

void BookCopy::setReaderName(string newReadName)
{
    this->readerName = newReadName;
};

void BookCopy::setReserverName(string newReserveName)
{
    this->reserverName = newReserveName;
};

void BookCopy::setReserveDate(int newReserveD)
{
    this->reserveDate = newReserveD;
};

void BookCopy::setStartDate(int newStartD)
{
    this->startDate = newStartD;
};

void BookCopy::setExpirationDate(int newExpirationD)
{
    this->expirationDate = newExpirationD;
};

// ******************** OPERATION OVERLOADING ********************

ostream &operator<<(ostream &output, BookCopy &book_copy)
{
    // If book doesnt exist
    if (book_copy.getID() == -1)
    {
        return output;
    }

    output << "ID:\t" << book_copy.getID() << endl
           << "Reader Name:\t" << book_copy.getReaderName() << endl
           << "Reserver Name:\t" << book_copy.getReserverName() << endl
           << "Reservation Date:\t" << book_copy.getReserveDate() << endl
           << "Start Date:\t" << book_copy.getStartDate() << endl
           << "Expiration Date:\t" << book_copy.getExpirationDate() << endl
           << endl;

    return output;
}

istream &operator>>(istream &input, BookCopy &book_copy)
{
    int ID, reserveDate, startDate, expirationDate;
    string readerName, reserverName;

    input >> ID >> readerName >> reserverName >> reserveDate >> startDate >> expirationDate;

    book_copy.setID(ID);
    book_copy.setReaderName(readerName);
    book_copy.setReserverName(reserverName);
    book_copy.setReserveDate(reserveDate);
    book_copy.setStartDate(startDate);
    book_copy.setExpirationDate(expirationDate);

    return input;
}

bool operator<(BookCopy &bc1, BookCopy &bc2)
{
    return bc1.getID() < bc2.getID();
}

bool operator>(BookCopy &bc1, BookCopy &bc2)
{
    return bc1.getID() > bc2.getID();
}