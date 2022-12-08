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
    void printMyInfo();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

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

void Reader::printMyInfo()
{
    // TODO print reader info: username, password, books borrowed
}

// Casting //
Reader *userToReader(User *toCast)
{
    return dynamic_cast<Reader *>(toCast);
}
