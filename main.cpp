//Sanjana Venkat
//5.26.19
//Hash table
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>

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
void printStudents(struct Student);
Student** addStudent(int & hashsize, Student** studenthash, int newhashsize, Student** newstudenthash);
void deleteStudent(struct Student);
Student** addtoHash(Student* student, int & hashsize, Student** studenthash, int newhashsize, Student** newstudenthash); 
int getHashIndex(int id, int hashsize);
void printHash(int hashsize, Student** studenthash);
Student** doubleHash(int & hashsize, int newhashsize, Student** studenthash, Student** newstudenthash);
void addtoNewHash(Student* current, int hashsize, int newhashsize, Student** studenthash, Student** newstudenthash);
void initializeNewHash(int hashsize, int newhashsize, Student** studenthash, Student** newstudenthash);
void initializeHash(int hashsize, Student** studenthash);

//vector to hold structs of different students
vector<Student*>* studentlist;

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
  if (collisions > 2) {
    //    cout << "Doubling hash" << endl;
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

//function to print students
//prints out all students stored in studentlist
void printStudents(vector <Student*>* studentlist) {
  for (int i = 0; i < studentlist->size(); i++) {
    Student* s = (*studentlist)[i];
    cout << s->firstname << " " << s->lastname << ", " << s->id << ", " << setprecision(3) << s->gpa <<endl;
  }
}

//function to delete a student
//prompts user to enter student id for student to delete
//deletes all data relating to student based on id
void deleteStudent(vector <Student*>* studentlist) {
  int studentid;
  int index;
  bool idexists = false;
  cout << "Enter student id" << endl;
  cin >> studentid;
   for (int i = 0; i < studentlist->size(); i++) {
    Student* s = (*studentlist)[i];
    if (s->id == studentid) {
      index = i;
      idexists = true;
      break;
    }
  }
   if (idexists == true) {
   studentlist->erase(studentlist->begin()+index);
   cout << "Deleted student" << endl;
   }
   //if id doesn't exist in student list, returns this message
   else {
     cout << "ID doesn't exist in student list" << endl;
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

//reads in response of user
void getResponse(char response[10]) {
  bool running = true;
  cout << "Enter ADD, PRINT, DELETE, or QUIT" << endl;
  cin >> response;
  running == true;
}

int main() {
  vector <Student*>* studentlist = new vector<Student*>();
char response[100];
 bool running = true;
 int hashsize = 100;
 int newhashsize;
 Student** studenthash;
 Student** newstudenthash;
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
     else  if (strcmp(response, "DELETE") == 0) {
      deleteStudent(studentlist);
      getResponse(response);
      
      }
    else if (strcmp(response, "QUIT") == 0) {
      cout << "Quitting" << endl;
	return 0;
      }
    else {
      cout << "Enter a valid response" << endl;
      getResponse(response);
    }
  }
    

}

