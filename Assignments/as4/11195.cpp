#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

bool collision(int x, int y, int size);
void set(int x, int y, int size);
int findSolutions(int row, vector<pair<int, int>> &badSquares, int size);

vector<int> c;
vector<int> dr;
vector<int> dl;

int main() {
  int caseNum = 0;
  while (true) {
    caseNum++;
    c.clear();
    dr.clear();
    dl.clear();
    int size;
    cin >> size;
    if (size == 0)
      break;
    vector<pair<int, int>> badSquares;
    for (int i = 0; i < size; i++) {
      string line;
      cin >> line;
      for (int j = 0; j < size; j++) {
        if (line.at(j) == '*') {
          badSquares.push_back(make_pair(j, i));
        }
      }
    }

    c.resize(size, 0);
    dr.resize(size * 2, 0);
    dl.resize(size * 2, 0);
    cout << "Case " << caseNum << ": " << findSolutions(0, badSquares, size)
         << endl;
  }
  return 0;
}

bool collision(int x, int y, int size) {
  if (c[x] || dl[x - y + size] || dr[x + y])
    return true;
  return false;
}

void set(int x, int y, int val, int size) {
  c[x] = val;
  dl[x - y + size] = val;
  dr[x + y] = val;
}

int findSolutions(int row, vector<pair<int, int>> &badSquares, int size) {
  int counter = 0;
  for (int i = 0; i < size; i++) {
    if (collision(i, row, size))
      continue;
    if (find(badSquares.begin(), badSquares.end(), make_pair(i, row)) !=
        badSquares.end())
      continue;
    set(i, row, 1, size);
    if (row == size - 1) {
      counter++;
    } else {
      counter += findSolutions(row + 1, badSquares, size);
    }
    set(i, row, 0, size);
  }
  return counter;
}