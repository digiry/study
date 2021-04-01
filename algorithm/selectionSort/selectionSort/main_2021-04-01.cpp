#include <iostream>

using namespace std;

const int LENGTH = 5;
int ARR[LENGTH] = { 3,2,5,1,4 };
int ARR4RECUR[LENGTH] = { 3,2,5,1,4 };

void PrintArray(int *const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void Swap(int *const pArr, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
	pArr[b_index] = pArr[a_index] ^ pArr[b_index];
	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
}

int MinIndex(int *const pArr, const int begin, const int end) {
	if (begin == end) {
		return begin;
	}

	int min_index = MinIndex(pArr, begin + 1, end);

	min_index = (pArr[begin] < pArr[min_index]) ? begin : min_index;

	return min_index;
}

void SelectionSortRecur(int *const pArr, const int begin, const int end) {
	if (begin == end) {
		return;
	}

	int min_index = MinIndex(pArr, begin, end);
	Swap(pArr, begin, min_index);

	SelectionSortRecur(pArr, begin + 1, end);
}

void SelectionSort(int *const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		int min_index = i;
		for (int j = i; j < length; j++) {
			if (pArr[min_index] > pArr[j]) {
				min_index = j;
			}
		}
		Swap(pArr, i, min_index);
	}
}

int main() {
	const int begin_index = 0;
	const int end_idnex = LENGTH - 1;

	PrintArray(ARR4RECUR, LENGTH);
	SelectionSortRecur(ARR4RECUR, begin_index, end_idnex);
	PrintArray(ARR4RECUR, LENGTH);

	cout << "---" << endl;
	PrintArray(ARR, LENGTH);
	SelectionSort(ARR, LENGTH);
	PrintArray(ARR, LENGTH);

	return 0;
}