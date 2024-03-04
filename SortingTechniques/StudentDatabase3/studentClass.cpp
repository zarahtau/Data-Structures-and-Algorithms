#include "studentClass.h"

#include <iostream>

using namespace std;

Student::Student()
{
    ID = "";
    fName = "";
    lName = "";
    level = "";
}

Student::Student(string ID, string lName, string fName, string level)
{
    this->ID = ID;
    this->lName = upperConversion(lName);
    this->fName = upperConversion(fName);
    this->level = upperConversion(level);
}

void Student::setID(string ID)
{
    this->ID = ID;
}

void Student::setfName(string fName)
{
    this->fName = upperConversion(fName);
}

void Student::setlName(string lName)
{
    this->lName = upperConversion(lName);
}

void Student::setLevel(string level)
{
    this->level = upperConversion(level);
}

string Student::getID()
{
    return ID;
}

string Student::getfName()
{
    return fName;
}

string Student::getlName()
{
    return lName;
}

string Student::getLevel()
{
    return level;
}

ostream &operator<<(ostream &os, Student &s)
{
    os << "ID: " << s.getID() << " Name: " << s.getfName() << " " << s.getlName() << " Level: " << s.getLevel() << endl;
    return os;
}

void Student::operator=(const Student &s)
{
    ID = s.ID;
    lName = s.lName;
    fName = s.fName;
    level = s.level;
}
string upperConversion(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (i == 0 && !s.empty() && islower(s[0]))
        {
            s[0] = toupper(s[0]);
        }

        if (s[i] == ' ' && i + 1 < s.size() - 1)
        {
            s[i + 1] = toupper(s[i + 1]);
        }
    }
    return s;
}