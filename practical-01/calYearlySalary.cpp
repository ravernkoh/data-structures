#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
  string firstName;
  string lastName;
  int salary;

public:
  Employee(string firstName, string lastName, int salary);
  void setFirstName(string firstName);
  string getFirstName();
  void setLastName(string lastName);
  string getLastName();
  void setSalary(int salary);
  int getSalary();
};

Employee::Employee(string firstName, string lastName, int salary) {
  this->firstName = firstName;
  this->lastName = lastName;
  this->salary = salary;
}

void Employee::setFirstName(string firstName) { this->firstName = firstName; }

string Employee::getFirstName() { return this->firstName; }

void Employee::setLastName(string lastName) { this->lastName = lastName; }

string Employee::getLastName() { return this->lastName; }

void Employee::setSalary(int salary) {
  if (salary < 0) {
    this->salary = 0;
    return;
  }
  this->salary = salary;
}

int Employee::getSalary() { return this->salary; }

int main() {
  Employee john("John", "Doe", 5000);
  Employee jane("Jane", "Dee", 7000);

  cout << john.getFirstName() << "'s yearly salary: $" << john.getSalary() * 12
       << endl;
  cout << jane.getFirstName() << "'s yearly salary: $" << jane.getSalary() * 12
       << endl;

  john.setSalary(john.getSalary() * 1.1);
  jane.setSalary(jane.getSalary() * 1.1);

  cout << john.getFirstName() << "'s yearly salary: $" << john.getSalary() * 12
       << endl;
  cout << jane.getFirstName() << "'s yearly salary: $" << jane.getSalary() * 12
       << endl;

  return 0;
}
