#include "studentClass.h"
#include "rosterClass.h"
#include "rosterClass.cpp"
#include "studentClass.cpp"

// implementation of max heap sort of students

int main()
{
    ifstream rosterFile;
    rosterFile.open("roster.txt", ios::out);

    if (!rosterFile)
    {
        cout << "Error opening file" << endl;
    }
    else
        cout << "File opened successfully" << endl
             << endl;

    Roster r(rosterFile);
    cout << r;

    cout << "\n\n---------------ADD NEW STUDENTS TO HEAP----------------------" << endl
         << endl;
    Student s1("10000", "ford", "gerald", "freshman"), s2("9999", "mckay", "sequoia", "senior"), s3("0001", "lovelace", "ada", "senior");

    r.addStudent(s1);
    r.addStudent(s2);
    r.addStudent(s3);

    r.dropStudent();

    cout << "\n\n---------------HEAP SORT----------------------" << endl
    << endl;
    r.heapSort();
    cout << r;

    // close the file
    rosterFile.close();

    return 0;
}