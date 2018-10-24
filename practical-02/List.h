#ifndef LIST_H
#define LIST_H

#include "Person.h"
#include <string>

using namespace std;

class List {
public:
  List(int cap);
  void add(Person *person);
  bool remove(int index);
  Person *get(int index);
  int length();

private:
  int cap;
  int len;
  Person **people;
  bool valid(int index);
};

#endif