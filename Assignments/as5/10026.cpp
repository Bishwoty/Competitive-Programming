#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct job {
  int jobNum;
  int time;
  int fine;
};

string orderStr(vector<job> &v);

int main() {
  int cases;
  cin >> cases;
  for (int caseNum = 1; caseNum <= cases; caseNum++) {
    int N;
    cin >> N;
    vector<job> jobOrder;
    for (int i = 0; i < N; i++) {
      job temp;
      temp.jobNum = i + 1;
      cin >> temp.time >> temp.fine;
      jobOrder.push_back(temp);
    }
    sort(jobOrder.begin(), jobOrder.end(),
         [](job a, job b) { return (a.fine * b.time) > (b.fine * a.time); });
    cout << orderStr(jobOrder) << endl;
    if (caseNum < cases)
      cout << endl;
  }
  return 0;
}

string orderStr(vector<job> &v) {
  string str;
  for (int i = 0; i < v.size(); i++) {
    str += to_string(v[i].jobNum);
    if (i < v.size() - 1)
      str += ' ';
  }
  return str;
}