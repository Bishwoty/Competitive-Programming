#include <iostream>
using namespace std;

int main() {
  long has = 0, opp = 0;
  while (cin >> has >> opp && cin) {
    cout << abs(opp - has) << endl;
  }
  return 0;
}