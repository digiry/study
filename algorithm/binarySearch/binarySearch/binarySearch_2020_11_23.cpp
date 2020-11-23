#include <iostream>

using namespace std;

int ARR[10] = { 1,2,3,4,5,11,12,13,14,15 };

int BinarySearch(const int* arr, const int length, const int key) {
	int l = 0;
	int h = length - 1;
	int m = 0;
	int k_index = -1;

	while (l < h) {
		m = (l + h) >> 1;
		if (arr[m] == key) {
			k_index = m;
			break;
		}
		else if (arr[m] < key) {
			l = m + 1;
		}
		else {
			h = m;
		}
	}

	return k_index;
}

void PrintArray(const int* arr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}

int main() {
	int length = sizeof(ARR) / sizeof(ARR[0]);
	int keys[] = { 12, 11, 10 };
	int key_index = -1;
	int keys_length = sizeof(keys) / sizeof(keys[0]);
	
	PrintArray(ARR, length);

	for (int i = 0; i < keys_length; i++) {

		key_index = BinarySearch(ARR, length, keys[i]);	
		cout << "key[" << keys[i] << "] index: " << key_index << endl;
	}

	return 0;
}
