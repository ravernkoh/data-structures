#include "List.h"
#include <iostream>

using namespace std;

int main() {
  List nameList;
  nameList.add("Alice");
  nameList.add("Jacky");
  nameList.add("Wendy");
  cout << endl;
  nameList.print();
  nameList.add(1, "Brenda");
  cout << endl;
  nameList.print();
  return 0;
}
