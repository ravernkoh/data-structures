#include "List.h"

List::List() {
  this->firstNode = new Node{Item(), nullptr};
  this->size = 0;
}

bool List::add(Item item) {
  Node *cur = this->firstNode;
  while (cur->next != nullptr) {
    cur = cur->next;
  }
  cur->next = new Node{item, nullptr};
  size++;
  return true;
}
