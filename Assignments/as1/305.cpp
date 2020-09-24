#include <iostream>
using namespace std;

bool checkM(int k, int m);
int findM(int k);

int main() {
	int k;
	int answers[12];
	for(int i = 1; i < 14; i++) {
		answers[i-1] = findM(i);
	}
	while(true) {
		cin >> k;
		if(k <= 0)
			break;
		cout << answers[k-1] << endl;
	}
	return 0;
}

// k is how many good and bad guys
// m is how many to skip
bool checkM(int k, int m) {
	int alive = 2 * k;
	int index = 0;
	while(alive > k) {
		index = (index + m - 1) % alive;
		if(index < k)
			return false;
		alive--;
	}
	return true;
}

// k is how many good and bad guys
int findM(int k) {
	int m = k + 1;
	while(!checkM(k, m)) {
		m++;
	}
	return m;
}