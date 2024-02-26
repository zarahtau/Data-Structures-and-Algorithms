#ifndef STUDENT_CLASS_H
#define STUDENT_CLASS_H

#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream>

using namespace std;

string upperConversion(string s);

class Student
{
private:
    string ID;
    string fName;
    string lName;
    string level;

public:
    // constructor
    Student();
    Student(string ID, string fName, string lName, string level);

    // setters
    void setID(string ID);
    void setfName(string fName);
    void setlName(string lName);
    void setLevel(string level);

    // getters
    string getID();
    string getfName();
    string getlName();
    string getLevel();

    // print the student information
    friend ostream &operator<<(ostream &os, Student &s);

    // assignment operator
    void operator=(const Student &s);
};

#endif