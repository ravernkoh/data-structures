#include <fstream>
#include <iostream>
#include <locale>
#include <string>

using namespace std;

struct Product {
  string name;
  int quantity;
  float price;
};

#define NUM_PRODUCTS 4

Product products[NUM_PRODUCTS] = {{"iPhone 7", 10, 1088},
                                  {"Galaxy S7", 10, 999},
                                  {"Xperia Z", 10, 899},
                                  {"Redmi 3S", 10, 299}};

// Adapted from this StackOverflow answer:
// https://stackoverflow.com/a/7304184
struct semicolon_is_space : ctype<char> {
  semicolon_is_space() : ctype<char>(get_table()) {}
  static mask const *get_table() {
    static mask rc[table_size];
    rc[';'] = ctype_base::space;
    rc['\n'] = ctype_base::space;
    return &rc[0];
  }
};

// Adapted from this StackOverflow answer:
// https://stackoverflow.com/a/3418285
void replaceAll(string &str, const string &from, const string &to) {
  if (from.empty()) {
    return;
  }
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

// Writes product information to `product1.txt`.
bool writeToFile1() {
  ofstream product1;
  product1.open("product1.txt");

  if (!product1.is_open()) {
    return false;
  }

  product1.precision(2);
  product1 << fixed;

  for (int i = 0; i < NUM_PRODUCTS; i++) {
    Product product = products[i];
    replaceAll(product.name, " ", "_");
    product1 << product.name << "\t";
    product1 << product.quantity << "\t";
    product1 << product.price;
    product1 << endl;
  }

  product1.close();

  return true;
}

// Reads product information from `product1.txt`, calculates the amounts and
// displays the results.
bool readFromFile1() {
  ifstream product1;
  product1.open("product1.txt");

  if (!product1.is_open()) {
    return false;
  }

  cout << "Name\t\tQty\tPrice\tAmount" << endl;

  for (int i = 0; i < NUM_PRODUCTS; i++) {
    Product product;
    product1 >> product.name;
    product1 >> product.quantity;
    product1 >> product.price;
    cout << product.name << "\t";
    cout << product.quantity << "\t";
    cout << (int)product.price << "\t";
    cout << product.quantity * (int)product.price;
    cout << endl;
  }

  product1.close();

  return true;
}

// Reads product information from `product1.txt`, calculates the amounts and
// writes the results to `transaction1.txt`.
bool readWriteFile1() {
  ifstream product1;
  product1.open("product1.txt");

  if (!product1.is_open()) {
    return false;
  }

  ofstream transaction1;
  transaction1.open("transaction1.txt");

  if (!transaction1.is_open()) {
    return false;
  }

  for (int i = 0; i < NUM_PRODUCTS; i++) {
    Product product;
    product1 >> product.name;
    product1 >> product.quantity;
    product1 >> product.price;
    transaction1 << product.name << "\t";
    transaction1 << product.quantity << "\t";
    transaction1 << (int)product.price << "\t";
    transaction1 << product.quantity * (int)product.price;
    transaction1 << endl;
  }

  product1.close();
  transaction1.close();

  return true;
}

// Writes product information to `product2.txt`.
bool writeToFile2() {
  ofstream product2;
  product2.open("product2.txt");

  if (!product2.is_open()) {
    return false;
  }

  product2.precision(2);
  product2 << fixed;

  for (int i = 0; i < NUM_PRODUCTS; i++) {
    Product product = products[i];
    product2 << product.name << ";";
    product2 << product.quantity << ";";
    product2 << product.price;
    product2 << endl;
  }

  product2.close();

  return true;
}

// Reads product information from `product2.txt`, calculates the amounts and
// writes the results to `transaction2.txt`.
bool readWriteFile2() {
  ifstream product2;
  product2.open("product2.txt");

  if (!product2.is_open()) {
    return false;
  }

  product2.imbue(locale(product2.getloc(), new semicolon_is_space));

  ofstream transaction2;
  transaction2.open("transaction2.txt");

  if (!transaction2.is_open()) {
    return false;
  }

  for (int i = 0; i < NUM_PRODUCTS; i++) {
    Product product;
    product2 >> product.name;
    product2 >> product.quantity;
    product2 >> product.price;
    transaction2 << product.name << ";";
    transaction2 << product.quantity << ";";
    transaction2 << (int)product.price << ";";
    transaction2 << product.quantity * (int)product.price;
    transaction2 << endl;
  }

  product2.close();
  transaction2.close();

  return true;
}

int main() {
  writeToFile1();
  readFromFile1();
  readWriteFile1();
  writeToFile2();
  readWriteFile2();
}