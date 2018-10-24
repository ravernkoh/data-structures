#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

class Person {
public:
  Person(string name, string telNo);
  string getName();
  string getTelNo();
  void print();

private:
  string name;
  string telNo;
};

#endif