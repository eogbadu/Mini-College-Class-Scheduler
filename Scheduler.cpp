#include "Scheduler.h"

// Default constructor
Scheduler::Scheduler() {
  m_name = "Spring 2020";
  m_fileName = "proj5_test1.txt";
}

// Overloaded constructor
Scheduler::Scheduler(string fileName) {
  m_name = "Spring 2020";
  m_fileName = fileName;
}

// Destructor
Scheduler::~Scheduler() {
  for ( vector<Class*>::iterator i = m_classes.begin(); i != m_classes.end(); ++i )
    delete *i;
}

// Loads a file into queues
void Scheduler::LoadFile() {
  string fName;
  string lName;
  string studentID;
  string courseName;

  ifstream inStream;
  inStream.open(m_fileName);

  if (inStream.fail()) {
    cout << "File failed to load.\n";
  }
  else {
    while (getline(inStream, fName, ',')) {
      getline (inStream, lName, ',');
      getline (inStream, studentID, ',');
      getline (inStream, courseName, '\n');

      Student *tempStudent = new Student(fName, lName, stoi(studentID));
      AddStudent(tempStudent, courseName);

    }
  }   
}

// Starts the game and prints the main menu
void Scheduler::Start() {
  cout << "Welcome to the UMBC Scheduler\n";
  LoadFile();
  MainMenu();
}

// The main menu in the program
void Scheduler::MainMenu() {
  int choice;

  cout << "1. Display All Courses\n";
  cout << "2. Display a Specific Course\n";
  cout << "3. Search for Specific Student\n";
  cout << "4. Sort Roster\n";
  cout << "5. Quit\n";

  cin >> choice;

  while ((choice < 1) || (choice > 5)) {
    cout << "Please enter a choice between 1 and 5\n";
    cout << "1. Display All Courses\n";
    cout << "2. Display a Specific Course\n";
    cout << "3. Search for Specific Student\n";
    cout << "4. Sort Roster\n";
    cout << "5. Quit\n";

    cin >> choice;
  }

  switch (choice) {
  case 1:
    DisplayCourses();
    break;
  case 2:
    DisplaySpecific();
    break;
  case 3:
    SearchStudent();
    break;
  case 4:
    SortRoster();
    break;
  case 5:
    exit (0);
    break;
  default:
    cout << "We tried didn't we?";
  }
}

// Display all courses in the scheduler
void Scheduler::DisplayCourses() {
  for (unsigned int i = 0; i < m_classes.size(); i++) {
    cout << i + 1 << " " << *m_classes[i];
  }
  cout << endl;
  MainMenu();
}

// Display a specific course
void Scheduler::DisplaySpecific() {
  int choice;
  int size = m_classes.size();
  
  cout << "Which course would you like to display?\n";

  for (unsigned int i = 0; i < m_classes.size(); i++) {
    cout << i + 1 << " " << *m_classes[i];
  }
  cin >> choice;

  while ((choice < 1) || (choice > size)) {
    cout << "Please enter a choice between 1 and " << m_classes.size() << endl;

    for (unsigned int i = 0; i < m_classes.size(); i++) {
      cout << i+ 1 << " " << *m_classes[i];
    }
    cin >> choice;
  }

  cout << "Displaying Student\n";
  m_classes[choice - 1]->DisplayStudents();
  cout << endl;
  MainMenu();
}

// Search for a student in the scheduler
void Scheduler::SearchStudent() {
  string studentName;
  cout << "What name do you want to search for?\n";
  cin >> studentName;

  cout << "Items with " << studentName << " in them:\n";
  for (unsigned int i = 0; i < m_classes.size(); i++) {
    if (m_classes[i]->SearchClass(studentName)) {
      cout << *m_classes[i] << endl;
    }
  }

  MainMenu();
}

// Sorts all the names in the scheduler in alphabetical order
void Scheduler::SortRoster() {
  for (unsigned int i = 0; i < m_classes.size(); i++) {
    m_classes[i]->SortStudents();
  }
  cout << endl;
  MainMenu();
}

// Helper function to find a course given the name
int Scheduler::FindClass(string course) {
  if (m_classes.size() > 0) {
    for (int i = m_classes.size(); i > 0; i--) {
      if (m_classes.at(i - 1)->GetName() == course) {
	return i - 1;
      }
    }
  }

  return -1;
}

// Add student to a course
void Scheduler::AddStudent(Student *s, string course) {
  int courseSection = 1;
  int initialSection = 1;
  int classIndex = FindClass(course);

  // If the course already exists
  // Attempt to add student
  if (classIndex >= 0) {
    // If student is added return
    if (m_classes.at(classIndex)->AddStudent(s)) {
      return;
    }
    // Else add a new section of the class 
    else {
      courseSection = m_classes.at(classIndex)->GetSection() + 1;
     
      Class *tempClass = new Class(course, courseSection);

      // Transfer students from waitlist to new section
      // then add new student to section
      m_classes.at(m_classes.size() - 1)->TransferWaitToRoster(*tempClass);
      m_classes.push_back(tempClass);
      m_classes.at(m_classes.size() - 1)->AddStudent(s);

      // If at maximum number of classes exit
      if (m_classes.size() >= MAX_CLASSES) {
        cout << "Maximum number of classes entered.\n"
             << "Edit file and start again.\n";
        exit (0);
      }
    }
  }
  
  else {
    // Else if the course does not exist, create course and
    // add student to course
    Class *tempClass = new Class(course, initialSection);
    m_classes.push_back(tempClass);
    m_classes.at(m_classes.size() - 1)->AddStudent(s);

    // If at maximum number of classes exit 
    if (m_classes.size() >= MAX_CLASSES) {
      cout << "Maximum number of classes entered.\n"
	   << "Edit file and start again.\n";
      exit (0);
    }
  }
}
