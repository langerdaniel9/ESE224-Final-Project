#pragma once

#include "Book.h"

#include <string>
#include <vector>

using namespace std;

class User
{
protected:
    string userName;
    string password;

public:
    // Getters //
    string getUserName();
    string getPassword();
    // Setters //
    void setUserName(string newUserName);
    void setPassword(string newPassword);
    virtual string type() = 0;
};

string User::getUserName()
{
    return userName;
}

string User::getPassword()
{
    return password;
}

void User::setUserName(string newUserName)
{
    userName = newUserName;
}

void User::setPassword(string newPassword)
{
    password = newPassword;
}
