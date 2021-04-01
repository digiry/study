#include <iostream>

using namespace std;

int ARR[] = { 1,2,3 };

void Powerset(int *const pArr, const int n) {
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			if (1 & (i >> j)) {
				cout << pArr[j] << ' ';
			}
		}
		cout << endl;
	}
}

int main() {
	const int length = sizeof(ARR) / sizeof(ARR[0]);

	Powerset(ARR, length);

	return 0;
}