#include <cctype>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int subStrCount(string sub, string str);
string tolower(string str);

int main() {
  int K, E;
  int eSet = 0;
  while (cin >> K >> E && cin) {
    eSet++;
    cin.ignore();
    vector<string> keywords;
    keywords.reserve(K);
    vector<pair<string, int>> excuses;
    excuses.reserve(E);
    for (int i = 0; i < K; i++) {
      string temp;
      getline(cin, temp);
      keywords.push_back(temp);
    }
    int maxKeyMatch = 0;
    for (int i = 0; i < E; i++) {
      string temp;
      int keyCount = 0;
      getline(cin, temp);
      for (int j = 0; j < K; j++) {
        keyCount += subStrCount(keywords[j], tolower(temp));
      }
      excuses.push_back(make_pair(temp, keyCount));
      if (keyCount > maxKeyMatch)
        maxKeyMatch = keyCount;
    }

    cout << "Excuse Set #" << eSet << endl;
    for (int i = 0; i < excuses.size(); i++) {
      if (excuses[i].second == maxKeyMatch)
        cout << excuses[i].first << endl;
    }
    cout << endl;
  }

  return 0;
}

string tolower(string str) {
  for (int i = 0; i < str.length(); i++) {
    str[i] = tolower(str[i]);
  }
  return str;
}

int subStrCount(string sub, string str) {
  int count = 0;
  int pos = str.find(sub);
  while (pos != string::npos) {
    if ((pos - 1 < 0 || !isalpha(str.at(pos - 1))) &&
        ((pos + sub.length() >= str.length()) ||
         !isalpha(str.at(pos + sub.length())))) {
      count++;
    }
    pos = str.find(sub, pos + 1);
  }
  return count;
}