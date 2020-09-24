// Approach: use two heaps like discussed in class.
// When adding numbers, if smaller than item at current index, put in max heap,
// and move top value to min heap. Otherwise, put in min heap.
// When getting numbers, shift

#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

int main() {
  int K;
  cin >> K;
  for (int q = 0; q < K; q++) {
    int M, N;
    bool shift = false;
    queue<int> data;
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    cin >> M >> N;
    for (int i = 0; i < M; i++) {
      int add;
      cin >> add;
      data.push(add);
    }
    for (int i = 0; i < N; i++) {
      int u;
      cin >> u;
      while (maxHeap.size() + minHeap.size() < u) {
        if (maxHeap.size() + minHeap.size() == 0) {
          maxHeap.push(data.front());
          data.pop();
        } else {
          if (data.front() >= maxHeap.top()) {
            minHeap.push(data.front());
          } else {
            maxHeap.push(data.front());
            minHeap.push(maxHeap.top());
            maxHeap.pop();
          }
          data.pop();
        }
      }
      if (shift) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
      }
      cout << maxHeap.top() << endl;
      shift = true;
    }
    if (q != K - 1)
      cout << endl;
  }

  return 0;
}