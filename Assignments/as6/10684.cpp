#include <iostream>
#include <vector>
using namespace std;

int streak(vector<int> &bets);

int main() {
  while (true) {
    int n;
    cin >> n;
    if (n == 0)
      break;
    vector<int> bets(n);
    for (int i = 0; i < n; i++) {
      cin >> bets[i];
    }
    int myStreak = streak(bets);
    if (myStreak > 0) {
      cout << "The maximum winning streak is " << myStreak << "." << endl;
    } else {
      cout << "Losing streak." << endl;
    }
  }
  return 0;
}

int streak(vector<int> &bets) {
  int best = 0;
  int runningTotal = 0;
  for (int i = 0; i < bets.size(); i++) {
    runningTotal += bets[i];
    if (runningTotal < 0) {
      runningTotal = 0;
    } else if (runningTotal > best) {
      best = runningTotal;
    }
  }
  return best;
}