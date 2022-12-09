#pragma once

#include <iostream>
#include <string>

using namespace std;

class BookCopy
{
private:
    int ID;
    string readerName;
    int startDate;
    int expirationDate;

public:
    // ********** CONSTRUCTORS **********
    BookCopy();
    BookCopy(int newId);

    // ********** ACCESSORS **********
    int getID();
    string getReaderName();
    int getStartDate();
    int getExpirationDate();

    // ********** MUTATORS **********
    void setID(int id);
    void setReaderName(string newReadName);
    void setStartDate(int newStartD);
    void setExpirationDate(int newExpirationDate);

    // ********** OPERATION OVERLOADING **********
    friend ostream &operator<<(ostream &output, BookCopy &bc);
    friend istream &operator>>(istream &input, BookCopy &bc);
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

BookCopy::BookCopy()
{
    this->ID = -1;
    this->readerName = "";
    this->startDate = -1;
    this->expirationDate = -1;
}

BookCopy::BookCopy(int newId)
{
    this->ID = newId;
    this->readerName = "";
    this->startDate = -1;
    this->expirationDate = -1;
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

void BookCopy::setStartDate(int newStartD)
{
    this->startDate = newStartD;
};

void BookCopy::setExpirationDate(int newExpirationDate)
{
    this->expirationDate = newExpirationDate;
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
           << "Start Date:\t" << book_copy.getStartDate() << endl
           << "Expiration Date:\t" << book_copy.getExpirationDate() << endl
           << endl;

    return output;
}

istream &operator>>(istream &input, BookCopy &book_copy)
{
    int ID, startDate, expirationDate;
    string readerName;

    input >> ID >> readerName >> startDate >> expirationDate;

    book_copy.setID(ID);
    book_copy.setReaderName(readerName);
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