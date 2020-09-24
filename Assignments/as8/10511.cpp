#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

struct Edge;
typedef list<Edge>::iterator EdgeIter;

struct Edge {
  int to;
  int cap;
  int flow;
  bool is_real;
  EdgeIter partner;

  Edge(int t, int c, bool real = true)
      : to(t), cap(c), flow(0), is_real(real){};

  int residual() const { return cap - flow; }
};

struct Graph {
  list<Edge> *nbr;
  int num_nodes;
  Graph(int n) : num_nodes(n) { nbr = new list<Edge>[num_nodes]; }

  ~Graph() { delete[] nbr; }

  // note: this routine adds an edge to the graph with the specified capacity,
  // as well as a residual edge.  There is no check on duplicate edge, so it
  // is possible to add multiple edges (and residual edges) between two
  // vertices
  void add_edge(int u, int v, int cap) {
    nbr[u].push_front(Edge(v, cap));
    nbr[v].push_front(Edge(u, 0, false));
    nbr[v].begin()->partner = nbr[u].begin();
    nbr[u].begin()->partner = nbr[v].begin();
  }
};

void push_path(Graph &G, int s, int t, const vector<EdgeIter> &path, int flow) {
  for (int i = 0; s != t; i++) {
    if (path[i]->is_real) {
      path[i]->flow += flow;
      path[i]->partner->cap += flow;
    } else {
      path[i]->cap -= flow;
      path[i]->partner->flow -= flow;
    }
    s = path[i]->to;
  }
}

// the path is stored in a peculiar way for efficiency: path[i] is the
// i-th edge taken in the path.
int augmenting_path(const Graph &G, int s, int t, vector<EdgeIter> &path,
                    vector<bool> &visited, int step = 0) {
  if (s == t) {
    return -1;
  }
  for (EdgeIter it = G.nbr[s].begin(); it != G.nbr[s].end(); ++it) {
    int v = it->to;
    if (it->residual() > 0 && !visited[v]) {
      path[step] = it;
      visited[v] = true;
      int flow = augmenting_path(G, v, t, path, visited, step + 1);
      if (flow == -1) {
        return it->residual();
      } else if (flow > 0) {
        return min(flow, it->residual());
      }
    }
  }
  return 0;
}

// note that the graph is modified
int network_flow(Graph &G, int s, int t) {
  vector<bool> visited(G.num_nodes);
  vector<EdgeIter> path(G.num_nodes);
  int flow = 0, f;

  do {
    fill(visited.begin(), visited.end(), false);
    if ((f = augmenting_path(G, s, t, path, visited)) > 0) {
      push_path(G, s, t, path, f);
      flow += f;
    }
  } while (f > 0);

  return flow;
}

struct person {
  string name;
  string party;
  vector<string> clubs;
};

int main() {
  int cases;
  cin >> cases;
  cin.ignore();
  cin.ignore();
  for (int caseNum = 1; caseNum <= cases; caseNum++) {
    if (caseNum > 1)
      cout << endl;
    vector<person> data;
    data.reserve(1000);
    map<string, int> people;
    map<string, int> parties;
    map<string, int> clubs;
    map<int, string> clubsR;
    int id = 1;
    while (true) {
      string temp;
      getline(cin, temp);
      if (temp.empty())
        break;
      stringstream s(temp);
      person p;
      s >> p.name >> p.party;
      people[p.name] = id++;
      if (!parties.count(p.party))
        parties[p.party] = id++;
      while (s >> temp) {
        p.clubs.push_back(temp);
        if (!clubs.count(temp)) {
          clubs[temp] = id;
          clubsR[id++] = temp;
        }
      }
      data.push_back(p);
    }
    Graph G(id + 1);
    // create tri-partite graph
    for (int i = 0; i < data.size(); i++) {
      G.add_edge(parties[data[i].party], people[data[i].name], 1);
      for (int j = 0; j < data[i].clubs.size(); j++) {
        G.add_edge(people[data[i].name], clubs[data[i].clubs[j]], 1);
      }
    }
    // connect the source
    for (auto i : parties) {
      G.add_edge(0, i.second, (clubs.size() - 1) / 2);
    }

    // connect the sink
    for (auto i : clubs) {
      G.add_edge(i.second, id, 1);
    }
    int flow = network_flow(G, 0, id);
    if (flow < clubs.size()) {
      cout << "Impossible." << endl;
    } else {
      for (auto p : people) {
        for (auto e : G.nbr[p.second]) {
          if (e.is_real && e.flow) {
            cout << p.first << ' ' << clubsR[e.to] << endl;
          }
        }
      }
    }
  }
  return 0;
}