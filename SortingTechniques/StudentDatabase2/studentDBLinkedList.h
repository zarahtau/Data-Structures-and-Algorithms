#ifndef STUDENTDB_LINKEDLIST_H
#define STUDENTDB_LINKEDLIST_H

#include "studentClass.h"

class Node
{
public:
    Node *next;
    Student data;

    Node() : next(nullptr) {}

    ~Node() { delete next; }
};

class StudentDB
{
protected:
    Node *head;
    Node *tail;
    int length;

public:
    // constructors
    StudentDB(ifstream &file); // accepts file input
    StudentDB();               // default constructor

    // destructor
    ~StudentDB();

    // takes student object and adds to the end of the linked list
    void appendStudent(Student s);

    // takes ID input and updates students info from the student database
    void updateStudent();

    // takes ID input and deletes student from the student database
    void dropStudent();

    // wrapper function - merge sort sorts database based on ID
    void mergeSort();
    // recursive function to continuously divided array into subarrays
    Node *mergeSortRecursion(Node *headRef);
    // compare two linked list elements and sort them merging the two lists
    Node *mergeSortedList(Node *a, Node *b);

    friend ostream &operator<<(ostream &os, const StudentDB &db);
};

#endif