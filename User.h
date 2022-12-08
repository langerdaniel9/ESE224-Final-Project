#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class User
{
protected:
    string username;
    string password;

    string type;

public:
    // ********** ACCESSORS **********
    string getUsername();
    string getPassword();
    string getType();

    // ********** MUTATORS **********
    void setUsername(string newUsername);
    void setPassword(string newPassword);

    // ********** FUNCTIONS **********
    void changePassword();
    void printLoginInfo();
    virtual void printMyInfo() = 0;

    // ********** OPERATOR OVERLOADING **********
    friend ostream &operator<<(ostream &output, User &user);
    friend istream &operator>>(istream &input, User &user);
};

string User::getUsername()
{
    return username;
}

string User::getPassword()
{
    return password;
}

string User::getType()
{
    return type;
}

void User::setUsername(string newUsername)
{
    username = newUsername;
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

ostream &operator<<(ostream &output, User &user)
{
    output << "Username:\t" << user.getUsername() << endl
           << "Password:\t" << user.getPassword() << endl
           << endl;

    return output;
}

istream &operator>>(istream &input, User &user)
{
    string newUsername, newPassword;
    input >> newUsername, newPassword;
    user.setUsername(newUsername);
    user.setPassword(newPassword);

    return input;
}

bool operator<(User &u1, User &u2)
{
    int val = u1.getUsername().compare(u2.getUsername());
    return (val == -1) ? true : false;
}

bool operator>(User &u1, User &u2)
{
    int val = u1.getUsername().compare(u2.getUsername());
    return (val == 1) ? true : false;
}