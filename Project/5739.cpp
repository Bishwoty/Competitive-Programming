#include <algorithm>
#include <iostream>
#include <set>
#include <string>
using namespace std;

string getUserName(set<string> &db, string userName, int maxlen);

int main() {
  for (int caseNum = 1; true; caseNum++) {
    int names, maxlen;
    cin >> names >> maxlen;
    if (names == 0 && maxlen == 0)
      break;
    cin.ignore();
    set<string> database;
    cout << "Case " << caseNum << endl;
    for (int a = 0; a < names; a++) {
      string input;
      getline(cin, input);
      for_each(input.begin(), input.end(), [](char &c) { c = tolower(c); });
      // Rule 2
      string userName =
          input[0] + input.substr(input.find_last_of(" ") + 1, string::npos);
      for (int i = 0; i < userName.length(); i++) {
        if (!isalnum(userName[i])) {
          userName.erase(i, 1);
          i--;
        }
      }
      // Rule 3
      if (userName.length() > maxlen) {
        userName = userName.substr(0, maxlen);
      }
      cout << getUserName(database, userName, maxlen) << endl;
    }
  }
  return 0;
}

string getUserName(set<string> &db, string userName, int maxlen) {
  if (db.find(userName) == db.end()) {
    db.insert(userName);
    return userName;
  }
  // Rule 4
  if (userName.length() < maxlen) {
    userName += ' ';
  }
  int pos = userName.length() - 1;
  for (char i = '1'; i <= '9'; i++) {
    userName[pos] = i;
    if (db.find(userName) == db.end()) {
      db.insert(userName);
      return userName;
    }
  }
  userName = userName.substr(0, userName.length() - 1);

  // Rule 5
  if (userName.length() > maxlen - 2) {
    userName = userName.substr(0, maxlen - 2);
  }
  for (int i = 10; i <= 99; i++) {
    userName += to_string(i);
    if (db.find(userName) == db.end()) {
      db.insert(userName);
      return userName;
    }
    userName = userName.substr(0, userName.length() - 2);
  }
  return "invalid";
}