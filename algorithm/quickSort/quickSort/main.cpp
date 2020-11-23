#include <iostream>

using namespace std;

int ARR[10] = { 42,89,63,12,94,27,78,3,50,36 };
//int ARR[10] = { 3, 12, 27, 36, 42, 50, 63, 78, 89, 94 };
int COUNT = 0;

void Swap(int*  const arr, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	arr[a_index] = arr[a_index] ^ arr[b_index];
	arr[b_index] = arr[a_index] ^ arr[b_index];
	arr[a_index] = arr[a_index] ^ arr[b_index];
}

int Partition(int* const arr, const int left, const int right) {
	cout << "[" << COUNT << "] call Partition(" << left << "," << right << ")" << endl;
	int i = left - 1;
	int j = left;
	int m = (left + right) >> 1;
	int p = arr[m];

	while (j < right) {
		if (arr[j] < p) {
			i++;
			Swap(arr, i, j);
		}
		j++;
	}

	Swap(arr, i + 1, j);

	return i + 1;
}

void QuickSort(int* const arr, const int left, const int right) {
	cout << "[" << ++COUNT << "] call QuickSort(" << left << "," << right << ")" << endl;
	if (left >= right) {
		return;
	}

	int p = Partition(arr, left, right);
	cout << "   QuickSort(" << left << "," << right << ") Pivot = " << p << endl;

	QuickSort(arr, left, p - 1);
	QuickSort(arr, p + 1, right);
}

void PrintArray(int* const arr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}

int main() {
	const int length = sizeof(ARR) / sizeof(ARR[0]);

	QuickSort(ARR, 0, length - 1);
	PrintArray(ARR, length);

	return 0;
}