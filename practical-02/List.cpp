#include "List.h"
#include <iostream>
#include <string>

using namespace std;

List::List(int cap) {
  this->cap = cap;
  this->len = 0;
  this->people = new Person *[cap];
}

void List::add(Person *person) { this->people[this->len++] = person; }

bool List::remove(int index) {
  if (!this->valid(index))
    return false;

  delete this->people[index];

  this->len--;
  for (int i = index; i < this->len; i++) {
    this->people[index] = this->people[index + 1];
  }

  return true;
}

Person *List::get(int index) {
  if (!this->valid(index))
    return nullptr;
  return this->people[index];
}

int List::length() { return this->len; }

bool List::valid(int index) { return index >= 0 && index < this->len; }
