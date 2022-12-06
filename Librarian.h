#pragma once

#include "User.h"
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
    Librarian(string initUserName, string initPassword);

    // ********** FUNCTIONS **********
    void addBook(TreeNode<Book> &bookCatalog, int &copycount);
    void deleteBook(TreeNode<Book> &bookCatalog);
    User *searchUser(TreeNode<User *> usersList);
    void addUsers(TreeNode<User *> usersList);
    void deleteUser(TreeNode<User *> usersList);
    string type();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

Librarian::Librarian()
{
}

Librarian::Librarian(string initUserName, string initPassword)
{
    userName = initUserName;
    password = initPassword;
}



void Librarian::addBook(TreeNode<Book> &bookCatalog,int &copycount)
{
    // TODO - (Ethan)
    string input;
    Book *temp;
    BookCopy tempcopy(copycount++);
    copycount++;
    cout << "Adding new book..." << endl;
    cout << "Please type the isbn of the new book: ";
    cin >> input;
    temp->setIsbn(input);
    cout << "Please type the title of the new book: ";
    cin >> input;
    temp->setTitle(input);
    cout << "Please type the Author of the new book: ";
    temp->setAuthor(input);
    cout << "Please type the catagory of the new book: ";
    cin >> input;
    temp->setCategory(input);
    temp->copiesVector.push_back(tempcopy);
    // bookCatalog.nodeInsert(temp);
    bookCatalog.nodeInsert(temp);
    //
    // may need further modification for copies data struct
    //
}

Book bookremoveInOrderTraversal(TreeNode<Book>* node, int inputID)
{
    if (node == nullptr)
    {
        Book defaultBook(-1);
        return defaultBook;
    }

    // visit left child
    IDInOrderTraversal(node->left, inputID);

    // What to do at current node
    for (int i = 0; i < node->val.copiesVector.size(); i++)
    {
        if (node->val.copiesVector.at(i).getID() == inputID)
        {
            return node->val
        }
    }
    // visit right child
    IDInOrderTraversal(node->right, inputID);
}

BookCopy IDCHECKInOrderTraversal(TreeNode<Book>* node, int inputID)
{
    if (node == nullptr)
    {
        BookCopy defaultBook(-1);
        return defaultBook;
    }

    // visit left child
    IDInOrderTraversal(node->left, inputID);

    // What to do at current node
    for (int i = 0; i < node->val.copiesVector.size(); i++)
    {
        if (node->val.copiesVector.at(i).getID() == inputID)
        {
            return node->val.copiesVector.at(i);
        }
    }
    // visit right child
    IDInOrderTraversal(node->right, inputID);
}

void Librarian::deleteBook(BST<Book> &bookCatalog)
{
    // TODO - (Ethan)
    cout << "Please input the book id to be removed: ";
    int idin;
    cin >> idin;
    if (IDCHECKInOrderTraversal(bookCatalog, idin).getID() == -1) {
        cout << "Id specified has not been found...";
        return;
    }
    else {
        //returnbook, then check if it has any copies
        string toremovetitle = bookremoveInOrderTraversal(bookCatalog, idin).getTitle;
        vector<BookCopy> b1 = bookremoveInOrderTraversal(bookCatalog, idin).getCopiesVector();
        for (int i = 0; i < b1.size()i++) {
            if (b1.at(i).getID() == idin) {
                b1.erase(b1.begin() + 0);//check if work
            }
        }
        if (b1.empty()) {
            //if array is now empty remove book
            bookCatalog.deleteNode(toremovetitle);
        }
        bookremoveInOrderTraversal(bookCatalog, idin).getCopiesVector() = b1;
    }
}

void *Librarian::searchUser(BST<User *> usersList)
{
    usersList.root->val->getUserName();

   

    if ((root->val.getUserName() == user))
    {   

        return root->val;
    }
    else
    {
        false;
    }
    /* Traverse left*/
    searchUser(root, user, pass);
    /* Traverse right */
    SearchUser(root, user, pass);
}

void Librarian::addUsers(BST<User *> usersList)
{
    int typein;
    string userin;
    string passwordin;
    cout << "What kind of user would you like to add? 1 for Student, 2 for Teacher, 3 for Librarian: ";
    cin >> typein;
    if (typein == 0)
    {
        cout << "Please input the desired username of the new user: ";
        cin >> userin;
        cout << "Please input the desired password of the new user: ";
        cin >> passwordin;
        Student temp(userin, passwordin);
        usersList.nodeInsert(temp);
    }
    if (typein == 1)
    {
        cout << "Please input the desired username of the new user: ";
        cin >> userin;
        cout << "Please input the desired password of the new user: ";
        cin >> passwordin;
        Teacher temp(userin, passwordin);
        usersList.nodeInsert(temp);
    }
    if (typein == 2)
    {
        cout << "Please input the desired username of the new user: ";
        cin >> userin;
        cout << "Please input the desired password of the new user: ";
        cin >> passwordin;
        Librarian temp(userin, passwordin);
        usersList.nodeInsert(temp);
    }
}

void Librarian::deleteUser(BST<User *> usersList)
{
    cout << "please enter the username of the user you wish to delete: ";
    string userin;
    cin >> userin;
    usersList.deleteNode(userin);

}




void BST<Book>::search(TreeNode<Book>* root)
{
    //// Make array for result of search
    vector<Book> matches;
    matches.clear();

    //// Search for matches and add them to the array
    searchRecursive(root, searchTerm, matches, TitleOrCategory);

    if (matches.size() == 0)
    {
        cout << endl
            << "There were no books that match that search critera, try again with a different search." << endl
            << endl;
        return;
    }

    // Sort matches by title
    quickSortForMatches(matches, 0, matches.size() - 1);

    //// Compiling the results
    for (int i = 0; i < matches.size(); i++)
    {
        vector<BookCopy> unavailable;
        vector<int> available;
        unavailable.clear();
        available.clear();
        for (int j = 0; j < matches.at(i).copiesVector.size(); j++)
        {
            if (matches.at(i).copiesVector.at(j).getReaderName() == "")
            {
                available.push_back(matches.at(i).copiesVector.at(j).getID());
            }
            else
            {
                unavailable.push_back(matches.at(i).copiesVector.at(j));
            }
        }

        // Print the Book
        cout << matches.at(i);

        // Print available ID's
        cout << "Available ID's: ";

        for (int avail : available)
        {
            cout << avail << " ";
        }
        cout << endl;

        // Sort unavailable BookCopies
        quickSortForUnavailableCopies(unavailable, 0, unavailable.size() - 1);

        // Print unavailable ID's
        for (int j = 0; j < unavailable.size(); j++)
        {
            cout << unavailable.at(j).getID() << " ";
        }
        cout << endl;
    }
}
////////////////////////////////////

string Librarian::type()
{
    return "Librarian";
}

// Casting //
Librarian *userToLibrarian(User *toCast)
{
    return dynamic_cast<Librarian *>(toCast);
}