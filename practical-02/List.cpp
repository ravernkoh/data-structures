#include "List.h"

#include <iostream>
#include <string>

using namespace std;

Contact::Contact(string name, string contact) {
  this->name = name;
  this->contact = contact;
}

string Contact::getName() {
  return this->name;
}

string Contact::getContact() {
  return this->contact;
}

void Contact::print() {
  cout << this->name << ": " << this->contact << endl;
}

List::List(int cap) {
  this->cap = cap;
  this->len = 0;
  this->contacts = (Contact *)malloc(sizeof(Contact) * this->cap);
}

void List::add(Contact contact) {
  this->contacts[this->len++] = contact;
}

Contact List::remove(int index) {
  if (!this->valid(index)) return Contact("", "");

  Contact contact = this->contacts[index];

  this->len--;
  for (int i = index; i < this->len; i++) {
    this->contacts[index] = this->contacts[index + 1];
  }

  return contact;
}

Contact List::get(int index) {
  if (!this->valid(index)) return Contact("", "");
  return this->contacts[index];
}

int List::length() {
  return this->len;
}

bool List::valid(int index) {
  return index >= 0 && index < this->len;
}