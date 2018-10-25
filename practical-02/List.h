#ifndef LIST_H
#define LIST_H

#include "Person.h"
#include <string>

using namespace std;

class List {
public:
  List(int cap);

  // Adds a person to the end of the list.
  // PRE  len < cap
  // POST Person added to end of the list.
  void add(Person *person);

  // Removes a person from the specified index.
  // PRE  index < len
  // POST Person removed from list at the specified index.
  bool remove(int index);

  // Returns the person from the specified index.
  // PRE  index < len
  // POST Returns the person at the specified index.
  Person *get(int index);

  // Returns the length of the list.
  // PRE  None.
  // POST Returns the length of the list.
  int length();

private:
  int cap;
  int len;
  Person **people;
  bool valid(int index);
};

#endif