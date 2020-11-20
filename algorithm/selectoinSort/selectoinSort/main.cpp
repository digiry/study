#include <iostream>

using namespace std;

int DataArray[] = { 2,3,5,4,1 };

void Swap(int* array, int idx_a, int idx_b) {
	if (idx_a == idx_b) {
		return;
	}
	array[idx_a] = array[idx_a] ^ array[idx_b];
	array[idx_b] = array[idx_a] ^ array[idx_b];
	array[idx_a] = array[idx_a] ^ array[idx_b];
}

void selection_sort(int* array, int length) {
	int i = 0;
	int j = 0;
	int min_value = 0;
	int min_index = 0;

	for (i = 0; i < length; i++) {
		min_index = i;
		for (j = i; j < length; j++) {
			if (array[min_index] > array[j]) {
				min_index = j;
			}
		}
		Swap(array, i, min_index);
	}
}

void print_array(int* array, int length) {
	for (int i = 0; i < length; i++) {
		cout << array[i] << ' ';
	}
}

int main() {
	int length = sizeof(DataArray) / sizeof(DataArray[0]);

	selection_sort(DataArray, length);
	print_array(DataArray, length);

	return 0;
}