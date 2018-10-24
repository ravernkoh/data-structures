#include "Person.h"
#include <iostream>

using namespace std;

Person::Person(string name, string telNo) {
  this->name = name;
  this->telNo = telNo;
}

string Person::getName() { return this->name; }

string Person::getTelNo() { return this->telNo; }

void Person::print() { cout << this->name << ": " << this->telNo << endl; }