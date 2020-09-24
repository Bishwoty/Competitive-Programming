#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
  int caseNum = 0;
  while (true) {
    caseNum++;
    int n, k1, k2;
    cin >> n >> k1 >> k2;
    if (n == 0)
      break;
    vector<pair<int, int>> prices;
    prices.reserve(n);
    for (int day = 1; day <= n; day++) {
      int dayPrice;
      cin >> dayPrice;
      prices.push_back(make_pair(dayPrice, day));
    }
    sort(prices.begin(), prices.end(), [](pair<int, int> a, pair<int, int> b) {
      if (a.first == b.first) {
        return a.second < b.second;
      } else {
        return a.first < b.first;
      }
    });
    sort(
        prices.begin(), prices.begin() + k1,
        [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });
    sort(
        prices.end() - k2, prices.end(),
        [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });
    cout << "Case " << caseNum << endl;
    for (int i = 0; i < k1; i++) {
      cout << prices.at(i).second << ' ';
    }
    cout << endl;
    for (int i = 0; i < k2; i++) {
      cout << prices.at(prices.size() - 1 - i).second << ' ';
    }
    cout << endl;
  }
  return 0;
}