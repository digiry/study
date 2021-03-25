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

void BubbleSort(int* const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length - i - 1; j++) {
			if (pArr[j] > pArr[j + 1]) {
				Swap(pArr, j, j + 1);
			}
			PrintArray(pArr, length);
		}
	}
}

int main() {
	int length = sizeof(ARR) / sizeof(ARR[0]);

	PrintArray(ARR, length);
	cout << "-----" << endl;
	BubbleSort(ARR, length);
	cout << "-----" << endl;
	PrintArray(ARR, length);

	return 0;
}