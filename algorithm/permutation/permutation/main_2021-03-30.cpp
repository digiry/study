#include <iostream>

using namespace std;

const int _N = 3;
const int _R = 2;
int ARR[_N] = { 4,5,6 };
int TEMP[_R] = { 0, };

void PrintArray(int *const pArr, const int length) {
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

void Pertmutation(int *const pArr, const int n, const int r) {
	if (r == 0) {
		PrintArray(TEMP, _R);
		return;
	}

	for (int i = n - 1; i >= 0; i--) {
		Swap(pArr, i, n - 1);
		TEMP[r - 1] = pArr[n - 1];
		Pertmutation(pArr, n - 1, r - 1);
		Swap(pArr, i, n - 1);
	}
}

void PermutationRepeat(int *const pArr, const int n, const int r) {
	if (r == 0) {
		PrintArray(TEMP, _R);
		return;
	}

	for (int i = n - 1; i >= 0; i--) {
		Swap(pArr, i, n - 1);
		TEMP[r - 1] = pArr[n - 1];
		PermutationRepeat(pArr, n, r - 1);
		Swap(pArr, i, n - 1);
	}
}

int main() {
	Pertmutation(ARR, _N, _R);

	cout << "---" << endl;

	PermutationRepeat(ARR, _N, _R);

	return 0;
}