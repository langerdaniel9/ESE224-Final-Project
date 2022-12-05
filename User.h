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
    // ********** ACCESSORS **********
    string getUserName();
    string getPassword();

    // ********** MUTATORS **********
    void setUserName(string newUserName);
    void setPassword(string newPassword);

    // ********** FUNCTIONS **********
    virtual string type() = 0;
    void changePassword();
    virtual void myInformation();

    // ********** OPERATOR OVERLOADING **********
    friend ostream &operator<<(ostream &output, User &user);
    friend istream &operator>>(istream &input, User &user);
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

void User::myInformation() {
    cout << "Username: " << userName << endl;
    cout << "Password: " << password << endl;
}

ostream &operator<<(ostream &output, User &user)
{
    output << "Username:\t" << user.getUserName() << endl
           << "Password:\t" << user.getPassword() << endl
           << endl;

    return output;
}

istream &operator>>(istream &input, User &user)
{
    string newUsername, newPassword;
    input >> newUsername, newPassword;
    user.setUserName(newUsername);
    user.setPassword(newPassword);

    return input;
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