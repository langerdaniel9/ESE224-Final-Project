#pragma once

#include "User.h"
#include "Student.h"
#include "Teacher.h"
#include "Book.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Librarian : public User
{
public:
    // ********** CONSTRUCTORS **********
    Librarian();
    Librarian(string initUsername, string initPassword);

    // ********** FUNCTIONS **********
    void printMyInfo();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

Librarian::Librarian()
{
    type = "Librarian";
}

Librarian::Librarian(string initUsername, string initPassword)
{
    username = initUsername;
    password = initPassword;
    type = "Librarian";
}

void Librarian::printMyInfo()
{
    // TODO print librarian info: username, password
}

// Casting //
Librarian *userToLibrarian(User *toCast)
{
    return dynamic_cast<Librarian *>(toCast);
}