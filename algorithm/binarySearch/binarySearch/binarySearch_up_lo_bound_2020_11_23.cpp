#include <iostream>

using namespace std;

int ARR[10] = { 1, 2, 3, 4, 7, 7, 9, 9, 10, 10 };

const int NOT_FOUND = -1;

int BinarySearchUpperBound(const int* arr, const int length, const int key) {
	int l = 0;
	int h = length - 1;
	int m = 0;
	
	while (l < h) {
		m = (l + h) >> 1;
		if (arr[m] <= key) {
			l = m + 1;
		}
		else {
			h = m;
		}
	}

	if (arr[l - 1] != key) {
		return NOT_FOUND;
	}

	return l;
}

int BinarySearchLowerBound(const int* arr, const int length, const int key) {
	int l = 0;
	int h = length - 1;
	int m = 0;

	while (l < h) {
		m = (l + h) >> 1;
		if (arr[m] >= key) {
			h = m;
		}
		else {
			l = m + 1;
		}
	}

	if (arr[l] != key) {
		return NOT_FOUND;
	}
	return l;
}

void PrintArray(const int* arr, int length) {
	for (int i = 0; i < length; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}

int main() {
	int length = sizeof(ARR) / sizeof(ARR[0]);
	int keys[2] = { 9, 8 };
	int keys_length = sizeof(keys) / sizeof(keys[0]);
	int key_index = -1;

	PrintArray(ARR, length);

	for (int i = 0; i < keys_length; i++) {
		key_index = BinarySearchUpperBound(ARR, length, keys[i]);		
		cout << "Upper bound of BinarySearh key[" << keys[i] << "]: key_index: " << key_index << endl;

		key_index = BinarySearchLowerBound(ARR, length, keys[i]);
		cout << "Lower bound of BinarySearh key[" << keys[i] << "]: key_index: " << key_index << endl;
		cout << endl;
	}
	return 0;
}