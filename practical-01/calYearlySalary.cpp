#include <iostream>

#include "Employee.h"

using namespace std;

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
