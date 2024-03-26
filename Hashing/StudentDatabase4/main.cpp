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
    cout << r;

    cout << "\n\n***************** DROP STUDENT ***************** " << endl  
        << endl;
    r.dropStudent();
    cout << r;

    cout << "\n\n**************** UPDATE STUDENT **************** " << endl  
        << endl;
    r.updateStudent();
    cout << r;
}