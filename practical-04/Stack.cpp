#include "Stack.h"

using namespace std;

Stack::Stack() { this->topNode = nullptr; }

Stack::~Stack() { delete this->topNode; }

bool Stack::isEmpty() { return this->topNode == nullptr; }

bool Stack::push(ItemType item) {
  this->topNode = new Node{item, this->topNode};
  return true;
}

bool Stack::pop() {
  ItemType item;
  bool result = this->pop(item);
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

  return true;
}

void Stack::getTop(ItemType &item) {
  if (this->topNode == nullptr) {
    return;
  }

  item = this->topNode->item;
}

void Stack::displayInOrder() {
  Stack other;

  while (!this->isEmpty()) {
    ItemType item;
    this->pop(item);
    other.push(item);

    cout << item << endl;
  }

  while (!other.isEmpty()) {
    ItemType item;
    other.pop(item);
    this->push(item);
  }
}

void Stack::displayInOrderOfInsertion() {
  Stack other;

  while (!this->isEmpty()) {
    ItemType item;
    this->pop(item);
    other.push(item);
  }

  while (!other.isEmpty()) {
    ItemType item;
    other.pop(item);
    this->push(item);

    cout << item << endl;
  }
}
