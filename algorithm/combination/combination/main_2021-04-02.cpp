#include <iostream>

using namespace std;

const int _N = 4;
const int _R = 3;
int ARR[_N] = { 4,5,6,7 };
int TEMP[_R] = { 0, };

int ARR4DUPL[_R] = { 1,2,3 };

void PrintArray(const int *const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void Combination(int *const pArr, const int n, const int r) {
	if (r == 0) {
		PrintArray(TEMP, _R);
	}
	else if (n < r) {
		return;
	}
	else {
		TEMP[r - 1] = pArr[n - 1];
		Combination(pArr, n - 1, r - 1);
		Combination(pArr, n - 1, r);
	}

}

void CombinatinoDuplicated(int *const pArr, const int n, const int r) {
	if (r == 0) {
		PrintArray(TEMP, _R);
	}
	else if (n == 0) {
		return;
	}
	else {
		TEMP[r - 1] = pArr[n - 1];
		CombinatinoDuplicated(pArr, n, r - 1);
		CombinatinoDuplicated(pArr, n - 1, r);
	}
}

int main() {
	Combination(ARR, _N, _R);
	cout << "----" << endl;
	CombinatinoDuplicated(ARR4DUPL, _R, _R);

	return 0;
}