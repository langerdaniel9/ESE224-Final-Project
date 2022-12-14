#pragma once

#include "Reader.h"

#include <string>
#include <vector>

using namespace std;

class Student : public Reader
{
public:
    Student();
    Student(string initUsername, string initPassword);
    string getType();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

Student::Student()
{
    type = "Student";
    maxCopies = 5;
    maxLoanTime = 30;
}

Student::Student(string initUsername, string initPassword)
{
    username = initUsername;
    password = initPassword;
    type = "Student";
    maxCopies = 5;
    maxLoanTime = 30;
}

string Student::getType()
{
    return "Student";
}

// Casting //
Student *userToStudent(User *toCast)
{
    return dynamic_cast<Student *>(toCast);
}