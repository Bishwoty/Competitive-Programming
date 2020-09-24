#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

void proccess(vector<int> &book, vector<string> &ranges, int maxPage);

int main() {
  while (true) {
    int pages;
    cin >> pages;
    if (pages == 0)
      break;
    vector<int> book(1000, 0);
    cin.ignore();
    string line;
    getline(cin, line);
    istringstream iss(line);

    string tok;
    vector<string> ranges;
    while (getline(iss, tok, ',')) {
      ranges.push_back(tok);
    }
    proccess(book, ranges, pages);
    int sum = 0;
    for (auto page : book) {
      sum += page;
    }
    cout << sum << endl;
  }
  return 0;
}

void proccess(vector<int> &book, vector<string> &ranges, int maxPage) {
  for (auto token : ranges) {
    int pos = token.find("-");
    int first, last;
    if (pos != string::npos) {
      first = stoi(token.substr(0, pos));
      last = stoi(token.substr(pos + 1, token.length()));
    } else {
      first = stoi(token);
      last = first;
    }
    for (int i = first; i <= last && i <= maxPage; i++) {
      book[i - 1] = 1;
    }
  }
}