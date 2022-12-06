#pragma once

#include "Structs.h"
#include "BookCopy.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book
{
private:
    string isbn;
    string title;
    string author;
    string category;
    LLNode *rrHead;
    int timesFavorited;

public:
    vector<BookCopy> copiesVector;

    // ********** CONSTRUCTORS **********
    Book();
    Book(string isbn, string title, string author, string category);

    // ********** ACCESSORS **********
    string getIsbn();
    string getTitle();
    string getAuthor();
    string getCategory();
    vector<BookCopy> getCopiesVector();
    LLNode *getReservers();
    int getTimesFavorited();

    // ********** MUTATORS **********
    void setIsbn(string isbn);
    void setTitle(string title);
    void setAuthor(string author);
    void setCategory(string category);

    // ********** FUNCTIONS **********
    void favorite();

    // ********** OPERATION OVERLOADING **********
    friend ostream &operator<<(ostream &output, Book &book);
    friend istream &operator>>(istream &input, Book &book);

    // ********** LINKED LIST **********
    void insertReader(string newReaderUsername);
    void deleteReader(string readerName);
    void deleteFirst();
};

// Leave functions in the .h file for now, will move them to their respective .cpp files when project is finished

// ******************** CONSTRUCTORS ********************

Book::Book()
{
    this->rrHead = new LLNode("-1");
    this->getCopiesVector().clear();
    this->timesFavorited = 0;
}

Book::Book(string isbn, string title, string author, string category)
{
    this->isbn = isbn;
    this->title = title;
    this->author = author;
    this->category = category;
    this->rrHead = new LLNode("-1");
    this->getCopiesVector().clear();
    this->timesFavorited = 0;
}

// ******************** ACCESSORS ********************

string Book::getIsbn()
{
    return isbn;
}

string Book::getTitle()
{
    return title;
}

string Book::getAuthor()
{
    return author;
}

string Book::getCategory()
{
    return category;
}

vector<BookCopy> Book::getCopiesVector()
{
    return copiesVector;
}

LLNode *Book::getReservers()
{
    return rrHead;
}

int Book::getTimesFavorited()
{
    return timesFavorited;
}

// ******************** MUTATORS ********************

void Book::setIsbn(string isbn)
{
    this->isbn = isbn;
}

void Book::setTitle(string title)
{
    this->title = title;
}

void Book::setAuthor(string author)
{
    this->author = author;
}

void Book::setCategory(string category)
{
    this->category = category;
}

// ******************** FUNCTIONS ********************

void Book::favorite()
{
    timesFavorited++;
}

// ******************** OPERATION OVERLOADING ********************

ostream &operator<<(ostream &output, Book &book)
{
    // FIXME
    output << "ISBN:\t" << book.getIsbn() << endl
           << "Title:\t" << book.getTitle() << endl
           << "Author:\t" << book.getAuthor() << endl
           << "Category:\t" << book.getCategory() << endl
           << "Copies:\t" << endl;
    // TODO - Print the id of each copy within copy binary tree

    // Print linked list
    /*output << "Reservers: " << endl;
    LLNode *head = book.getReservers();
    while (head != NULL)
    {
        output << head->data << " ";
        head = head->next;
    }
    output << endl;
    //
    output << "Number of Favorites: " << book.getTimesFavorited() << endl;*/

    return output;
}

istream &operator>>(istream &input, Book &book)
{
    int id, startDate, expDate;
    string isbn, title, author, category, readerName;
    input >> isbn >> title >> author >> category;
    book.setIsbn(isbn);
    book.setTitle(title);
    book.setAuthor(author);
    book.setCategory(category);

    return input;
}

bool operator<(Book &b1, Book &b2)
{
    int val = b1.getIsbn().compare(b2.getIsbn());
    return (val == -1) ? true : false;
}

bool operator>(Book &b1, Book &b2)
{
    int val = b1.getIsbn().compare(b2.getIsbn());
    return (val == 1) ? true : false;
}

// ******************** LINKED LIST ********************

void Book::insertReader(string newReaderUsername)
{
    LLNode *newNode = new LLNode(newReaderUsername);
    LLNode *head = rrHead;

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    while (head->next != nullptr)
    {
        head = head->next;
    }
    head->next = newNode;
    return;
}

void Book::deleteFirst()
{
    LLNode *temp = rrHead;
    rrHead = rrHead->next;
    delete (temp);
}

void Book::deleteReader(string readerName)
{
    LLNode *head = rrHead;
    LLNode *prev = nullptr;

    if (head != nullptr && head->data == readerName)
    {
        rrHead = head->next;
        delete head;
        return;
    }

    while (head != nullptr && head->data != readerName)
    {
        prev = head;
        head = head->next;
    }

    if (head == nullptr)
    {
        return;
    }

    prev->next = head->next;
    delete head;
}

// ******************** OTHER BOOK FUNCTIONS ********************

void returnBookCopyGivenID(TreeNode<Book> *node, int inputID, BookCopy &bc)
{
    if (node == nullptr)
    {
        return;
    }

    // visit left child
    returnBookCopyGivenID(node->left, inputID, bc);

    // What to do at current node
    for (int i = 0; i < node->val.copiesVector.size(); i++)
    {
        if (node->val.copiesVector.at(i).getID() == inputID)
        {
            bc = node->val.copiesVector.at(i);
        }
    }
    // visit right child
    returnBookCopyGivenID(node->right, inputID, bc);
}

void returnBookGivenID(TreeNode<Book> *node, int inputID, Book &result)
{
    if (node == nullptr)
    {
        return;
    }

    // visit left child
    return returnBookGivenID(node->left, inputID, result);

    // What to do at current node
    // Check through bookCopies vector for an id that matches inputID
    for (int i = 0; i < node->val.copiesVector.size(); i++)
    {
        if (node->val.copiesVector.at(i).getID() == inputID)
        {
            result = node->val;
        }
    }

    // visit right child
    return returnBookGivenID(node->right, inputID, result);
}

void checkOutBookInCatalog(TreeNode<Book> *inputBST, int bookID, int startLoanTime, int endLoanTime, string readerUsername)
{
    if (inputBST == nullptr)
    {
        return;
    }

    // visit left child
    checkOutBookInCatalog(inputBST->left, bookID, startLoanTime, endLoanTime, readerUsername);

    /**************************/
    for (int i = 0; i < inputBST->val.copiesVector.size(); i++)
    {
        if (inputBST->val.copiesVector.at(i).getID() == bookID)
        {
            inputBST->val.copiesVector.at(i).setStartDate(startLoanTime);
            inputBST->val.copiesVector.at(i).setExpirationDate(endLoanTime);
            inputBST->val.copiesVector.at(i).setReaderName(readerUsername);
            return;
        }
    }
    /**************************/

    // visit right child
    checkOutBookInCatalog(inputBST->right, bookID, startLoanTime, endLoanTime, readerUsername);
}

void renewBookInCatalog(TreeNode<Book> *inputBST, int inputID, int maxLoanTime)
{
    if (inputBST == NULL)
    {
        return;
    }

    // visit left child
    renewBookInCatalog(inputBST->left, inputID, maxLoanTime);

    /**************************/
    for (int i = 0; i < inputBST->val.copiesVector.size(); i++)
    {
        if (inputBST->val.copiesVector.at(i).getID() == inputID)
        {
            inputBST->val.copiesVector.at(i).setExpirationDate(inputBST->val.copiesVector.at(i).getExpirationDate() + maxLoanTime);
            return;
        }
    }
    /**************************/

    // visit right child
    renewBookInCatalog(inputBST->right, inputID, maxLoanTime); // visit right child
}