#include <iomanip>
#include <iostream>
#include <set>
using namespace std;

int accessPoints(set<double> &houses, double maxDistance);

int main() {
  int cases;
  cin >> cases;
  for (int caseNum = 0; caseNum < cases; caseNum++) {
    int aps, houseNum;
    cin >> aps >> houseNum;
    set<double> houses;
    for (int i = 0; i < houseNum; i++) {
      double address;
      cin >> address;
      houses.insert(address);
    }
    double high = *(--houses.end()), low = 0, mid;
    while (high - low > 0.05) {
      mid = low + (high - low) / 2;
      if (accessPoints(houses, mid) >= aps) {
        low = mid;
      } else {
        high = mid;
      }
    }
    cout << setprecision(1) << fixed << mid << endl;
  }
  return 0;
}

int accessPoints(set<double> &houses, double maxDistance) {
  double range = *houses.begin() + 2 * maxDistance;
  int count = 0;
  for (auto house : houses) {
    if (house > range) {
      count++;
      range = house + 2 * maxDistance;
    }
  }
  return count;
}