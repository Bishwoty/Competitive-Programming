#include <bitset>
#include <iostream>
#include <map>
using namespace std;

map<char, bitset<10>> notes;

void generateTable();

int main() {
  generateTable();
  int songCount;
  cin >> songCount;
  cin.ignore();
  for (int i = 0; i < songCount; i++) {
    string song;
    int fingerCount[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    getline(cin, song);
    char prevNote = 'Z';
    for (int j = 0; j < song.length(); j++) {
      for (int k = 0; k < 10; k++) {
        if (notes[song[j]][9 - k] && !notes[prevNote][9 - k]) {
          fingerCount[k]++;
        }
      }
      prevNote = song[j];
    }
    for (int j = 0; j < 10; j++) {
      cout << fingerCount[j];
      if (j < 9)
        cout << ' ';
    }
    cout << endl;
  }
  return 0;
}

void generateTable() {
  notes['Z'] = bitset<10>("0000000000"); // Dummy note with no fingers pressed
  notes['c'] = bitset<10>("0111001111");
  notes['d'] = bitset<10>("0111001110");
  notes['e'] = bitset<10>("0111001100");
  notes['f'] = bitset<10>("0111001000");
  notes['g'] = bitset<10>("0111000000");
  notes['a'] = bitset<10>("0110000000");
  notes['b'] = bitset<10>("0100000000");
  notes['C'] = bitset<10>("0010000000");
  notes['D'] = bitset<10>("1111001110");
  notes['E'] = bitset<10>("1111001100");
  notes['F'] = bitset<10>("1111001000");
  notes['G'] = bitset<10>("1111000000");
  notes['A'] = bitset<10>("1110000000");
  notes['B'] = bitset<10>("1100000000");
}