#include "Stack.h"

using namespace std;

Stack::Stack() { this->topNode = nullptr; }

Stack::~Stack() { delete this->topNode; }

bool Stack::isEmpty() { return this->topNode == nullptr; }

bool Stack::push(ItemType &item) {
  this->topNode = new Node{item, this->topNode};
  return true;
}

bool Stack::pop() {
  ItemType *item;
  bool result = this->pop(*item);
  delete item;
  return result;
}

bool Stack::pop(ItemType &item) {
  if (this->topNode == nullptr) {
    return false;
  }

  Node *oldNode = this->topNode;
  item = oldNode->item;

  this->topNode = this->topNode->next;

  oldNode->next = nullptr;
  delete oldNode;
}
