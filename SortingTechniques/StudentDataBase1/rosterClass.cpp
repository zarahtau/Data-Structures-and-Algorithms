#include "rosterClass.h"

#include <iostream>
#include <fstream>

Roster::Roster(ifstream &file)
{
    string line;

    studentArraySize = 100;
    currentSize = 0;

    // read all the lines of the source txt file
    while (getline(file, line))
    {
        string substring = "";
        string studentInformation[4];

        // now that a complete line has been read, we want to store it into istringstream to use iostream functions
        istringstream iss(line);

        // get the substrings within each student information
        int i = 0;
        while (getline(iss, substring, ','))
        {
            studentInformation[i] = substring;
            i++;
        }

        Student s(studentInformation[0], studentInformation[1], studentInformation[2], studentInformation[3]);

        students[currentSize] = s;

        currentSize++;
    }
}

void Roster::addStudent(Student &s)
{
    if (currentSize < studentArraySize)
    {
        students[currentSize] = s;
        currentSize++;
        cout << "Student successfully added" << endl;
    }
    else
        cout << "Student not added to roster" << endl;
}

void Roster::dropStudent()
{
    string ID;
    int confirmation;
    int idx = -1;

    cout << "Enter ID:" << endl;
    cin >> ID;

    for (int i = 0; i < currentSize; i++)
    {
        if (ID == students[i].getID())
        {
            idx = i;
            break;
        }
    }
    if (idx == -1)
    {
        cout << "Student not found" << endl;
        return;
    }
    // confimation:
    cout << "Confirm Deletion of " << students[idx] << endl;
    cout << "Enter [1] to delete or [0] to exit: ";
    cin >> confirmation;

    if (confirmation == 0)
    {
        cout << "Student Deletion not Confirmed" << endl;
        return;
    }
    else if (idx == currentSize - 1)
    { // the ID is the last element in the array
        currentSize--;
        return;
    }
    else
    {
        for (int i = idx; i < currentSize; i++)
        {
            students[i] = students[i + 1];
        }
        currentSize--;
    }
}

void Roster::updateStudent()
{
    string ID;
    int confirmation;
    int IDidx = -1;
    int selection;
    string updateString;

    cout << "Enter ID:" << endl;
    cin >> ID;

    for (int i = 0; i < currentSize; i++)
    {
        if (ID == students[i].getID())
        {
            IDidx = i;
            break;
        }
    }

    if (IDidx != -1)
    {
        cout << "Update Pending for " << students[IDidx];
        cout << "Selection for update. Enter corresponding interger: \n";
        cout << "[1] ID Update \n[2] First Name Update \n[3] Last Name Update \n[4] Level Update" << endl;
        cin >> selection;
        // clear the input buffer before calling 'getline()'
        cin.ignore();
    }
    else
    {
        cout << "ID not found" << endl;
        return;
    }

    if (selection == 1)
    {
        cout << "Enter ID: ";
        getline(cin, updateString);
        students[IDidx].setID(updateString);
    }
    else if (selection == 2)
    {
        cout << "Enter First Name: " << endl;
        getline(cin, updateString);
        students[IDidx].setfName(updateString);
    }
    else if (selection == 3)
    {
        cout << "Enter Last Name: ";
        getline(cin, updateString);
        students[IDidx].setlName(updateString);
    }
    else if (selection == 4)
    {
        cout << "Enter Level: ";
        getline(cin, updateString);
        students[IDidx].setLevel(updateString);
    }
    else
    {
        cout << "Invalid Selection" << endl;
        return;
    }

    cout << "Update: " << students[IDidx] << endl;
}

void Roster::insertionSort()
{
    // sort last names using insertation sort
    for (int i = 1; i < currentSize; i++)
    {
        Student currentStudent = students[i];

        int j = i - 1;
        while (j >= 0 && students[j].getlName() > currentStudent.getlName())
        {
            students[j + 1] = students[j];
            j--;
        }
        students[j + 1] = currentStudent;
    }

    int idx = 0;
    while (idx < currentSize - 1)
    {
        int arraySize = 1;
        // finding repeated last names
        while (students[idx].getlName() == students[idx + arraySize].getlName() && (idx + arraySize < currentSize))
        {
            arraySize++;
        }

        if (arraySize > 1)
        {
            // insertion sort based on first name
            for (int i = idx + 1; i < arraySize + idx; i++)
            {
                // key
                Student currentStudent = students[i];
                int j = i - 1;
                while (j >= idx && students[j].getfName() > currentStudent.getfName())
                {
                    students[j + 1] = students[j];
                    j--;
                }
                students[j + 1] = currentStudent;
            }
            arraySize = 1;
        }
        idx += arraySize;
    }
}

void Roster::selectionSort()
{
    // sort by last name
    for (int i = 0; i < currentSize; i++)
    {
        int minIdx = i;
        int currentMinimum = i;

        while (currentMinimum < currentSize)
        {
            if (students[currentMinimum].getlName() <= students[minIdx].getlName())
            {
                minIdx = currentMinimum;
            }
            currentMinimum++;
        }
        // swap the student objects with the name with the "minimum" last name
        if (minIdx != i)
        {
            Student temp = students[i];
            students[i] = students[minIdx];
            students[minIdx] = temp;
        }
    }
}

void Roster::quickSort()
{
    quickSortRecursion(0, 0, currentSize - 1);

    // once sorted, call quickSort recursion function for the first names
    int idx = 0;
    while (idx < currentSize - 1)
    {
        int arraySize = 1;
        while (students[idx].getlName() == students[idx + arraySize].getlName() && idx + arraySize < currentSize)
        {
            arraySize++;
        }
        if (arraySize > 1)
        {
            // type one indicates we are sorting by last name
            quickSortRecursion(1, idx, arraySize + idx - 1);
        }
        idx += arraySize;
    }
}

void Roster::quickSortRecursion(int type, int low, int high)
{
    if (low < high && type == 0)
    {
        int pivot_index = partitionLastName(low, high);

        quickSortRecursion(0, low, pivot_index - 1);
        quickSortRecursion(0, pivot_index + 1, high);
    }
    else if (low < high && type == 1)
    {
        int pivot_index = partitionFirstName(low, high);

        quickSortRecursion(1, low, pivot_index - 1);
        quickSortRecursion(1, pivot_index + 1, high);
    }
}

int Roster::partitionFirstName(int low, int high)
{
    string pivot_value = students[high].getfName();
    int i = low;

    for (int j = low; j < high; j++)
    {
        if (students[j].getfName().compare(pivot_value) < 0)
        {
            Student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
            i++;
        }
    }

    Student temp = students[i];
    students[i] = students[high];
    students[high] = temp;
    return i;
}

int Roster::partitionLastName(int low, int high)
{
    string pivot_value = students[high].getlName();
    int i = low;

    for (int j = low; j < high; j++)
    {
        if (students[j].getlName().compare(pivot_value) < 0)
        {
            // swao to sort last names that are greater than or less than the value
            Student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
            i++;
        }
    }
    // need to swap the pivot to the 'middle' of the partition
    // swap the current index of i and the pivot which is 'high'
    Student temp = students[i];
    students[i] = students[high];
    students[high] = temp;
    return i;
}
ostream &operator<<(ostream &os, Roster &r)
{
    Student *rosterStudents = r.getStudents();

    for (int i = 0; i < r.currentSize; i++)
    {
        os << rosterStudents[i] << endl;
    }

    return os;
}