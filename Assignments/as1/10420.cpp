#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

vector<pair<string, int>> data;
void addLover(string country);

int main() {
  int total;
  cin >> total;
  for (int i = 0; i < total; i++) {
    string country, garbage;
    cin >> country;
    getline(cin, garbage);
    addLover(country);
  }
  sort(data.begin(), data.end(), [](pair<string, int> x, pair<string, int> y) {
    return x.first <= y.first;
  });
  for (int i = 0; i < data.size(); i++) {
    cout << data.at(i).first << ' ' << data.at(i).second << endl;
  }
  return 0;
}

void addLover(string country) {
  for (int i = 0; i < data.size(); i++) {
    if (data.at(i).first == country) {
      data.at(i).second++;
      return;
    }
  }
  data.push_back(make_pair(country, 1));
}