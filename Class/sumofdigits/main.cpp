#include <iostream>
#include "functions.cpp"

using std::cout, std::cin, std::endl;

int main() {
  int num = 0;
  cout << "Enter number: ";
  cin >> num;
  int sum = digitsum(num);
  cout << "sum of digits: " << sum << endl;
}