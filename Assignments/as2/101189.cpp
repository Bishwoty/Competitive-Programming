#include <iostream>
using namespace std;

int nearbyBombs(char **field, int x, int y, int n, int m);

int main() {
  int m, n, fieldNum = 0;
  bool first = true;
  while (cin >> n >> m) {
    if (n == 0 || m == 0)
      break;
    fieldNum++;
    char **field;
    field = new char *[n];
    for (int i = 0; i < n; i++) {
      field[i] = new char[m];
    }
    cin.ignore();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin.get(field[i][j]);
      }
      cin.ignore();
    }
    if (first) {
      first = false;
    } else {
      cout << endl;
    }
    cout << "Field #" << fieldNum << ":" << endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (field[i][j] != '*') {
          cout << nearbyBombs(field, i, j, n, m);
        } else {
          cout << '*';
        }
      }
      cout << endl;
    }
    // cout << endl;
    for (int i = 0; i < n; i++) {
      delete field[i];
    }
    delete field;
  }
  return 0;
}

int nearbyBombs(char **field, int x, int y, int n, int m) {
  int count = 0;
  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      if (i >= 0 && i < n && j >= 0 && j < m) {
        if (field[i][j] == '*')
          count++;
      }
    }
  }
  return count;
}