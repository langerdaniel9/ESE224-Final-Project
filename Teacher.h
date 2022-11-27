#pragma once

#include "Reader.h"
#include "Book.h" // Might be unnecessary

#include <string>
#include <vector>

using namespace std;

class Teacher : public Reader
{
public:
    Teacher();
    Teacher(string initUserName, string initPassword);
    string type();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

Teacher::Teacher()
{
    maxCopies = 10;
    maxLoanTime = 50;
}

Teacher::Teacher(string initUserName, string initPassword)
{
    userName = initUserName;
    password = initPassword;
    maxCopies = 10;
    maxLoanTime = 50;
}

string Teacher::type()
{
    return "Teacher";
}
