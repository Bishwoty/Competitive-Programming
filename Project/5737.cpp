#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int64_t>> values(31, vector<int64_t>(31, -1));

int64_t pills(int whole, int half);

int main() {
  while (true) {
    int size;
    cin >> size;
    if (!(size > 0)) {
      break;
    }
    cout << pills(size, 0) << endl;
  }
  return 0;
}

int64_t pills(int whole, int half) {
  if (values[whole][half] < 0) {
    if (whole + half == 1) {
      values[whole][half] = 1;
    } else {
      int64_t total = 0;
      if (whole > 0) {
        total += pills(whole - 1, half + 1);
      }
      if (half > 0) {
        total += pills(whole, half - 1);
      }
      values[whole][half] = total;
    }
  }
  return values[whole][half];
}