#include <iostream>

using namespace std;

int ARR[] = { 3,2,5,1,4 };

void PrintArray(const int* const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void Swap(int* const pArr, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
	pArr[b_index] = pArr[a_index] ^ pArr[b_index];
	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
}

void SelectionSort(int* const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		int max_index = 0;
		for (int j = 0; j < length - i; j++) {
			if (pArr[max_index] < pArr[j]) {
				max_index = j;
			}
		}
		Swap(pArr, max_index, length - i - 1);
	}
}

void SelectionSortPro(int* const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		int max_index = 0;
		for (int j = 0; j < length - i; j++) {
			if (pArr[max_index] < pArr[j]) {
				max_index = j;
			}
		}
		int target_index = length - i - 1;
		if (max_index != target_index) {
			pArr[max_index] = pArr[max_index] ^ pArr[target_index];
			pArr[target_index] = pArr[max_index] ^ pArr[target_index];
			pArr[max_index] = pArr[max_index] ^ pArr[target_index];
		}
	}
}

int main() {
	int length = sizeof(ARR) / sizeof(ARR[0]);
	PrintArray(ARR, length);
	SelectionSort(ARR, length);
	PrintArray(ARR, length);

	int ARR2[] = { 3,2,5,1,4 };
	length = sizeof(ARR2) / sizeof(ARR2[0]);
	PrintArray(ARR2, length);
	SelectionSortPro(ARR2, length);
	PrintArray(ARR2, length);
	return 0;
}