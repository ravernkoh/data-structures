#include <string>

using namespace std;

class Contact {
public:
  Contact(string name, string contact);
  string getName();
  string getContact();
  void print();

private:
  string name;
  string contact;
};

class List {
public:
  List(int cap);
  void add(Contact contact);
  Contact remove(int index);
  Contact get(int index);
  int length();

private:
  int cap;
  int len;
  Contact *contacts;
  bool valid(int index);
};
