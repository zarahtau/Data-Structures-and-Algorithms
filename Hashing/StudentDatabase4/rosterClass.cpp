#include "rosterClass.h"

#include <iostream>
#include <fstream>

Roster::Roster(ifstream &file)
{   
    string line;

    // initialize the hash table size
    const int size  = 16;
    this->size = size;

    // create an array of linked list
    HashTable = new Node* [size];

    // allocate memory for the hash table
    for(int i=0; i<size; i++)
    {
        HashTable[i] = NULL;
    }
    
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
        
        // add student to the hash table
        addStudent(s);
    }
}

Roster::Roster()
{
    // given the roster size, 16 is a suitable size
    int size = 16;
    this->size = size;

    // create an array of linked lists
    HashTable = new Node* [size];
    for(int i=0; i<size; i++)
    {   
        // set each value in the array to null
        HashTable[i] = NULL;
    }
}

Roster::~Roster()
{   
    // delete all linked lists within the array
    for(int i=0; i<size; i++)
    {
        Node *temp = HashTable[i];
        while (HashTable[i] != NULL)
        {  
            // move to the next value in the list before deleting the currently value pointed to by temp
            HashTable[i] = HashTable[i]->next;
            // delete each node in the list 
            delete temp;
            // move temp to the next value in the list 
            temp = HashTable[i];
        }
    }

    // delete the array
    delete [] HashTable;
}

void Roster::addStudent(Student &s)
{
    // get the hash index
    int index = hash(s.getID());

    // allocate memory to create a node
    Node *temp = new Node();
    temp->data = s;
    temp->next = NULL;

    // there are no values in the hash index
    if(HashTable[index] == NULL)
    {
        // assign the temporary node to the bucket in the hash table
        HashTable[index] = temp;
    } 
    // a node at that index exists - insert it in ascending order
    else
    {
        Node *current = HashTable[index];
        Node *traverse = HashTable[index];

        while (traverse!=NULL && stoi( traverse->data.getID() ) < stoi( s.getID() ))
        {
            current = traverse; // store the address in current
            traverse = traverse->next; // move to the next element in the chain
        }

        // in the case we need to insert at the first point
        if (traverse == HashTable[index])
        {
            temp->next = HashTable[index]; // point the temp variable to the previous 'first' value
            HashTable[index] = temp; // the new 'first' value is the temp 
        }
        // we are not inserting the student at the first position of the chain
        else
        {
            temp->next = current->next; // set the temp variable to point to the value after the current
            current->next = temp; // point the current to the temp to complete insertion
        }
    }
}

void Roster::dropStudent()
{
    string ID;

    cout << "Enter ID to drop student: " << endl;
    cin >> ID;

    int idx = search(ID);

    if (idx == -1)
    {
        cout << "\nStudent not found. Exiting now.\n" << endl;
        return;
    }

    // student is in the database, use a temporary variable to find the student
    Node *temp = HashTable[idx];

    // if the student is the first object in the chain
    if ( stoi(temp->data.getID()) == stoi (ID))
    {   
        bool confirm = confirmation(1, temp->data);

        if (confirm)
        {
            // delete the first object in the chain if it is the only item in the chain
            if (temp->next == nullptr)
            {
                temp = nullptr;
            }
            // delete the first object in the chain if it is not the only item in the chain
            else
            {
                temp = temp->next;
            }
            cout << "\nStudent deleted from database\n" << endl;
        }
        else 
        {   
            // deletion not confirmed
            cout << "\nStudent was not deleted from database\n" << endl;
        }
    }
    // the student is stored in the index but is not the first object in the chain
    else
    {
        Node *traverse = HashTable[idx];
        Node *current = HashTable[idx];

        while (traverse!=nullptr && stoi(traverse->data.getID()) != stoi(ID))
        {   
            // point to the value before the target value
            current = traverse;
            traverse = traverse->next;
        }
        // store the student to delete in the temporary variable
        temp = current->next;
        bool confirm = confirmation (0, temp->data);

        if (confirm)
        {
            // delete the student
            current->next = traverse->next;
            traverse->next = nullptr;
            cout << "\nStudent deleted from database\n" << endl;
        }
        else 
        {
            // deletion not confirmed
            cout << "\nStudent was not deleted from database\n" << endl;
        }
    }
}

void Roster::updateStudent()
{
    string ID;

    cout << "Enter ID to update student: " << endl;
    cin >> ID;

    int idx = search(ID);

    if (idx == -1)
    {
        cout << "\nStudent not found. Exiting now.\n" << endl;
        return;
    }

    // student is in the database, use a temporary variable to find the student
    Node *temp = HashTable[idx];

    // store the new student to make changes
    Student studentForUpdate;

    // student is the first object in the chain
    if (stoi(ID) == stoi(temp->data.getID()))
    {
        studentForUpdate = temp->data;
    }
    // find the student in the chain if it is not the first object in the bucket
    while(temp!=NULL)
    {
        if(stoi(ID) == stoi(temp->data.getID()))
        {
            break;
        }
        temp = temp->next;
    }
    // the student to update is now stored as the student
    studentForUpdate = temp->data;

    // update student information
    bool confirm = confirmation(1, studentForUpdate);

    if (!confirm)
    {
        cout << "\nUpdate not confirmed. Good bye" << endl;
    }

    int selection = -1;
    string updateString;

    cout << "Selection for update. Enter corresponding interger: \n";
    cout << "[1] First Name Update \n[2] Last Name Update \n[3] Level Update" << endl;
    cin >> selection;
    // clear the input buffer before calling 'getline()'
    cin.ignore();

    // update first name
    if(selection == 1)
    {
        cout << "Enter First Name: " << endl;
        getline(cin, updateString);
        studentForUpdate.setfName(updateString);
    }
    else if (selection == 2)
    {
        cout << "Enter Last Name: ";
        getline(cin, updateString);
        studentForUpdate.setlName(updateString);
    } 
    else if (selection == 3)
    {
        cout << "Enter Level: ";
        getline(cin, updateString);
        studentForUpdate.setLevel(updateString);
    }
    else
    {
        cout << "Invalid Selection" << endl;
        return;
    }

    temp->data = studentForUpdate;
    cout << "Update: " << temp->data << endl;
}   

int Roster::hash(string ID)
{   
    // possible hash function stoi(ID) % size
    return stoi(ID) % size;
}

int Roster::search(string ID)
{   
    int index = hash(ID);

    if (HashTable[index]==nullptr)
    {
        return -1;
    }

    // create a temporary variable to move through the hash chain
    Node *temp = HashTable[index];

    while(temp != nullptr)
    {
        if (stoi(ID) == stoi(temp->data.getID()) )
        {
            return index;
        }
        temp = temp->next;
    }

    // the ID does not exist in the hash table
    return -1;
}

bool Roster::confirmation(int type, Student &s)
{   
    int confirm = -1;

    // two types - 0 is update 1 is delete
    if (type == 0)
    {
        // confimation:
        cout << "------------------------------------------" << endl;
        cout << "Confirm Deletion of " << s << endl;
        cout << "Enter [1] to delete or other int to exit: ";
        cin >> confirm;
        cout << "\n------------------------------------------" << endl;
    }
    else if (type == 1)
    {
        // confimation:
        cout << "Update pending for " << s << endl;
        cout << "Enter [1] to confirm student for update or other int to exit: ";
        cin >> confirm;
        cout << "\n------------------------------------------" << endl;
    }

    if(confirm == 1)
    {
        return true;
    }
    return false;

}

ostream &operator<<(ostream &os, Roster &r)
{   
    // temporary variable to point to the beginning of the hash table

    os << "\n------------------------------------------" << endl;
    for(int i=0; i<r.size; i++)
    {
        Node *temp = r.HashTable[i];
        while(temp!=nullptr)
        {
            os << temp->data << endl;
            temp = temp->next;
        }
        os << "------------------------------------------" << endl;
    }


    return os;
}