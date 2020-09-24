#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

struct node {
  set<node *> edges;
  bool destination = false;
  int cost = -1;
  void connect(node &a) { edges.insert(&a); }
};

int cost(node *start);
bool valid(vector<vector<char>> &grid, int row, int col);

int m, n;

int main() {
  int caseNum = 1;
  while (cin >> m >> n) {
    if (m == 0 && n == 0)
      break;
    cin.ignore();
    pair<int, int> start;
    vector<vector<char>> grid(m, vector<char>(n));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        cin.get(grid[i][j]);
        if (grid[i][j] == 'S')
          start = make_pair(i, j);
      }
      cin.ignore();
    }

    // row, col, dir, color
    node graph[25][25][4][5];
    for (int row = 0; row < m; row++) {
      for (int col = 0; col < n; col++) {
        if (grid[row][col] != '#') {
          for (int dir = 0; dir < 4; dir++) {
            for (int color = 0; color < 5; color++) {
              if (grid[row][col] == 'T' && color == 0)
                graph[row][col][dir][color].destination = true;
              // turn right
              graph[row][col][dir][color].connect(
                  graph[row][col][(dir + 1) % 4][color]);
              // turn left
              graph[row][col][dir][color].connect(
                  graph[row][col][(dir + 3) % 4][color]);

              // go forward
              switch (dir) {
              case 0:
                if (valid(grid, row - 1, col)) {
                  graph[row][col][dir][color].connect(
                      graph[row - 1][col][dir][(color + 1) % 5]);
                }
                break;
              case 1:
                if (valid(grid, row, col + 1)) {
                  graph[row][col][dir][color].connect(
                      graph[row][col + 1][dir][(color + 1) % 5]);
                }
                break;
              case 2:
                if (valid(grid, row + 1, col)) {
                  graph[row][col][dir][color].connect(
                      graph[row + 1][col][dir][(color + 1) % 5]);
                }
                break;
              case 3:
                if (valid(grid, row, col - 1)) {
                  graph[row][col][dir][color].connect(
                      graph[row][col - 1][dir][(color + 1) % 5]);
                }
                break;
              }
            }
          }
        }
      }
    }
    if (caseNum > 1)
      cout << endl;
    cout << "Case #" << caseNum << endl;
    int time = cost(&graph[start.first][start.second][0][0]);
    if (time < 0) {
      cout << "destination not reachable" << endl;
    } else {
      cout << "minimum time = " << time << " sec" << endl;
    }
    caseNum++;
  }
  return 0;
}

int cost(node *start) {
  queue<node *> proccess;
  start->cost = 0;
  proccess.push(start);
  while (!proccess.empty()) {
    if (proccess.front()->destination)
      return proccess.front()->cost;
    for (auto adjacent : proccess.front()->edges) {
      if (adjacent->cost < 0) {
        adjacent->cost = proccess.front()->cost + 1;
        proccess.push(adjacent);
      }
    }
    proccess.pop();
  }
  return -1;
}

bool valid(vector<vector<char>> &grid, int row, int col) {
  if (row >= m || row < 0 || col >= n || col < 0)
    return false;
  return grid[row][col] != '#';
}