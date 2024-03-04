#ifndef ROSTER_CLASS_H
#define ROSTER_CLASS_H

#include "studentClass.h"
#include <fstream>

class Roster : public Student
{
protected:
    // creating an array of students of size 100
    Student *students;
    int studentArraySize;

public:
    // constructor
    int currentSize;

    Roster(ifstream &file);
    Roster() {}

    ~Roster(){ delete [] students; }

    // add students to the roster 
    void addStudent(Student &s);

    // update the student based on ID; can update any aspect of the student
    // if the student's ID is updated, it will change position based on ID
    void updateStudent();

    // drop the student based on ID selection
    void dropStudent();

    // wrapper function to call insert node and heapify -> called within the constructor, drop, and update function
    void buildHeap();

    // create a heap that sorts students based on ID
    void heapify(int n);

    // insert into the head - called within the add student function
    void insertNode(int n);

    // heap sort function - sorts according to max heap -> ascending order
    void heapSort();

    // operator to print
    friend ostream &operator<<(ostream &os, Roster &r);

    // public member function to access student array
    Student *getStudents() { return students; }
};

// swapping function used to swap students in heap creation
void swap(Student *a, Student *b)
{
    Student temp = *a;
    *a = *b;
    *b = temp;
}

#endif