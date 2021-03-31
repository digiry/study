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

int MinIndex(int* const pArr, const int begin, const int end) {
	cout << "Begin: i" << begin << "(" << pArr[begin] << ")" << " End: i" << end << "(" << pArr[end] << ")" << endl;
	if (begin == end) {
		cout << " min_index: i" << begin << "(" << pArr[begin] << ")" << endl;
		return begin;
	}

	int prev_min_index = MinIndex(pArr, begin + 1, end);
	

	int min_index = (pArr[begin] < pArr[prev_min_index]) ? begin : prev_min_index;
	cout << " min_index: i" << min_index << "(" << pArr[min_index] << ")" << endl;

	return min_index;
}

void SelectionSortRecur(int *const pArr, const int begin, const int end) {
	if (begin == end) {
		return;
	}
	
	int min_index = MinIndex(pArr, begin, end);

	Swap(pArr, min_index, begin);
	PrintArray(ARR, LENGTH);
	SelectionSortRecur(pArr, begin + 1, end);
}

void SelectionSort(int* const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		int min = i;
		for (int j = i; j < length; j++) {
			if (pArr[min] > pArr[j]) {
				min = j;
			}
		}
		Swap(pArr, min, i);
	}
}

int main() {
	const int BEGIN_INDEX = 0;
	const int END_INDEX = LENGTH - 1;

	PrintArray(ARR, LENGTH);
	SelectionSort(ARR, LENGTH);
	PrintArray(ARR, LENGTH);

	cout << "---" << endl;
	PrintArray(ARR4RECUR, LENGTH);
	SelectionSortRecur(ARR4RECUR, BEGIN_INDEX, END_INDEX);
	PrintArray(ARR4RECUR, LENGTH);

	return 0;
}