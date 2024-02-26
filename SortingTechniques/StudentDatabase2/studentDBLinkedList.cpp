#include "studentDBLinkedList.h"

#include <iostream>
#include <fstream>

using namespace std;

StudentDB::StudentDB()
{
    head = tail = NULL;
    length = 0;
}

void StudentDB::appendStudent(Student s)
{
    cout << "\n////////////////////// ADD STUDENT //////////////////////" << endl;
    // simply adding to the end the linked list
    Node *temp = new Node();
    temp->data = s;
    temp->next = nullptr;

    if (length == 0 || head == nullptr)
    {
        head = tail = temp;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
    length++;

    cout << "Adding  " << s << " to database";
    cout << "\n////////////// APPEND SUCCESSFUL - EXITING NOW //////////////" << endl;
}

void StudentDB::updateStudent()
{
    // check to see if there are nodes in the list
    if (head == nullptr || length == 0)
    {
        cout << "Database is empty" << endl;
        return;
    }
    cout << "\n////////////////////// UPDATE STUDENT //////////////////////" << endl;
    int type;
    string id;

    cout << "\nEnter ID for student update:" << endl;
    cin >> id;

    // search for id in the student database
    Node *temp = head;
    bool isInDatabase = false;
    while (temp != NULL)
    {
        if (temp->data.getID() == id)
        {
            isInDatabase = true;
            break;
        }
        temp = temp->next;
    }

    // determine if student is in database and prompt user for update selection
    int selection;
    if (isInDatabase)
    {
        cout << "Update for " << temp->data << endl;
        cout << "UPDATE SELECTION: Enter integer for selection: \n";
        cout << "[1] ID Update \n[2] First Name Update \n[3] Last Name Update \n[4] Level Update\n[5] EXIT " << endl;
        cin >> selection;
    }
    else
    {
        cout << "////////////// STUDENT NOT FOUND - EXITING NOW //////////////" << endl
             << endl;
        return;
    }

    // student update section
    if (selection == 5)
    {
        cout << "///////// NO CHANGES MADE IN DATABASE - EXITING NOW /////////" << endl
             << endl;
        return;
    }
    else if (selection > 5 || selection < 1)
    {
        cout << "////////////// INVALID SELECTION - EXITING NOW //////////////" << endl
             << endl;
        return;
    }
    else
    {
        string updateString;
        if (selection == 1)
        {
            cin.ignore(); // ignore the input buffer
            cout << "Enter ID for Update: ";
            getline(cin, updateString);
            temp->data.setID(updateString);
        }
        else if (selection == 2)
        {
            cin.ignore();
            cout << "Enter First Name for Update: ";
            getline(cin, updateString);
            temp->data.setfName(updateString);
        }
        else if (selection == 3)
        {
            cin.ignore();
            cout << "Enter Last Name for Update: ";
            getline(cin, updateString);
            temp->data.setlName(updateString);
        }
        else if (selection == 4)
        {
            cin.ignore();
            cout << "Enter Level for Update: ";
            getline(cin, updateString);
            temp->data.setLevel(updateString);
        }
        cout << "\nUpdate:\n"
             << temp->data;
        cout << "\n////////////// UPDATE SUCESSFULL - EXITING NOW //////////////" << endl
             << endl;
    }
}

void StudentDB::dropStudent()
{
    // check to see if there are nodes in the list
    if (head == nullptr || length == 0)
    {
        cout << "Database is empty" << endl;
        return;
    }
    cout << "\n/////////////////////// DROP STUDENT ///////////////////////" << endl;

    string id;

    cout << "\nEnter ID to drop student:" << endl;
    cin >> id;

    // find student in database
    bool isInDatabase = false;
    Node *temp = head;
    int index = 0;
    while (temp != NULL)
    {
        index++;
        if (temp->data.getID() == id)
        {
            isInDatabase = true;
            break;
        }
        temp = temp->next;
    }

    int confirmation;
    if (!isInDatabase)
    {
        cout << "\n////////////// STUDENT NOT FOUND - EXITING NOW //////////////" << endl
             << endl;
        return;
    }
    else
    {
        cout << "\nConfirm deletion for " << temp->data << endl;
        cout << "[1] to confirm\n[ANY INT] to exit" << endl;
        cin >> confirmation;
    }

    if (confirmation != 1)
    {
        cout << "\n///////////// STUDENT NOT DROPPED - EXITING NOW /////////////" << endl;
        return;
    }
    // delete student from data base
    else
    {
        // instance where the student to be dropped is the first student in the database
        if (index == 1)
        {
            temp = nullptr;
            head = head->next;
        }
        // instance where the student to be dropped is the last student in the database
        else if (index == length)
        {
            Node *current = head;
            for (int i = 0; i < index - 2; i++)
            {
                current = current->next;
            }
            current->next = nullptr;
            tail = current;
        }
        // instance where the student to be dropped is neither the first nor last in the database
        else
        {
            // reach the node before the value to be deleted
            Node *current = head;
            for (int i = 0; i < index - 2; i++)
            {
                current = current->next;
            }
            current->next = temp->next;
            temp->next = nullptr;
        }
        // delete the temporary variable and decrease the tracked length of the string
        delete temp;
        length--;
        cout << "\n/////////////// STUDENT DROPPED - EXITING NOW ///////////////" << endl;
    }
}

void StudentDB::mergeSort()
{
    if (head != nullptr)
    {
        head = mergeSortRecursion(head);
    }
}
Node *StudentDB::mergeSortRecursion(Node *headRef)
{
    // base case - length of 0 or 1
    if (headRef->next == nullptr || head == nullptr)
    {
        return headRef;
    }
    // find the middle
    Node *slow = headRef;
    Node *fast = headRef->next;

    while (fast != nullptr && fast->next != nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    Node *secondHalf = slow->next;
    slow->next = nullptr; // split the two lists

    // recursively sort the sublists

    Node *left = mergeSortRecursion(headRef);
    Node *right = mergeSortRecursion(secondHalf);

    // merge the two sorted listed together
    Node *newHead = mergeSortedList(left, right);

    return newHead;
}

Node *StudentDB::mergeSortedList(Node *a, Node *b)
{
    if (a == nullptr)
        return b;
    if (b == nullptr)
        return a;

    // acts as temporary head of the new list
    Node *dummy = new Node();
    // tail points to the last node in the newList
    Node *tail = dummy;

    while (a != nullptr && b != nullptr)
    {
        // check which value is larger or smaller
        if (a->data.getID().compare(b->data.getID()) <= 0)
        {
            tail->next = a;    // append 'a' to the new list
            a = a->next;       // advance 'a'
            tail = tail->next; // move the tail pointer so it always points to the last node in the new list
        }
        else
        {
            tail->next = b;    // append 'b' to the new list
            b = b->next;       // advance 'b'
            tail = tail->next; // move the tail pointer so it always points to the last node in the new list
        }
    }
    // either a or b is nullptr; append them remaining elements to the tail
    while (b != nullptr)
    {
        tail->next = b; // append 'b' to the new list
        b = b->next;    // advance 'b'
        tail = tail->next;
    }
    while (a != nullptr)
    {
        tail->next = a; // append 'a' to the new list
        a = a->next;    // advance 'a'
        tail = tail->next;
    }

    return dummy->next;
}
StudentDB::StudentDB(ifstream &file)
{
    head = tail = NULL;
    length = 0;

    string line;
    while (getline(file, line))
    {
        string substring = "";
        string studentInformation[4];

        istringstream iss(line);

        int i = 0;
        while (getline(iss, substring, ','))
        {
            studentInformation[i] = substring;
            i++;
        }

        Student s(studentInformation[0], studentInformation[1], studentInformation[2], studentInformation[3]);
        // add the current student to the linked list
        // allocate the new node
        Node *temp = new Node();
        temp->data = s;
        temp->next = nullptr;

        // first item added to the list
        if (head == nullptr)
        {
            head = tail = temp;
        } // add to the end of the list
        else
        {
            tail->next = temp;
            tail = temp;
        }
        length++;
    }
}

StudentDB::~StudentDB()
{
    cout << "\nDestructor called successfully" << endl;
}

ostream &operator<<(ostream &os, const StudentDB &db)
{
    if (db.head == nullptr)
    {
        os << "Student database is null" << endl;
    }
    else
    {
        Node *temp = db.head;
        cout << "\n///////////////////// STUDENT DATABASE /////////////////////" << endl;
        while (temp != NULL)
        {
            if (!temp->data.getID().empty())
            {
                os << temp->data;
            }
            temp = temp->next;
        }
        cout << "\n////////////////////////////////////////////////////////////" << endl;
    }
    return os;
}
