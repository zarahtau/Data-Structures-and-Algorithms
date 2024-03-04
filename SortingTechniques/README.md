# Student Roster Management System
This is a simple, terminal-based student database management system designed for temporary data handling.
It allows for addition, deletion, and modification of student records in a command-line interface.

## Contents
### Student Database 1
- 'main.cpp': The core of the program. It interfaces with the user, facilitating the management of the student roster
from a .txt file. It includes operations like adding, removing, updating, and sorting student records
- 'studentClass': Defines the 'Student' class with attributes and function to individual students. This includes student information like ID, name, and grades
- 'rosterClass' : Introduces the 'Roster' class which manages a collection of 'Student' objects with an array.

#### Included Sorting Algorithms based on Name
- Insertion Sort
- Selection Sort
- Quick Sort

### Student Database 2
Building on the foundation of Student Database 1, this version elevates the managements by connecting student objects via linked lists, allowing more efficient data manipulation and access. 

#### Key Features
- **Linked List Integration**: Student records are now managed using linked lists, allowing for more efficient data manipulation and access. This eases the process of insertion, delection, and traversal of student data.
- **Enhanced Sorting Capability**: Uses a Merge Sort algorithm tailored to organize student records by ID. This provides a more advanced and efficient way to manage information.

### Student Database 3
This version uses a pointer array for managing student data. Each element of the array points to a student object, allowing for direct access to individual record.

#### Key Features
- **Heap Building**: Constructs a heap from the existing student records. Insert node function adds a new student record while maintaing the heap property. This allows for dynamic expansion of the database.
- **Heap Sort Integration**: The database gains enhanced sorting capabilities. Heap sort optimizes the arrangement of student databased based on ID.
