#include <iostream>

using namespace std;

int ARR[] = { 3,2,5,1,4 };

void PrintArray(int* const pArr, const int length) {
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
		int min_index = i;
		for (int j = i + 1; j < length; j++) {
			if (pArr[min_index] > pArr[j]) {
				min_index = j;
			}
		}
		Swap(pArr, min_index, i);
	}
}

int main() {
	int length = sizeof(ARR) / sizeof(ARR[0]);
	PrintArray(ARR, length);
	SelectionSort(ARR, length);
	PrintArray(ARR, length);

	return 0;
}
