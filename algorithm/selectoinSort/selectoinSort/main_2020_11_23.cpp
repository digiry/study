#include <iostream>

using namespace std;

int ARR[] = { 2,3,5,4,1 };

void Swap(int* arr, int a_index, int b_index) {
	if (a_index == b_index) {
		return;
	}

	arr[a_index] = arr[a_index] ^ arr[b_index];
	arr[b_index] = arr[a_index] ^ arr[b_index];
	arr[a_index] = arr[a_index] ^ arr[b_index];
}

void SelectionSort(int* arr, int length) {
	int i = 0;
	int j = 0;
	int max_i = 0;

	for (i = 0; i < length; i++) {
		max_i = 0;
		for (j = 0; j < (length - i); j++) {
			if (arr[max_i] < arr[j]) {
				max_i = j;
			}
		}
		Swap(arr, max_i, (length - i - 1));
	}
}

void PrintArray(int* arr, int length) {
	for (int i = 0; i < length; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}

int main() {
	int length = sizeof(ARR) / sizeof(ARR[0]);

	SelectionSort(ARR, length);
	PrintArray(ARR, length);

	return 0;
}