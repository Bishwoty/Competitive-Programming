#include <iostream>
using namespace std;

bool slump(string s);
bool slimp(string s);
bool slurpy(string s);

int main() {
  int cases;
  cin >> cases;
  cout << "SLURPYS OUTPUT" << endl;
  for (int caseNum = 0; caseNum < cases; caseNum++) {
    string word;
    cin >> word;
    if (slurpy(word)) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
  cout << "END OF OUTPUT" << endl;
  return 0;
}

bool slump(string s) {
  if (s.length() < 3) {
    return false;
  }
  if ((s[0] != 'D' && s[0] != 'E') || s[1] != 'F') {
    return false;
  }
  int pos = 2;
  while (s[pos] == 'F') {
    pos++;
    if (pos >= s.length()) {
      return false;
    }
  }
  return (pos == s.length() - 1 && s[pos] == 'G') || slump(s.substr(pos));
}

bool slimp(string s) {
  if (s.length() < 2) {
    return false;
  }
  if (s[0] != 'A') {
    return false;
  }
  if (s.length() == 2 && s[1] == 'H') {
    return true;
  }
  if (s[1] == 'B') {
    return s[s.length() - 1] == 'C' && slimp(s.substr(2, s.length() - 3));
  } else {
    return s[s.length() - 1] == 'C' && slump(s.substr(1, s.length() - 2));
  }
}

bool slurpy(string s) {
  for (int i = 2; i < s.length() - 2; i++) {
    if (slimp(s.substr(0, i)) && slump(s.substr(i))) {
      return true;
    }
  }
  return false;
}