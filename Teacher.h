#pragma once

#include "Reader.h"

#include <string>
#include <vector>

using namespace std;

class Teacher : public Reader
{
public:
    Teacher();
    Teacher(string initUsername, string initPassword);
    string getType();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

Teacher::Teacher()
{
    maxCopies = 10;
    maxLoanTime = 50;
    type = "Teacher";
}

Teacher::Teacher(string initUsername, string initPassword)
{
    username = initUsername;
    password = initPassword;
    type = "Teacher";
    maxCopies = 10;
    maxLoanTime = 50;
}

string Teacher::getType()
{
    return "Teacher";
}

// Casting //
Teacher *userToTeacher(User *toCast)
{
    return dynamic_cast<Teacher *>(toCast);
}