#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

struct node {
  set<node *> edges;
  int color = 0;
};

void connect(node &a, node &b);
bool biColor(vector<node> &graph);

int main() {
  int n, l;
  while (cin >> n) {
    if (n == 0)
      break;
    vector<node> graph(n);
    cin >> l;
    for (int i = 0; i < l; i++) {
      int a, b;
      cin >> a >> b;
      connect(graph[a], graph[b]);
    }
    if (biColor(graph)) {
      cout << "BICOLORABLE." << endl;
    } else {
      cout << "NOT BICOLORABLE." << endl;
    }
  }
  return 0;
}

void connect(node &a, node &b) {
  a.edges.insert(&b);
  b.edges.insert(&a);
}

bool biColor(vector<node> &graph) {
  queue<node *> proccess;
  graph[0].color = 1;
  proccess.push(&graph[0]);
  while (!proccess.empty()) {
    for (auto adjacent : proccess.front()->edges) {
      if (adjacent->color) {
        if (adjacent->color == proccess.front()->color)
          return false;
        else
          continue;
      }
      adjacent->color = (proccess.front()->color == 1) ? 2 : 1;
      proccess.push(adjacent);
    }
    proccess.pop();
  }
  return true;
}