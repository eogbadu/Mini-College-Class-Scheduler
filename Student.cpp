#include "Student.h"

// Default constructor
Student::Student(string fName) {
  m_fName = fName;
  m_lName = "Ogbadu";
  m_id    = 1;
}

// Overloaded constructor
Student::Student(string fName, string lName, int id) {
  SetFName(fName);
  SetLName(lName);
  SetID(id);
}

// Used to get the first name of a student
string Student::GetFName() {
  return m_fName;
}

// Used to get the last name of a student 
string Student::GetLName() {
  return m_lName;
}

// Used to get the id number of a student 
int Student::GetID() {
  return m_id;
}

// Used to set the first name of a student 
void Student::SetFName(string fName) {
  m_fName = fName;
}

// Used to set the last name of a student 
void Student::SetLName(string lName) {
  m_lName = lName;
}

// Used to set the id number of a student 
void Student::SetID(int id) {
  m_id = id;
}

// Overloaded << operator to print to screen
ostream& operator<< (ostream& outputStream, Student& s) {
  outputStream << s.m_fName << ", " << s.m_lName << endl;
  return outputStream;
}

// Overloaded < operator used to compare students when sorting
// Higher priority given to the last name
bool operator< (const Student &s1, const Student &s2) {
  if (s1.m_lName < s2.m_lName) {
    return true;
  }
  else if (s1.m_lName == s2.m_lName) {
    if (s1.m_fName < s2.m_fName) {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}
