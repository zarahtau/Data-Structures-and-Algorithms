#ifndef ROSTER_CLASS_H
#define ROSTER_CLASS_H

#include "studentClass.h"
#include <fstream>

class Roster : public Student
{
protected:
    // creating an array of students of size 100
    Student students[100];
    int studentArraySize;

public:
    // constructor
    int currentSize;

    Roster(ifstream &file);
    Roster() {}

    // add students to the roster
    void addStudent(Student &s);

    // drop the student based on ID selection
    void dropStudent();

    // update the student based on ID; can update any aspect of the student
    void updateStudent();

    // sorting operations based on last name then first name
    void insertionSort();

    void selectionSort();

    // quicksort wrapper function, recursive call, and partition function
    void quickSort();
    void quickSortRecursion(int type, int low, int high);
    // determine which partition function to call based on type input
    int partitionFirstName(int low, int high);
    int partitionLastName(int low, int high);

    // operator to print
    friend ostream &operator<<(ostream &os, Roster &r);

    // public member function to access student array
    Student *getStudents() { return students; }
};

#endif