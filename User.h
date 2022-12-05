#pragma once

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
    // TODO - operator overloading
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

bool operator<(User &u1, User &u2)
{
    int val = u1.getUserName().compare(u2.getUserName());
    return (val == -1) ? true : false;
}

bool operator>(User &u1, User &u2)
{
    int val = u1.getUserName().compare(u2.getUserName());
    return (val == 1) ? true : false;
}