#include <iostream>

using namespace std;

int DataArray[] = { 2,3,5,4,1 };

void swap(int* array, int idx_a, int idx_b) {
	array[idx_a] = array[idx_a] ^ array[idx_b];
	array[idx_b] = array[idx_a] ^ array[idx_b];
	array[idx_a] = array[idx_a] ^ array[idx_b];
}


void print_array(int* array, int length) {
	for (int i = 0; i < length; i++) {
		cout << array[i] << ' ';
	}
}

int main() {
	int length = sizeof(DataArray) / sizeof(DataArray[0]);

	print_array(DataArray, length);

	return 0;
}