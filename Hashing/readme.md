# Student Roster Management System
### Student Database 4
Another use of the terminal-based student database management system designed for temporary data handling.
It allows for CRUD(Create, Read, Update, Delete) operations typical in a database management system.

- 'main.cpp': Interfaces with the user, facilitating the management of the student roster
from a .txt file. 
- 'studentClass': Implements the 'Student' class to model student data. Features methods for retrieving student attributes (ID, name, level)
- 'rosterClass': Defines the 'roster' of students. It features a method for adding, dropping, and updating student records, utilizing a hash table for efficient data retrieval

#### Separate Chaining Hash 
Within the roster class, chaining is used as the collision resolution technique for the hash table. This involves using linked lists for each hash table buckets 
to store multiple entries that map to the same index. 
