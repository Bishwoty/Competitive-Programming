// Approach: Sort dimensions, longest is length, medium is width, shortest is
// thickness. Check if it meets the requirements for each mail type one by one

#include <algorithm>
#include <array>
#include <iostream>
using namespace std;

int main() {
  array<double, 3> dim;
  while (cin >> dim[0] >> dim[1] >> dim[2]) {
    if (dim[0] == 0 && dim[1] == 0 && dim[2] == 0)
      break;
    sort(dim.begin(), dim.end());
    if (dim[0] < 0.25 || dim[1] < 90 || dim[2] < 125) {
      cout << "not mailable" << endl;
    } else if (dim[0] <= 7 && dim[1] <= 155 && dim[2] <= 290) {
      cout << "letter" << endl;
    } else if (dim[0] <= 50 && dim[1] <= 300 && dim[2] <= 380) {
      cout << "packet" << endl;
    } else if (2 * (dim[0] + dim[1]) + dim[2] <= 2100) {
      cout << "parcel" << endl;
    } else {
      cout << "not mailable" << endl;
    }
  }
  return 0;
}