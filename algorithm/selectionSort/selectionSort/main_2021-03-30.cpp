#include <iostream>

using namespace std;

int ARR[] = { 3,2,5,1,4 };

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

void SelectionSort(int *const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		int min = i;
		for (int j = i; j < length; j++) {
			if (pArr[min] > pArr[j]) {
				min = j;
			}
		}
		Swap(pArr, min, i);
	}
}

int main() {
	const int length = sizeof(ARR) / sizeof(ARR[0]);

	PrintArray(ARR, length);
	SelectionSort(ARR, length);
	PrintArray(ARR, length);

	return 0;
}