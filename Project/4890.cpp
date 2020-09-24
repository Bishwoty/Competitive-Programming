#include <iostream>
#include <vector>
using namespace std;

string ordinalOnes[] = {"zeroth",    "first",       "second",     "third",
                        "fourth",    "fifth",       "sixth",      "seventh",
                        "eighth",    "ninth",       "tenth",      "eleventh",
                        "twelfth",   "thirteenth",  "fourteenth", "fifteenth",
                        "sixteenth", "seventeenth", "eighteenth", "nineteenth"};

string cardinalOnes[] = {"zero",    "one",       "two",      "three",
                         "four",    "five",      "six",      "seven",
                         "eight",   "nine",      "ten",      "eleven",
                         "twelve",  "thirteen",  "fourteen", "fifteen",
                         "sixteen", "seventeen", "eighteen", "nineteen"};

// Wierd ones are for debugging
string cardinalTens[] = {"zeroty", "onety", "twenty",  "thirty", "forty",
                         "fifty",  "sixty", "seventy", "eighty", "ninety"};

string sentence = ".tisthe";
vector<int> computed(100001, 0);

string ordinal(int n);
int aronson(int n);

int main() {
  int k;
  while (cin >> k) {
    if (k == 0)
      break;
    cout << aronson(k) << endl;
    // cout << sentence << endl;
  }
  return 0;
}

string ordinal(int n) {
  vector<int> digits(7, 0);
  for (int i = 0; i < 7; i++) {
    digits[i] = n % 10;
    n /= 10;
  }
  // get cardinal version
  string num = "";
  if (digits[6]) {
    num += cardinalOnes[digits[6]] + "million";
  }
  bool thousands = false;
  if (digits[5]) {
    num += cardinalOnes[digits[5]] + "hundred";
    thousands = true;
  }
  if (digits[4] > 1) {
    num += cardinalTens[digits[4]];
    thousands = true;
  }
  if (digits[4] == 1) {
    num += cardinalOnes[digits[4] * 10 + digits[3]];
    thousands = true;
  } else if (digits[3]) {
    num += cardinalOnes[digits[3]];
    thousands = true;
  }
  if (thousands) {
    num += "thousand";
  }
  bool inOrdinal = false;
  if (digits[2]) {
    num += cardinalOnes[digits[2]] + "hundred";
  }
  if (digits[1] > 1) {
    num += cardinalTens[digits[1]];
  }
  if (digits[1] == 1) {
    num += ordinalOnes[digits[1] * 10 + digits[0]];
    inOrdinal = true;
  } else if (digits[0]) {
    num += ordinalOnes[digits[0]];
    inOrdinal = true;
  }

  if (!inOrdinal) {
    if (num[num.length() - 1] == 'y') {
      num[num.length() - 1] = 'i';
      num += 'e';
    }
    num += "th";
  }

  return num;
}

int aronson(int n) {
  if (n == 0)
    return 0;
  if (computed[n])
    return computed[n];
  int offset = aronson(n - 1);
  computed[n] = sentence.find_first_of('t', aronson(n - 1) + 1);
  sentence += ordinal(computed[n]);
  return computed[n];
}