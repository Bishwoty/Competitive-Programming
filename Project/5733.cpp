#include <iostream>
#include <vector>
using namespace std;

bool same(vector<int> &vec);

int main() {
  int caseNum = 0;
  while (true) {
    caseNum++;
    int size;
    cin >> size;
    if (size == 0)
      break;
    vector<int> list;
    list.reserve(size);
    for (int i = 0; i < size; i++) {
      int temp;
      cin >> temp;
      list.push_back(temp);
    }
    int iterations = 0;
    cout << "Case " << caseNum << ": ";
    while (true) {
      if (same(list)) {
        cout << iterations << " iterations" << endl;
        break;
      }
      iterations++;
      if (iterations > 1000) {
        cout << "not attained" << endl;
        break;
      }
      int first = list.at(0);
      for (int i = 0; i < list.size() - 1; i++) {
        list.at(i) = abs(list.at(i) - list.at(i + 1));
      }
      list.at(list.size() - 1) = abs(list.at(list.size() - 1) - first);
    }
  }
  return 0;
}

bool same(vector<int> &vec) {
  for (int i = 1; i < vec.size(); i++) {
    if (vec.at(0) != vec.at(i))
      return false;
  }
  return true;
}