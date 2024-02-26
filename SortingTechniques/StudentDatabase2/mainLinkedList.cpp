#include "studentClass.h"
#include "studentClass.cpp"

#include "studentDBLinkedList.h"
#include "studentDBLinkedList.cpp"

int main()
{
  ifstream studentFile;
  studentFile.open("roster.txt", ios::out);

  if (!studentFile)
  {
    cout << "\nError opening file" << endl;
  }
  else
    cout << "\nFile opened successfully" << endl;

  StudentDB s(studentFile);

  cout << s;

  cout << "\n\n-----------------------MERGE SORT--------------------------" << endl;
  s.mergeSort();
  cout << s;

  s.updateStudent();
  s.dropStudent();

  studentFile.close();

  return 0;
}