#pragma once

#include "Book.h"

#include <string>
#include <vector>
#include <iostream>

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
    void changePassword();
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

void User::changePassword()
{
    cout << "What do you want the new password to be:" << endl;
    string newPass;
    cin >> newPass;
    password = newPass;
}