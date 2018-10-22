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