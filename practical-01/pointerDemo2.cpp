#include <iostream>

using namespace std;

void changeValue(int x, int *y) {
  x += 10;
  *y += 10;
}

int main() {
  int x = 30;
  int y;
  y = x;
  changeValue(x, &y);
  cout << x << endl; // `x` is still 30, but `y` is 40! Since `changeValue` was
  cout << y << endl; // passed the address to `y`, it had access to its value.
  return 0;
}