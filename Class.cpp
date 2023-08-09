#include "Class.h"

// Default Constructor
Class::Class() {
  m_name = "CMSC201";
  m_section = 1;
}

// Overloaded constructor
Class::Class(string name, int section) {
  SetName(name);
  SetSection(section);
}

// Destructor
Class::~Class() {
  delete &m_roster;
  delete &m_waitlist;
}

// Displays students enrolled in a course
void Class::DisplayStudents() {

  // Output heading
  cout << "Course: " << GetName() << " Section: " << GetSection() << endl;
  cout << "Enrolled (" << m_roster.Size() << " enrolled)" << endl;

  // Output students in the class
  for (int i = 0; i < m_roster.Size(); i++) {
    cout << *m_roster[i];
  }

  // If there are students in the waitlist
  // Output them as well
  if (m_waitlist.Size() > 0) {
    cout << "Waitlisted (" << m_waitlist.Size() << " waitlisted)" << endl;
    for (int i = 0; i < m_waitlist.Size(); i++) {
      cout << *m_waitlist[i];
    }
  }
}

// Used to add students to a class
bool Class::AddStudent(Student *s) {
  // If the class is not full, add student
  if (!IsRosterFull()) {
    m_roster.Enqueue(s);
    return true;
  }
  // Else if the class is full but waitlist is not full
  // Add to the waitlist
  else if (!IsWaitlistFull()) {
    
      m_waitlist.Enqueue(s);
      return true;
  }
  // Else do not add to the class
  else {
    return false;
  }
}

// Used to sort students in alphabetical order
// By last name first
void Class::SortStudents() {

  // Declare temporary queues
  Tqueue<Student*, ROSTER_MAX> temp(m_roster);
  Tqueue<Student*, ROSTER_MAX> temp2(m_roster);

  // Copy queue into a temp variable
  for (int i = 0; i < m_roster.Size(); i++) {
    temp[i] = m_roster[i];
  }

  // Perform swap in ascending order
  for (int i = 0; i < m_roster.Size(); i++) {
    for (int j = i + 1; j < m_roster.Size(); j++) {
      if (*temp[j] < *m_roster[i]) {
	temp2[i] = m_roster[i];
	m_roster[i] = temp[j];
	m_roster[j] = temp2[i];
      }
    }
    
    for (int j = 0; j < m_roster.Size(); j++) {
      temp[j] = m_roster[j];
    }
    
  }
  
}

// Used to Get the name of the course
string Class::GetName() {
  return m_name;
}

// Used to set name of the course
void Class::SetName(string name) {
  m_name = name;
}

// Used to get the section of a course
int Class::GetSection() {
  return m_section;
}

// Used to set the section of a course
void Class::SetSection(int section) {
  if (section >= 1)
    m_section = section;
  else
    cout << "Wrong section entered" << endl;
}

// Used to transfer students from the waitlist
// to a new section of the course
void Class::TransferWaitToRoster(Class& destination) {
  
  int noToRemove = m_waitlist.Size();
  for (int i = 0; i < noToRemove; i++) {
    destination.m_roster.Enqueue(m_waitlist[i]);
  }

  for (int j = 0; j < noToRemove; j++) {
    m_waitlist.Dequeue();
  }  
}

// Used to check if the course section is at maximum capacity
bool Class::IsRosterFull() {
  if (m_roster.IsFull() == 1)
    return true;
  else
    return false;
}

// Used to check if the waitlist of a course is full
bool Class::IsWaitlistFull() {
  if (m_waitlist.IsFull() == 1)
    return true;
  else
    return false;
}

// Searches all courses for name of a student
// and prints courses where student is enrolled
bool Class::SearchClass(string item) {

  // Search the courses
  for (int i = 0; i < m_roster.Size(); i++) {
    if ((item == m_roster[i]->GetFName()) ||
	(item == m_roster[i]->GetLName())) {
      return true;
    }
  }
  // Search the waitlist of the course searched above
  if (m_waitlist.Size() > 0) {
    for (int j = 0; j < m_waitlist.Size(); j++) {
      if ((item == m_waitlist[j]->GetFName()) ||
	  (item == m_waitlist[j]->GetLName())) {
	
	return true;
      }
    }
  }
  
  return false;
}

// Overloaded << operator for printing to screen
ostream& operator<< (ostream& os, Class& c) {
  os << "Course: " << c.m_name << " Section: " << c.m_section << endl;
  return os;
}
