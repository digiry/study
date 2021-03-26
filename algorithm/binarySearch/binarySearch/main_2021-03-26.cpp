#include <iostream>

using namespace std;

const int NOT_FOUND = -1;
int ARR[] = { 1,2,3,4,5,11,12,13,14,15 };
int ARR4BOUND[] = { 1,2,3,4,7,7,9,9,10,10 };

void PrintArray(int* const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

int BinarySearch(int* const pArr, const int low, const int high, const int key) {
	int l = low;
	int h = high;
	int found = NOT_FOUND;

	while (l < h) {
		int m = (l + h) >> 1;
		if (pArr[m] == key) {
			found = m;
			break;
		}
		else if (pArr[m] < key) {
			l = m + 1;
		}
		else {
			h = m;
		}
	}

	return found;
}

int BinarySearchLowerBound(int* const pArr, const int low, const int high, const int key) {
	int found = NOT_FOUND;
	int l = low;
	int h = high;
	int m = 0;

	while (l < h) {
		m = (l + h) >> 1;
		if (pArr[m] >= key) {
			h = m;
		}
		else {
			l = m + 1;
		}
	}

	if (pArr[l] == key) {
		found = l;
	}

	return found;
}

int BinarySearchUpperBound(int* const pArr, const int low, const int high, const int key) {
	int found = NOT_FOUND;
	int l = low;
	int h = high;
	int m = 0;

	while (l < h) {
		m = (l + h) >> 1;
		if (pArr[m] <= key) {
			l = m + 1;
		}
		else {
			h = m;
		}
	}

	if (pArr[l - 1] == key) {
		found = l;
	}

	return found;
}

int main() {
	int length = sizeof(ARR) / sizeof(ARR[0]);
	int low_index = 0;
	int high_index = length - 1;
	int key_find = 12;
	int key_notfind = 10;

	cout << "Normal BinarySearch" << endl;
	PrintArray(ARR, length);
	int key = key_find;
	int found = BinarySearch(ARR, low_index, high_index, key);
	cout << "key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not Found: ") << found << endl;
	key = key_notfind;
	found = BinarySearch(ARR, low_index, high_index, key);
	cout << "key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not Found: ") << found << endl;

	cout << endl;
	cout << "LowerBound BinarySearch" << endl;

	length = sizeof(ARR4BOUND) / sizeof(ARR4BOUND[0]);
	low_index = 0;
	high_index = length - 1;
	key_find = 9;
	key_notfind = 5;
	PrintArray(ARR4BOUND, length);
	key = key_find;
	found = BinarySearchLowerBound(ARR4BOUND, low_index, high_index, key);
	cout << "key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not Found: ") << found << endl;
	key = key_notfind;
	found = BinarySearchLowerBound(ARR4BOUND, low_index, high_index, key);
	cout << "key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not Found: ") << found << endl;

	cout << endl;
	cout << "UpperBound BinarySearch" << endl;

	length = sizeof(ARR4BOUND) / sizeof(ARR4BOUND[0]);
	low_index = 0;
	high_index = length - 1;
	key_find = 9;
	key_notfind = 5;
	PrintArray(ARR4BOUND, length);
	key = key_find;
	found = BinarySearchUpperBound(ARR4BOUND, low_index, high_index, key);
	cout << "key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not Found: ") << found << endl;
	key = key_notfind;
	found = BinarySearchUpperBound(ARR4BOUND, low_index, high_index, key);
	cout << "key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not Found: ") << found << endl;

	return 0;
}
