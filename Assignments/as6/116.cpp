#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int rows, cols;
  while (cin >> rows >> cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        cin >> matrix[i][j];
      }
    }
    vector<vector<int>> cost(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++) {
      cost[i][cols - 1] = matrix[i][cols - 1];
    }
    for (int j = cols - 2; j >= 0; j--) {
      for (int i = 0; i < rows; i++) {
        cost[i][j] = matrix[i][j] +
                     min(cost[i][j + 1], min(cost[(i - 1 + rows) % rows][j + 1],
                                             cost[(i + 1) % rows][j + 1]));
      }
    }
    /*
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        cout << setw(3) << cost[i][j];
      }
      cout << endl;
    }
    */
    int currRow = 0;
    int bestCost = cost[0][0];
    for (int i = 1; i < rows; i++) {
      if (cost[i][0] < bestCost) {
        currRow = i;
        bestCost = cost[i][0];
      }
    }
    cout << currRow + 1;
    for (int j = 1; j < cols; j++) {
      int up = cost[(currRow - 1 + rows) % rows][j];
      int straight = cost[currRow][j];
      int down = cost[(currRow + 1) % rows][j];
      int best = min(up, min(straight, down));
      // cout << endl << "U:" << up << " S:" << straight << " D:" << down << "
      // Best:" << best << endl;

      if (currRow == 0) {
        if (straight == best) {
          // choose straight
        } else if (down == best) {
          // choose down
          currRow = (currRow + 1) % rows;
        } else {
          // choose up
          currRow = (currRow - 1 + rows) % rows;
        }

      } else if (currRow == rows - 1) {
        if (down == best) {
          // choose down
          currRow = (currRow + 1) % rows;
        } else if (up == best) {
          // choose up
          currRow = (currRow - 1 + rows) % rows;
        } else {
          // choose straight
        }

      } else {
        if (up == best) {
          // choose up
          currRow = (currRow - 1 + rows) % rows;
        } else if (straight == best) {
          // choose straight
        } else {
          // choose down
          currRow = (currRow + 1) % rows;
        }
      }
      cout << ' ' << currRow + 1;
    }
    cout << endl << bestCost << endl;
  }
  return 0;
}