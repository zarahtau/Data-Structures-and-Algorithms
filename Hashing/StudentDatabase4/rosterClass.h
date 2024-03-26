#ifndef ROSTER_CLASS_H
#define ROSTER_CLASS_H

#include "studentClass.h"
#include <fstream>

class Node
{
    public:
    Student data;
    Node *next;

};

class Roster : public Student
{
protected: 
    // hash table of linked lists containing students
    Node **HashTable;
    int size;

public:
    // constructor to add students to the hash
    Roster(ifstream &file);
    // default constructor to 
    Roster ();

    // destructor
    ~Roster();

    // add students to the roster
    void addStudent(Student &s);
    // drop the student based on ID selection
    void dropStudent();
    // update the student based on ID; can update any part of student info
    void updateStudent();

    // return the hash function index
    int hash(string ID);

    // search for the student in the hash table and return the index of the bucket
    int search(string ID);

    // display the roster
    friend ostream& operator<<(ostream &os, Roster &r);

    // will be used for drop and update confirmation where type indicates whether we will delete or update
    bool confirmation(int type, Student &s);
};

#endif