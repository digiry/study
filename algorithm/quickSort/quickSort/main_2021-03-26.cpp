#include <iostream>

using namespace std;

int ARR[] = { 42,89,63,12,94,27,78,3,50,36 };

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

int Partition(int* const pArr, const int left, const int right) {
	int i = left - 1;
	int j = left;
	int pv = (left + right) >> 1;

	while (j <= right) {
		if (pArr[j] < pArr[pv]) {
			i++;
			Swap(pArr, i, j);
			if (i == pv) {
				pv = j;
			}
		}
		j++;
	}
	Swap(pArr, i + 1, pv);

	return i + 1;
}

void QuickSort(int* const pArr, const int left, const int right) {
	cout << "L:" << left << " R:" << right;
	if (left >= right) {
		cout << endl;
		return;
	}

	int pivot = Partition(pArr, left, right);
	cout << " P:" << pivot << endl;
	QuickSort(pArr, left, pivot - 1);
	QuickSort(pArr, pivot + 1, right);
}

int main() {
	const int length = sizeof(ARR) / sizeof(ARR[0]);
	const int left_index = 0;
	const int right_index = length - 1;

	PrintArray(ARR, length);
	QuickSort(ARR, left_index, right_index);
	PrintArray(ARR, length);

	return 0;
}