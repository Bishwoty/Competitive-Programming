// Approach: Create a graph that represents each fuel level up to 100 in each
// city. Connect each fuel level in a city to fuel level +1 with an edge weight
// of the gas price. Connect cities by reducing fuel level with cost 0. Disable
// nodes with fuel leves greater than the tank size by marking them as already
// visited. Run Dijkstra's to find the shortest path.

// Code from dijkstra_sparse.cc
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int to;
  int weight; // can be double or other numeric type
  Edge(int t, int w) : to(t), weight(w) {}
};

typedef vector<Edge>::iterator EdgeIter;

struct Graph {
  vector<Edge> *nbr;
  int num_nodes;
  Graph(int n) : num_nodes(n) { nbr = new vector<Edge>[num_nodes]; }

  ~Graph() { delete[] nbr; }

  // note: There is no check on duplicate edge, so it is possible to
  // add multiple edges between two vertices
  //
  // If this is an undirected graph, be sure to add an edge both
  // ways
  void add_edge(int u, int v, int weight) { nbr[u].push_back(Edge(v, weight)); }
};

/* assume that D and P have been allocated */
void dijkstra(const Graph &G, int src, vector<int> &D, vector<int> &P,
              int maxGas) {
  typedef pair<int, int> pii;

  int n = G.num_nodes;
  vector<bool> used(n, false);

  for (int i = 0; i < G.num_nodes; i += 101) {
    for (int j = maxGas + 1; j < 101; j++) {
      used[i + j] = true;
    }
  }

  priority_queue<pii, vector<pii>, greater<pii>> fringe;

  D.resize(n);
  P.resize(n);
  fill(D.begin(), D.end(), -1);
  fill(P.begin(), P.end(), -1);

  D[src] = 0;
  fringe.push(make_pair(D[src], src));

  while (!fringe.empty()) {
    pii next = fringe.top();
    fringe.pop();
    int u = next.second;
    if (used[u])
      continue;
    used[u] = true;

    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      int v = it->to;
      int weight = it->weight + next.first;
      if (used[v])
        continue;
      if (D[v] == -1 || weight < D[v]) {
        D[v] = weight;
        P[v] = u;
        fringe.push(make_pair(D[v], v));
      }
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  Graph city(101 * n);
  // Index 0-100 are for city 0, 101-201 for city 1, 202-302 for city 2, etc
  for (int i = 0; i < n; i++) {
    // cities
    int gasPrice;
    cin >> gasPrice;
    for (int j = 0; j < 100; j++) {
      city.add_edge(i * 101 + j, i * 101 + j + 1, gasPrice);
    }
  }
  int u, v, d;
  for (int i = 0; i < m; i++) {
    // roads
    cin >> u >> v >> d;
    for (int j = d; j < 101; j++) {
      city.add_edge(u * 101 + j, v * 101 + j - d, 0);
      city.add_edge(v * 101 + j, u * 101 + j - d, 0);
    }
  }

  int queries;
  cin >> queries;
  for (int i = 0; i < queries; i++) {
    int tank, a, b;
    cin >> tank >> a >> b;
    vector<int> D, P;
    dijkstra(city, a * 101, D, P, tank);
    if (D[b * 101] < 0) {
      cout << "impossible";
    } else {
      cout << D[b * 101];
    }
    cout << endl;
  }
  return 0;
}