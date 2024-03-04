#include "rosterClass.h"

#include <iostream>
#include <fstream>

Roster::Roster(ifstream &file)
{
    string line;
    studentArraySize = 100;
    students = new Student[studentArraySize];

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

        // call build heap
        buildHeap();
    }
   
}

void Roster::addStudent(Student &s)
{
    if (currentSize < studentArraySize)
    {
        students[currentSize] = s;
        insertNode(currentSize);
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

    cout << "Enter ID to drop student:" << endl;
    cin >> ID;

    // find student in database based on ID
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
        cout << "Student was not deleted from databse" << endl;
        return;
    }
    else if (idx == currentSize - 1)
    { // the ID is the last element in the array, no need to heapify
        currentSize--;
        cout << "\nStudent deleted from database" << endl;
        return;
    }
    else
    {
        for (int i = idx; i < currentSize; i++)
        {
            students[i] = students[i + 1];
        }
        currentSize--;
        // once student is deleted, we will need to rebuild the heap
        buildHeap();
        cout << "\nStudent deleted from database" << endl;
    }
}

void Roster::updateStudent()
{
    string ID;
    int confirmation;
    int IDidx = -1;
    int selection;
    string updateString;

    // Enter ID to find student in database
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

    // update ID
    if (selection == 1)
    {
        cout << "Enter ID: ";
        getline(cin, updateString);
        students[IDidx].setID(updateString);
        // if the ID changes, we need to rebuild the heap
        buildHeap();
    }
    // update first name
    else if (selection == 2)
    {
        cout << "Enter First Name: " << endl;
        getline(cin, updateString);
        students[IDidx].setfName(updateString);
    }
    // update last name
    else if (selection == 3)
    {
        cout << "Enter Last Name: ";
        getline(cin, updateString);
        students[IDidx].setlName(updateString);
    }
    // update level
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

void Roster::buildHeap()
{   
    // Determine the starting index for heapification
    // Start from the middle of the array and work way towards beginning 
    // to ensure efficient heap construction
   int startIdx = (currentSize/2)-1;

   for(int i=startIdx; i>=0; i--)
   {
        heapify(i);
   }
}

void Roster::heapify(int n)
{   
    // the item add to the heap is inserted 
    int largest = n;
    int leftNode = 2*n + 1;
    int rightNode = 2*n + 2;

    // extract the ID from the students array and convert to integer
    int itemID = stoi(students[largest].getID());

    // if the left child is larger than the current largest
    // update the index of the largest ID to the left node
    if(leftNode<currentSize && stoi(students[leftNode].getID()) > itemID)
    {
        largest = leftNode;
    }

    // if the right child is larger than the current largest
    // update the index of the largest ID to the right node
    if(rightNode<currentSize && stoi(students[rightNode].getID()) > itemID)
    {   
        largest = rightNode;
    }

    // if the children exist and if its ID is larger than the current 'largests' ID
    // swap values
    if (largest!=n)
    {   
        swap(students[n], students[largest]);

        // recursively call the affected sub-tree at index 'largest'
        heapify(largest);
    }

}

void Roster::insertNode(int n)
{   
    // one value in heap, no need to sort
    if(n==0)
    {
        return;
    }

    // percolate up to determine the ID placement in the heap
    int itemID = stoi(students[n].getID());

    // locate the parent node, used to determine if swapping is necessary 
    int i = n;

    // continue until we have reached the parent node && the parent of the current child (item) id is less
    while( i>0 && stoi(students[(i-1)/2].getID()) < itemID)
    {
        swap(students[ (i-1) / 2], students[i]);
        i = (i-1)/2; // move to parent index
    }

}

void Roster::heapSort()
{   
    // there is one value in the heap, return
    if(currentSize < 1)
    {
        return;
    }

    // determine the index of the last value in heap
    int currentIdx = currentSize-1;

    while(currentIdx >= 0)
    {
        // swap the highest value (first value) with the last
        swap(students[currentIdx], students[0]);

        // percolate down 
        int item = stoi(students[0].getID());

        int i = 0;
        // find the respective child nodes for the parent
        int j = (i*2) + 1;

        int heapSize = currentIdx;
        while (j < heapSize)
        {   
            // if we are within the bounds of the current heap size && if the right child is less then the left
            if (j+1 < heapSize && stoi(students[j].getID()) < stoi(students[j+1].getID()))
            {
                j++;
            }
            // the item has reached its correct position in the heap
            if (item > stoi(students[j].getID()))
            {
                break;
            }

            // swap the parents with its respective right or left child
            swap(students[(j-1)/2], students[j]);
            
            // move the current value of j to its respective child
            j = (j*2) + 1;
        }
        // decrement the size of the heap
        currentIdx--;
    }
}

ostream &operator<<(ostream &os, Roster &r)
{   
    // save the array of students in a new student array
    Student *rosterStudents = r.getStudents();

    for (int i = 0; i < r.currentSize; i++)
    {   
        // traverse and print all students
        os << rosterStudents[i] << endl;
    }

    return os;
}