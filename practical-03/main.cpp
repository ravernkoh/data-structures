#include "List.h"
#include <iostream>

using namespace std;

int main() {
  List nameList;
  nameList.add("Alice");
  nameList.add("Jacky");
  nameList.add("Wendy");
  nameList.print();
  nameList.add(1, "Brenda");
  nameList.print();
  nameList.remove(2);
  nameList.print();
  nameList.remove(0);
  nameList.print();
  return 0;
}
