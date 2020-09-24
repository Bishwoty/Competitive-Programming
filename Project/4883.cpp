#include <iostream>
using namespace std;

int maxClimbers(int maxPitch, int totalClimb, int ropeLength);

int main() {
  while (true) {
    int N;
    cin >> N;
    if (N == 0)
      break;
    int maxPitch = 0, totalClimb = 0;
    for (int i = 0; i < N; i++) {
      int in;
      cin >> in;
      if (in > maxPitch)
        maxPitch = in;
      totalClimb += in;
    }
    cout << maxClimbers(maxPitch, totalClimb, 50) << ' '
         << maxClimbers(maxPitch, totalClimb, 60) << ' '
         << maxClimbers(maxPitch, totalClimb, 70) << endl;
  }
  return 0;
}

int maxClimbers(int maxPitch, int totalClimb, int ropeLength) {
  if (totalClimb * 2 > ropeLength) {
    return 0;
  }
  if (ropeLength < maxPitch) {
    return 0;
  }
  if (ropeLength / maxPitch + 1 < 2) {
    return 0;
  }
  return ropeLength / maxPitch + 1;
}