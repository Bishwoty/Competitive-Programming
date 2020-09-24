#include <iostream>
#include <vector>
using namespace std;

bool validOrder(vector<int> &t1, vector<int> &t2, vector<int> &out, int pos1,
                int pos2, int outPos, vector<vector<int>> &values);

int main() {
  while (true) {
    int n1, n2;
    cin >> n1 >> n2;
    if (n1 == 0 && n2 == 0) {
      break;
    }
    vector<int> train1;
    vector<int> train2;
    vector<int> trainOut;
    train1.reserve(n1);
    train2.reserve(n2);
    trainOut.reserve(n1 + n2);
    int temp;
    for (int i = 0; i < n1; i++) {
      cin >> temp;
      train1.push_back(temp);
    }
    for (int i = 0; i < n2; i++) {
      cin >> temp;
      train2.push_back(temp);
    }
    for (int i = 0; i < n1 + n2; i++) {
      cin >> temp;
      trainOut.push_back(temp);
    }
    vector<vector<int>> values(n1 + 1, vector<int>(n2 + 1, -1));
    if (!validOrder(train1, train2, trainOut, 0, 0, 0, values)) {
      cout << "not ";
    }
    cout << "possible" << endl;
  }
  return 0;
}

bool validOrder(vector<int> &t1, vector<int> &t2, vector<int> &out, int pos1,
                int pos2, int outPos, vector<vector<int>> &values) {

  if (outPos >= out.size()) {
    return true;
  }

  if (values[pos1][pos2] != -1)
    return values[pos1][pos2];

  if (pos1 < t1.size() && t1[pos1] == out[outPos]) {
    if (validOrder(t1, t2, out, pos1 + 1, pos2, outPos + 1, values)) {
      values[pos1][pos2] = 1;
      return true;
    }
  }
  if (pos2 < t2.size() && t2[pos2] == out[outPos]) {
    if (validOrder(t1, t2, out, pos1, pos2 + 1, outPos + 1, values)) {
      values[pos1][pos2] = 1;
      return true;
    }
  }
  values[pos1][pos2] = 0;
  return false;
}