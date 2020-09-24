#include <iostream>
#include <vector>
using namespace std;

vector<int> denom = {1, 5, 10, 25, 50};
vector<vector<int>> computed(7490, vector<int>(5, -1));

int comb(int amount, int coins);

int main() {
  int amount;
  while (cin >> amount) {
    cout << comb(amount, 4) << endl;
  }
  return 0;
}

int comb(int amount, int coins) {
  if (amount == 0)
    return 1;
  if (coins == 0)
    return 1;
  if (computed[amount][coins] >= 0)
    return computed[amount][coins];
  int total = 0;
  for (int i = 0; i <= amount / denom[coins]; i++) {
    total += comb(amount - (i * denom[coins]), coins - 1);
  }
  computed[amount][coins] = total;
  return total;
}