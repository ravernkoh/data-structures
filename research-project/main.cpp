#include <fstream>
#include <iostream>
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

  product1.precision(2);
  product1 << fixed;

  if (!product1.is_open()) {
    return false;
  }

  for (int i = 0; i < NUM_PRODUCTS; i++) {
    Product product = products[i];
    replaceAll(product.name, " ", "_");
    product1 << product.name << "\t";
    product1 << product.quantity << "\t";
    product1 << product.price << "\t";
    product1 << product.quantity * product.price << "\t";
    product1 << endl;
  }

  product1.close();

  return true;
}

int main() { writeToFile1(); }