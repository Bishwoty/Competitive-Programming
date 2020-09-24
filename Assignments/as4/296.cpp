#include <iostream>
#include <utility>
#include <vector>
using namespace std;

bool checkAnswer(vector<pair<string, string>> &guesses, const string &answer);

int main() {
  int numCases;
  cin >> numCases;
  for (int caseNum = 1; caseNum <= numCases; caseNum++) {
    int totalGuess;
    cin >> totalGuess;
    vector<pair<string, string>> guesses;
    for (int i = 0; i < totalGuess; i++) {
      string guess, result;
      cin >> guess >> result;
      guesses.push_back(make_pair(guess, result));
    }
    string correct = "";
    for (int i = 0; i < 10000; i++) {
      string answer = to_string(i);
      if (i < 10)
        answer = "000" + answer;
      else if (i < 100)
        answer = "00" + answer;
      else if (i < 1000)
        answer = "0" + answer;
      if (checkAnswer(guesses, answer)) {
        // cout << answer << endl;
        if (correct == "") {
          correct = answer;
        } else {
          correct = "indeterminate";
          break;
        }
      }
    }
    if (correct == "")
      correct = "impossible";
    cout << correct << endl;
  }
  return 0;
}

bool checkAnswer(vector<pair<string, string>> &guesses, const string &answer) {
  // cout << endl << answer << ":\n";
  for (auto g : guesses) {
    string temp = answer;
    string guess = g.first;
    int correct = 0, misplaced = 0;
    for (int digit = 0; digit < 4; digit++) {
      if (g.first[digit] == temp[digit]) {
        correct++;
        temp[digit] = '.';
        guess[digit] = '!';
      }
    }
    for (int digit = 0; digit < 4; digit++) {
      int foundPos = temp.find(guess[digit]);
      if (foundPos != string::npos) {
        misplaced++;
        temp[foundPos] = '.';
      }
    }
    // cout << g.first << ' ' << correct << '/' << misplaced << endl;
    string result = to_string(correct) + '/' + to_string(misplaced);
    if (result != g.second)
      return false;
  }
  return true;
}