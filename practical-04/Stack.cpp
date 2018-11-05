#include "Stack.h"

using namespace std;

Stack::Stack() { this->topNode = nullptr; }

Stack::~Stack() { delete this->topNode; }

bool Stack::isEmpty() { return this->topNode == nullptr; }

bool Stack::push(ItemType &item) {
  this->topNode = new Node{item, this->topNode};
  return true;
}