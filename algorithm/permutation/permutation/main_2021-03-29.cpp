#include <iostream>

using namespace std;

const int _N = 3;
const int _R = 2;
int ARR[_N] = { 1,2,3 };
int TEMP[_R] = { 0, };

void PrintArray(int* const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void Swap(int *const pArr, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}
	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
	pArr[b_index] = pArr[a_index] ^ pArr[b_index];
	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
}

void Permutation(int* const pArr, const int n, const int r) {

	if (r == 0) {
		PrintArray(TEMP, _R);
	}
	else {
		for (int i = n - 1; i >= 0; i--) {
			Swap(pArr, i, n - 1);
			TEMP[r - 1] = pArr[n - 1];
			Permutation(pArr, n - 1, r - 1);
			Swap(pArr, i, n - 1);
		}
	}
}

int main() {
	Permutation(ARR, _N, _R);

	return 0;
}
