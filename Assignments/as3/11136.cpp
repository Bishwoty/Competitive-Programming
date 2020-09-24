#include <iostream>
#include <set>
using namespace std;

int main() {
  while (true) {
    multiset<int> urn;
    int days;
    cin >> days;
    if (days <= 0)
      break;
    int64_t cost = 0;
    for (int i = 0; i < days; i++) {
      int k;
      cin >> k;
      for (int j = 0; j < k; j++) {
        int bill;
        cin >> bill;
        urn.insert(bill);
      }
      auto first = urn.begin();
      auto last = --urn.end();
      cost += *last - *first;
      urn.erase(first);
      urn.erase(last);
    }
    cout << cost << endl;
  }
  return 0;
}