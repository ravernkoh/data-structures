#include "List.h"
#include <iostream>

using namespace std;

List::List() {
  this->firstNode = new Node{Item(), nullptr};
  this->size = 0;
}

bool List::add(Item item) { return this->add(this->size, item); }

bool List::add(int index, Item item) {
  if (index > this->size) {
    return false;
  }

  Node *cur = this->firstNode;
  while (index-- > 0) {
    cur = cur->next;
  }

  cur->next = new Node{item, cur->next};
  this->size++;

  return true;
}

void List::remove(int index) {
  if (index >= this->size) {
    return;
  }

  Node *cur = this->firstNode;
  while (index-- > 0) {
    cur = cur->next;
  }

  Node *temp = cur->next;
  cur->next = cur->next->next;
  delete temp;
  this->size--;
}

void List::print() {
  cout << "----" << endl;
  Node *cur = this->firstNode;
  while (cur->next != nullptr) {
    cur = cur->next;
    cout << cur->item << endl;
  }
}
