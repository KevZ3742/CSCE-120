#include <bits/stdc++.h>

using namespace std;

int main() {
  double sum = 0;
  double num = 0;
  unsigned int count = 0;
  do {
    cin >> num;
    if (num >= 0) {
      sum += num;
      count++;
    }
  } while (num != -1);

  cout << "average: " << sum/count << endl;
  return 0;
}