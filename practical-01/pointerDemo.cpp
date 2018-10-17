#include <iostream>

using namespace std;

int main() {
  int value1 = 200000;
  int value2;
  int *ptr;
  ptr = &value1;
  cout << *ptr << endl;
  value2 = *ptr;
  cout << value2 << endl; // It's the same as `value1`!
  cout << &value1 << endl;
  cout << ptr << endl; // Yes, because `ptr` is still pointing to `value1`.
  ptr = &value2;
  *ptr += 2000;
  cout << value1 << endl; // `value1` was not affected...
  cout << value2 << endl; // but `value2` was!
  return 0;
}
