#include <iostream>

using namespace std;

const int NOT_FOUND = -1;
int ARR[] = { 1,2,3,4,5,11,12,13,14,15 };
int ARR4BOUND[] = { 1,2,3,4,7,7,9,9,10,10 };

int BinarySearch(int *const pArr, const int low, const int high, const int key) {
	int found = NOT_FOUND;
	int l = low;
	int h = high;
	int m = 0;

	while (l < h) {
		m = (l + h) >> 1;
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

int BinarySearchUpperBound(int *const pArr, const int low, const int high, const int key) {
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
	const int low_index = 0;
	int high_index = length - 1;
	int key = -1;
	int key_found = 12;
	int key_notfound = 10;
	int found = NOT_FOUND;

	cout << "BinarySearch()" << endl;
	key = key_found;
	found = BinarySearch(ARR, low_index, high_index, key);
	cout << "Key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not Found: ") << found << endl;
	key = key_notfound;
	found = BinarySearch(ARR, low_index, high_index, key);
	cout << "Key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not Found: ") << found << endl;

	cout << "BinarySearchLowerBound()" << endl;
	length = sizeof(ARR4BOUND) / sizeof(ARR4BOUND[0]);
	high_index = length - 1;
	key_found = 9;
	key_notfound = 8;

	key = key_found;
	found = BinarySearchLowerBound(ARR4BOUND, low_index, high_index, key);
	cout << "Key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not Found: ") << found << endl;
	key = key_notfound;
	found = BinarySearchLowerBound(ARR4BOUND, low_index, high_index, key);
	cout << "Key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not Found: ") << found << endl;

	cout << "BinarySearchUpperBound()" << endl;
	key = key_found;
	found = BinarySearchUpperBound(ARR4BOUND, low_index, high_index, key);
	cout << "Key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not Found: ") << found << endl;
	key = key_notfound;
	found = BinarySearchUpperBound(ARR4BOUND, low_index, high_index, key);
	cout << "Key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not Found: ") << found << endl;

	return 0;
}