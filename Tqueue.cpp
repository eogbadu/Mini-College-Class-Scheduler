#ifndef TQUEUE_CPP
#define TQUEUE_CPP

#include <iostream>
#include <cstdlib>
using namespace std;

template <class T, int N>
class Tqueue {
public:
  //Name: Tqueue - Default Constructor
  //Precondition: None (Must be templated)
  //Postcondition: Creates a queue using dynamic array
  Tqueue(); //Default Constructor
  //.Name: Copy Constructor
  //Precondition: Existing Tqueue
  //Postcondition: Copies an existing Tqueue
  Tqueue( const Tqueue<T,N>& x ); //Copy Constructor
  //Name: Destructor
  //Desc: Empties m_data
  //Precondition: Existing Tqueue
  //Postcondition: Destructs existing Tqueue
  ~Tqueue(); //Destructor
  //Name: ClearData
  //Desc: Empties m_data
  //Precondition: Existing Tqueue
  //Postcondition: Empty m_data
  void ClearData();
  //Name: Enqueue
  //Desc: Adds item to the back of queue
  //Precondition: Existing Tqueue
  //Postcondition: Returns true if successful else false
  void Enqueue(T data); //Adds item to queue (to back)
  //Name: Dequeue
  //Desc: Removes item from queue (from front)
  //Precondition: Existing Tqueue
  //Postcondition: Returns true if successful else false
  void Dequeue();
  //Name: Sort
  //Desc: Sorts the contents of the Tqueue
  //NOTE: You may implement to only deal with dereferenced pointers
  //Precondition: Existing Tqueue
  //Postcondition: Contents of Tqueue is sorted (ascending)
  void Sort();
  //Name: IsEmpty
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is empty else 0
  int IsEmpty(); //Returns 1 if queue is empty else 0
  //Name: IsFull
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is full else 0
  int IsFull(); //Returns 1 if queue is full else 0
  //Name: Size
  //Desc: Returns size of queue
  //Precondition: Existing Tqueue
  //Postcondition: Returns size of queue
  int Size() const;
  //Name: Overloaded assignment operator
  //Precondition: Existing Tqueue
  //Postcondition: Sets one Tqueue to same as a second Tqueue using =
  Tqueue<T,N>& operator=(const Tqueue<T,N>& y); //Overloaded assignment operator for queue
  //Name: Overloaded [] operator
  //Precondition: Existing Tqueue
  //Postcondition: Returns object from Tqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from queue
private:
  T* m_data; //Data of the queue (Must be dynamically allocated array)
  int m_front; //Front of the queue
  int m_back; //Back of the queue
};

//**** Add class definition below ****

// Default constructor
template <class T, int N>
Tqueue<T, N>::Tqueue() {
  m_data = new T[N];
  m_front = 0;
  m_back = 0;
}

// Copy constructor
template <class T, int N>
Tqueue<T, N>::Tqueue(const Tqueue<T, N>& x) {
  m_data = new T[x.Size()];
  m_front = 0;
  m_back = 0;
  for (int i = 0; i < x.Size(); i++) {
    m_data[i] = x.m_data[i];
    m_back++;
  }
}

// Destructor
template <class T, int N>
Tqueue<T, N>::~Tqueue() {
  delete [] m_data;
}

// Clear data which is used to empty m_data
template <class T, int N>
void Tqueue<T, N>::ClearData() {
  m_back = 0;
}

// Enqueue which is used to add data to the back of the queue
template <class T, int N>
void Tqueue<T, N>::Enqueue(T data) {
  // If at maximum capacity exit
  if (m_back >= N) {
    cout << "Exceeded capacity in array.\n";
    exit(1);
  }
  else { // If not at maximum capacity add to queue
    m_data[m_back] = data;
    m_back++;
  }
}

// Dequeue is used to remove data from the front of the queue
template <class T, int N>
void Tqueue<T, N>::Dequeue() {
  // If there is nothing to remove exit
  if (m_back == 0) {
    cout << " Underflow \n";
    exit (1);
  }

  T temp;
  // Else remove the first item in the queue
  for (int i = 0; i < m_back - 1; i++) {
    temp = m_data[i + 1];
    m_data[i] = temp;
  }
  
  m_back--;
}

// Sort is used to sort Tqueue
template <class T, int N>
void Tqueue<T, N>::Sort() {
  // Declare Temp variables
  Tqueue<T, N> *temp = new Tqueue;
  Tqueue<T, N> *temp2 = new Tqueue;

  // Copy queue into a temp variable
  for (int j = 0; j < N; j++) {
    temp->m_data[j] = m_data[j];
  }

  // Perform swap in ascending order
  for (int i = 0; i < m_back; i++) {
    for (int j = i + 1; j < m_back; j++) {
      if (m_data[i] > temp->m_data[j]) {
	temp2->m_data[i] = m_data[i];
	m_data[i] = temp->m_data[j];
	m_data[j] = temp2->m_data[i];
	}
    }
     for (int j = 0; j < N; j++) {
       temp->m_data[j] = m_data[j];
     }
  }
  // Delete temp queues
  delete temp;
  delete temp2;
}

// Checks if queue is empty. Returns 1 if empty
template <class T, int N>
int Tqueue<T, N>::IsEmpty() {
  if (m_back == 0)
    return 1;
  else
    return 0;
}

// Checks if queue is full. Returns 1 if full
template <class T, int N>
int Tqueue<T, N>::IsFull() {
  if (m_back >= N) {
    return 1;
  }
  else {    
    return 0;
  }
}

// Returns the size of the queue
template <class T, int N>
int Tqueue<T, N>::Size() const {
  return m_back;
}

// Overloaded assignment operator for Tqueue
template <class T, int N>
Tqueue<T, N>& Tqueue<T, N>::operator=(const Tqueue<T, N>& otherQueue) {
  if (N != otherQueue.Size()) {
    delete [] m_data;
    m_data = new T[otherQueue.Size()];
  }
  
  m_front = otherQueue.m_front;
  m_back = otherQueue.m_back;
  for (int i = 0; i < m_back; i++) {
    m_data[i] = otherQueue.m_data[i];
  }

  return *this;
}

// Overloaded [] operator. Returns object from Tqueue using []
template <class T, int N>
T& Tqueue<T, N>::operator[](int x) {
  if (x >= N) {
    cout << "illegal index used\n";
    exit (0);
  }

  return m_data[x];
}




/*
// To test just Lqueue follow these instructions:
//   1.  Uncomment out int main below
//   2.  make Tqueue
//   3.  ./Tqueue (try valgrind too!)



int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  Tqueue <int, 10> newTQ1;
  //Push 4 nodes into Lqueue
  newTQ1.Enqueue(10);
  newTQ1.Enqueue(40);
  newTQ1.Enqueue(15);
  newTQ1.Enqueue(13);
    newTQ1.Enqueue(16);
  cout << endl;

  cout << "Printing the queue\n";
  for(int i = 0; i < newTQ1.Size(); i++){
    cout << newTQ1[i] << endl;
  }

  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  Tqueue <int, 10> newTQ2(newTQ1);
  //Test Overloaded Assignment Operator
  Tqueue <int, 10> newTQ3;
  newTQ3 = newTQ1;
  cout << endl;

  //Test 3 - Test Dequeue
  cout << "Test 3 - Dequeue" << endl;
  //cout << newTQ1.Dequeue() << endl;
  newTQ1.Dequeue();
  cout << endl;

  cout << "Sorting the list\n";
  newTQ1.Sort();
  
  //Test 4 - Test Overloaded []
  cout << "Test 4 - Test Overloaded []" << endl;
  for(int i = 0; i < newTQ1.Size(); i++){
    cout << newTQ1[i] << endl;
  }

  //Test 5 - Test Size and ClearData
  cout << "Test 5 - Size and ClearData" << endl;
  //Test GetSize()
  cout << "Outputting the size" << endl;
  cout << newTQ1.Size() << endl;
  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newTQ1.ClearData();
  cout << "Outputting the size" << endl;
  cout << newTQ1.Size() << endl;
  cout << endl;
  
  return 0;
}
*/
#endif
