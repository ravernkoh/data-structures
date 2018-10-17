#include <iostream>
#include <limits>
#include <math.h>

using namespace std;

#define DIGITS 5

int main() {
  int maxN = pow(10, DIGITS) - 1;
  int minN = pow(10, DIGITS - 1);

  while (true) {
    cout << "Enter a " << DIGITS << "-digit integer: ";
    int n;
    cin >> n;

    if (cin.fail() || n < minN || n > maxN) {
      cout << "You have entered an invalid number! Try again." << endl;

      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    for (int i = 0; i < DIGITS; i++) {
      cout << n / (int)pow(10, DIGITS - i - 1) % 10;
      if (i < DIGITS - 1) {
        cout << "   ";
      }
    }
    cout << endl;

    return 0;
  }
}
