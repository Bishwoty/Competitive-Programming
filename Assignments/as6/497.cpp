#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
  int cases;
  cin >> cases;
  cin.ignore();
  cin.ignore();
  for (int caseNum = 1; caseNum <= cases; caseNum++) {
    vector<int> missles;
    while (true) {
      string input;
      getline(cin, input);
      if (input == "")
        break;
      missles.push_back(stoi(input));
    }
    int bestEndpoint = 0;
    vector<pair<int, int>> len(missles.size());
    for (int i = 0; i < len.size(); i++) {
      int best = 1;
      int pos = i;
      for (int j = i - 1; j >= 0; j--) {
        if (missles[j] < missles[i] && len[j].first >= best) {
          best = len[j].first + 1;
          pos = j;
        }
      }
      len[i] = make_pair(best, pos);
      if (best > len[bestEndpoint].first)
        bestEndpoint = i;
    }
    /*
    cout << "len: ";
    for (auto i : len) {
      cout << i.first << ' ';
    }
    cout << endl << "bestEndpoint: " << bestEndpoint << endl;
    */
    vector<int> sequence;
    sequence.reserve(len[bestEndpoint].second);
    for (int i = bestEndpoint; true; i = len[i].second) {
      sequence.push_back(missles[i]);
      if (len[i].second == i)
        break;
    }

    cout << "Max hits: " << len[bestEndpoint].first << endl;
    for (int i = sequence.size() - 1; i >= 0; i--) {
      cout << sequence[i] << endl;
    }

    if (caseNum < cases)
      cout << endl;
  }
  return 0;
}