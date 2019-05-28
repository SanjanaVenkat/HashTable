//Sanjana Venkat
//5.26.19
//Hash table
#include <iostream>
#include <iomanip>
#include <cstring>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//struct for student, holds their full name, student id, and gpa
struct Student {
  char firstname[1000];
  char lastname[1000];
  int id;
  float gpa;
  Student* next;
};

//voids for three main functions of studentlist
Student** addStudent(int & hashsize, Student** studenthash, int newhashsize, Student** newstudenthash);
Student** addtoHash(Student* student, int & hashsize, Student** studenthash, int newhashsize, Student** newstudenthash); 
int getHashIndex(int id, int hashsize);
void printHash(int hashsize, Student** studenthash);
Student** doubleHash(int & hashsize, int newhashsize, Student** studenthash, Student** newstudenthash);
void addtoNewHash(Student* current, int hashsize, int newhashsize, Student** studenthash, Student** newstudenthash);
void initializeNewHash(int hashsize, int newhashsize, Student** studenthash, Student** newstudenthash);
void initializeHash(int hashsize, Student** studenthash);
Student** deleteStudent(int hashsize, Student** studenthash);
Student** removefromHash(int studentid, int hashsize, Student** studenthash);
Student** addRandom(int & hashsize, Student** studenthash, int newhashsize, Student** newstudenthash, int & randomid);

void initializeNewHash(int hashsize, int newhashsize, Student** studenthash, Student** newstudenthash) {
  for (int i = 0; i < newhashsize; i++) {
    newstudenthash[i] = NULL;
  }
}

void addtoNewHash(Student* current, int hashsize, int newhashsize, Student** studenthash, Student** newstudenthash) {
  int index = getHashIndex(current->id, newhashsize);
  if (newstudenthash[index] == NULL) {
    newstudenthash[index] = current;
  }
  else {
    Student* newcurrent = newstudenthash[index];
    while (newcurrent->next != NULL) {
      newcurrent = newcurrent->next;
    }
    newcurrent->next = current;
  }
}


int getHashIndex(int id, int hashsize) {
  int index = id % hashsize;
  return index;
}

Student** addtoHash(Student* student, int & hashsize, Student** studenthash, int newhashsize, Student** newstudenthash) {
    int index = getHashIndex(student->id, hashsize);
    int collisions = 0;
  if (studenthash[index] == NULL) {
      studenthash[index] = student;
    }
  else {
    //cout << "Else" << endl;
    Student* current = studenthash[index];
    collisions++;
    while (current->next != NULL) {
      current = current->next;
      collisions++;
    }
    current->next = student;
  }
  if (collisions >= 3) {
    cout << "Doubling number of slots" << endl;
    studenthash = doubleHash(hashsize, newhashsize, studenthash, newstudenthash);
  }
  return studenthash;
}

void initializeHash(int hashsize, Student** studenthash) {
  for (int i = 0; i < hashsize; i++) {
    studenthash[i] = NULL;
  }
}


Student** addStudent(int & hashsize, Student** studenthash, int newhashsize, Student** newstudenthash) {
  Student* student = new Student();
  cout << "Enter student first name" << endl;
  cin >> student->firstname;
  cout << "Enter student last name" << endl;
  cin >> student->lastname;
  cout << "Enter student ID" << endl;
  cin >> student->id;
  cout << "Enter student GPA" << endl;
  cin >> student->gpa;
 studenthash = addtoHash(student, hashsize, studenthash, newhashsize, newstudenthash);
 return studenthash;
}

Student** addRandom(int & hashsize, Student** studenthash, int newhashsize, Student** newstudenthash, int & randomid) {
  int studentnum;
  cout << "How many students do you want to add?" << endl;
  cin >> studentnum;
  int counter = 0;
  char fileFirst[1000];
  char fileLast[1000];
  int numFirst;
  int numLast;
  int randomF;
  int randomL;
  float randomGPA;
  srand(time(NULL));
  cout << "How many first names are in your first name file?" << endl;
  cin >> numFirst;
  cout << "How many last names are in your last name file?" << endl;
  cin >> numLast;
  cout << "What is the name of your first name file?" << endl;
  cin >> fileFirst;
  cout << "What is the name of your last name file?" << endl;
  cin >> fileLast[1000];
  while (studentnum > counter) {
    randomF = rand() % numFirst;
    randomL = rand() % numLast;
    Student* student = new Student();
    randomGPA = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/4.5));
    student->gpa = randomGPA;
    student->id = randomid;
    char testname [1000] = "test";
    strcpy(student->firstname, testname);
    strcpy(student->lastname, testname);
    studenthash = addtoHash(student, hashsize, studenthash, newhashsize, newstudenthash);
    randomid++;
    counter++;
  }
}


Student** doubleHash(int & hashsize, int newhashsize, Student** studenthash, Student** newstudenthash) {
  newhashsize = hashsize * 2;
  newstudenthash = new Student*[newhashsize];
  initializeNewHash(hashsize, newhashsize, studenthash, newstudenthash);
  for (int i = 0; i < hashsize; i++) {
    Student* current = studenthash[i];
    while (current != NULL) {
      Student* next = current->next;
      current->next = NULL;
      addtoNewHash(current, hashsize, newhashsize, studenthash, newstudenthash);
      current = next;
    }
  }
  //  delete [] studenthash;
  hashsize = newhashsize;
  studenthash = newstudenthash;
  return studenthash;
}

void printHash(int hashsize, Student** studenthash) {
  cout << "Number of slots: " << hashsize << endl;
  cout << "Slot First Last ID GPA" << endl;
  for (int i = 0; i < hashsize; i++) {
    Student* current = studenthash[i];
    while (current != NULL) {
      cout << i << ": " << current->firstname << " " << current->lastname << " " << current->id << " " << setprecision(3) << current->gpa << endl;
      current = current->next;
    }
  }
}

Student** deleteStudent(int hashsize, Student** studenthash) {
  int studentid;
  cout << "Enter the id of the student that you want to delete" << endl;
  cin >> studentid;
  studenthash = removefromHash(studentid, hashsize, studenthash);
  return studenthash;
}

Student** removefromHash(int studentid, int hashsize, Student** studenthash) {
  int index = getHashIndex(studentid, hashsize);
  if (studenthash[index] == NULL) {
    return studenthash;
  }
  Student* current = studenthash[index];
  Student* prev = NULL;
  while (current != NULL) {
    if (current->id == studentid) {
      if (prev != NULL) {
	prev->next = current->next;
      }
      else {
	studenthash[index] = current->next;
      }
      delete current;
      break;
    }
    prev = current;
    current = current->next;
  }
  return studenthash;
}

//reads in response of user
void getResponse(char response[10]) {
  bool running = true;
  cout << "Enter ADD, RANDOM, PRINT, DELETE, or QUIT" << endl;
  cin >> response;
  running == true;
}

int main() {
char response[100];
 bool running = true;
 int hashsize = 100;
 int newhashsize;
 Student** studenthash;
 Student** newstudenthash;
 int randomid = 100000;
 studenthash = new Student*[hashsize];
 initializeHash(hashsize, studenthash);
 getResponse(response);
  while (running == true) {
    if (strcmp(response, "ADD") == 0) {
      studenthash = addStudent(hashsize, studenthash, newhashsize, newstudenthash);
	getResponse(response);
	}
    else if (strcmp(response, "PRINT") == 0)
     {
       printHash(hashsize, studenthash);
      getResponse(response);
           }
    else if (strcmp(response, "RANDOM") == 0) {
      studenthash = addRandom(hashsize, studenthash, newhashsize, newstudenthash, randomid);
      getResponse(response);
    }
     else  if (strcmp(response, "DELETE") == 0) {
       studenthash = deleteStudent(hashsize, studenthash);
       getResponse(response);
      }
    else if (strcmp(response, "QUIT") == 0) {
	return 0;
      }
    else {
      cout << "Enter a valid response" << endl;
      getResponse(response);
    }
  }
    

}

