#include <iostream>

using namespace std;

//int ARR[] = { 42,89,63,12,94,27,78,3,50,36 };
int ARR[] = { 3, 12, 27, 36, 42, 50, 63, 78, 89, 94 };

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
	// int p = right;
	int p = (left + right) >> 1; // pivot을 중앙으로 예상시

	while (j < right) {
		if (pArr[j] < pArr[p]) {
			i++;
			Swap(pArr, i, j);
			// pivot을 중앙으로 예상시
			if (i == p) {
				p = j;
			}
		}
		j++;
	}
	Swap(pArr, i + 1, p);

	return i + 1;
}

void QuickSort(int* const pArr, const int left, const int right) {
	cout << "l:" << left << " r:" << right;
	if (left >= right) {
		cout << endl;
		return;
	}

	int pivot = Partition(pArr, left, right);
	cout << " p:" << pivot << endl;
	QuickSort(pArr, left, pivot - 1);
	QuickSort(pArr, pivot + 1, right);
}

int main() {
	int length = sizeof(ARR) / sizeof(ARR[0]);
	int right_index = length - 1;

	PrintArray(ARR, length);
	QuickSort(ARR, 0, right_index);
	PrintArray(ARR, length);

	return 0;
}
