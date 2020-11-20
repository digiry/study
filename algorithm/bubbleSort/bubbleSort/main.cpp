#include <iostream>

using namespace std;

int DataArray[] = { 2,3,5,4,1 };

void swap(int* array, int idx_a, int idx_b) {
	array[idx_a] = array[idx_a] ^ array[idx_b];
	array[idx_b] = array[idx_a] ^ array[idx_b];
	array[idx_a] = array[idx_a] ^ array[idx_b];
}

void bubble_sort(int* array, int length) {
	int i = 0;
	int j = 0;

	for (i = 0; i < length; i++) {
		for (j = 1; j < (length - i + 1); j++) {
			if (array[j - 1] > array[j]) {
				swap(array, j - 1, j);
			}
		}
	}
}

void print_array(int* array, int length) {
	for (int i = 0; i < length; i++) {
		cout << array[i] << ' ';
	}
}

int main() {
	int length = sizeof(DataArray) / sizeof(DataArray[0]);

	bubble_sort(DataArray, length);
	print_array(DataArray, length);

	return 0;
}