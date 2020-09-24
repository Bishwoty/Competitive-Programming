#include <iostream>
using namespace std;

int main() {
  int N;
  while (true) {
    cin >> N;
    if (N == 0)
      break;
    bool didOutput = false;
    for (int i = 0; i < N; i++) {
      int temp;
      cin >> temp;
      if (temp > 0) {
        if (didOutput)
          cout << ' ';
        cout << temp;
        didOutput = true;
      }
    }
    if (!didOutput)
      cout << '0';
    cout << endl;
  }
  return 0;
}