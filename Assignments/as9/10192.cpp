#include <iostream>
#include <vector>
using namespace std;

int vacation(string seq1, string seq2);
int longestSubSeq(int i, int j, string seq1, string seq2,
                  vector<vector<int>>& data);

int main() {
  string seq1, seq2;
  int caseNum = 1;
  while (true) {
    getline(cin, seq1);
    if (seq1 == "#") {
      break;
    }
    getline(cin, seq2);
    cout << "Case #" << caseNum << ": you can visit at most "
         << vacation(seq1, seq2) << " cities." << endl;
    caseNum++;
  }
  return 0;
}

int vacation(string seq1, string seq2) {
  vector<vector<int>> data(seq1.length() + 1,
                           vector<int>(seq2.length() + 1, -1));
  return longestSubSeq(seq1.length(), seq2.length(), seq1, seq2, data);
}

int longestSubSeq(int i, int j, string seq1, string seq2,
                  vector<vector<int>>& data) {
  if (data[i][j] < 0) {
    if (i == 0 || j == 0) {
      data[i][j] = 0;
    } else {
      if (seq1[i - 1] == seq2[j - 1]) {
        data[i][j] = longestSubSeq(i - 1, j - 1, seq1, seq2, data) + 1;
      } else {
        data[i][j] = max(longestSubSeq(i - 1, j, seq1, seq2, data),
                         longestSubSeq(i, j - 1, seq1, seq2, data));
      }
    }
  }
  return data[i][j];
}