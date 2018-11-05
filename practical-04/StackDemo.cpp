#include "Stack.h"
#include <iostream>

int main() {
  Stack s;

  s.push("3");
  s.push("4");

  ItemType top;
  s.getTop(top);
  cout << top << endl;

  s.displayInOrderOfInsertion();
  s.pop();
  s.displayInOrderOfInsertion();

  return 0;
}
