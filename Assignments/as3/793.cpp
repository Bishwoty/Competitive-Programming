#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

class UnionFind {
  struct UF {
    int p;
    int rank;
  };

public:
  UnionFind(int n) { // constructor
    howMany = n;
    uf = new UF[howMany];
    for (int i = 0; i < howMany; i++) {
      uf[i].p = i;
      uf[i].rank = 0;
    }
  }

  ~UnionFind() { delete[] uf; }

  int find(int x) { return find(uf, x); } // for client use

  bool merge(int x, int y) {
    int res1, res2;
    res1 = find(uf, x);
    res2 = find(uf, y);
    if (res1 != res2) {
      if (uf[res1].rank > uf[res2].rank) {
        uf[res2].p = res1;
      } else {
        uf[res1].p = res2;
        if (uf[res1].rank == uf[res2].rank) {
          uf[res2].rank++;
        }
      }
      return true;
    }
    return false;
  }

private:
  int howMany;
  UF *uf;

  int find(UF uf[], int x) { // recursive funcion for internal use
    if (uf[x].p != x) {
      uf[x].p = find(uf, uf[x].p);
    }
    return uf[x].p;
  }
};

int main() {
  int cases;
  cin >> cases;
  for (int i = 0; i < cases; i++) {
    int totalComputers, success = 0, fail = 0;
    cin >> totalComputers;
    cin.ignore();
    UnionFind network(totalComputers);
    char command;
    int c1, c2;
    while (true) {
      string line;
      getline(cin, line);
      if (line == "")
        break;
      istringstream s(line);
      s >> command >> c1 >> c2;
      switch (command) {
      case 'c':
        network.merge(c1 - 1, c2 - 1);
        break;
      case 'q':
        if (network.find(c1 - 1) == network.find(c2 - 1)) {
          success++;
        } else {
          fail++;
        }
        break;
      }
    }
    cout << success << ',' << fail << endl;
    if (i < cases - 1)
      cout << endl;
  }
  return 0;
}