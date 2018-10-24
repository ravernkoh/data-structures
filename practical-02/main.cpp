/**
 * Answers:
 *   1. a. The operations are list, add, remove and search.
 *      b. The operations are size, get, add and remove.
 */

#include "List.h"
#include "Person.h"
#include <iostream>

using namespace std;

void printMenu() {
  cout << "---------------- Main Menu -------------------" << endl;
  cout << "[1] List the phone numbers" << endl;
  cout << "[2] Add a new contact" << endl;
  cout << "[3] Remove a contact" << endl;
  cout << "[4] Search for a phone number" << endl;
  cout << "[0] Exit" << endl;
  cout << "----------------------------------------------" << endl;
}

int inputNumber(string prompt) {
  while (true) {
    cout << prompt;
    int n;
    cin >> n;

    if (cin.fail()) {
      cout << "You have entered an invalid number! Try again." << endl;

      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    return n;
  }
}

string inputString(string prompt) {
  while (true) {
    cout << prompt;
    string s;
    cin >> s;

    if (cin.fail()) {
      cout << "You have entered an invalid string! Try again." << endl;

      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    return s;
  }
}

int main() {
  List list(100);

  while (true) {
    printMenu();
    int n = inputNumber("Enter your option: ");

    switch (n) {
    case 1:
      for (int i = 0; i < list.length(); i++) {
        cout << "(" << i << ") ";
        list.get(i)->print();
      }
      break;
    case 2: {
      string name = inputString("Enter the name: ");
      string phone = inputString("Enter the phone number: ");
      Person *person = new Person(name, phone);
      list.add(person);
    } break;
    case 3: {
      int index = inputNumber("Enter the index: ");
      list.remove(index);
    } break;
    case 4: {
      string phone = inputString("Enter the phone number: ");
      for (int i = 0; i < list.length(); i++) {
        Person *person = list.get(i);
        if (person->getTelNo() != phone) {
          continue;
        }

        cout << "(" << i << ") ";
        list.get(i)->print();
      }
    } break;
    case 0:
      return 0;
    default:
      cout << "You have entered an invalid option! Try again." << endl;
      break;
    }
  }
}
