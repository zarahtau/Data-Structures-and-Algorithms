#include "studentClass.h"
#include "rosterClass.h"
#include "rosterClass.cpp"
#include "studentClass.cpp"

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

    cout << "\n\n---------------INSERTATION SORT----------------------" << endl
         << endl;
    r.insertionSort();
    cout << r;

    cout << "\n\n---------------ADD NEW STUDENTS----------------------" << endl
         << endl;
    Student s1("3241", "ford", "gerald", "freshman"), s2("9999", "mckay", "maple", "senior"), s3("0001", "lovelace", "ada", "senior");

    r.addStudent(s1);
    r.addStudent(s2);
    r.addStudent(s3);

    cout << "\n\n---------------SELECTION SORT----------------------" << endl
         << endl;
    r.selectionSort();
    cout << r;

    cout << "\n\n---------------DROP STUDENT----------------------" << endl
         << endl;
    r.dropStudent();

    cout << "\n\n---------------QUICK SORT----------------------" << endl
         << endl;
    r.quickSort();
    cout << r;

    // close the file
    rosterFile.close();

    return 0;
}