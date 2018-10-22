#include "Employee.h"

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