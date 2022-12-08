#pragma once

#include "Reader.h"

#include <string>
#include <vector>

using namespace std;

class Student : public Reader
{
public:
    Student();
    Student(string initUserName, string initPassword);
    string type();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

Student::Student()
{
    maxCopies = 5;
    maxLoanTime = 30;
}

Student::Student(string initUserName, string initPassword)
{
    userName = initUserName;
    password = initPassword;
    maxCopies = 5;
    maxLoanTime = 30;
}

string Student::type()
{
    return "Student";
}

// Casting //
Student *userToStudent(User *toCast)
{
    return dynamic_cast<Student *>(toCast);
}