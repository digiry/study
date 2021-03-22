#include <iostream>

using namespace std;

int ARR[] = { 3,2,5,1,4 };

void Swap(int* const pArr, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
	pArr[b_index] = pArr[a_index] ^ pArr[b_index];
	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
}

void PrintArray(const int* pArr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void BubbleSort(int* const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < (length - i - 1); j++) {
			if (pArr[j] > pArr[j + 1]) {
				Swap(pArr, j, j + 1);
			}
		}
	}
}

void BubbleSortPro(int* const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < (length - i - 1); j++) {
			if (pArr[j] > pArr[j + 1]) {
				pArr[j] = pArr[j] ^ pArr[j + 1];
				pArr[j + 1] = pArr[j] ^ pArr[j + 1];
				pArr[j] = pArr[j] ^ pArr[j + 1];
			}
		}
	}
}

int main() {
	int length = sizeof(ARR) / sizeof(ARR[0]);

	PrintArray(ARR, length);
	BubbleSort(ARR, length);	
	PrintArray(ARR, length);

	int ARR2[] = { 3,2,5,1,4 };
	length = sizeof(ARR2) / sizeof(ARR2[0]);

	PrintArray(ARR2, length);
	BubbleSortPro(ARR2, length);
	PrintArray(ARR2, length);

	return 0;
}