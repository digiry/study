#include <iostream>

using namespace std;

const int LENGTH = 5;
int ARR[LENGTH] = { 0, };

typedef struct _User {
	char mName[20];
	int mWeight;
} User;

User MEMBERS[LENGTH] = {
	{"abc", 60},
	{"def", 98},
	{"ghi", 72},
	{"jkl", 53},
	{"mno", 103},
};

void PrintArray(const int *const pArr, const User *const pMembers, const int length) {
	for (int i = 0; i < length; i++) {
	 	cout << "[" << pArr[i] << "]" << " " << pMembers[pArr[i]].mName << ": " << pMembers[pArr[i]].mWeight << endl;
	}
}

void Swap(int *const pArr, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
	pArr[b_index] = pArr[a_index] ^ pArr[b_index];
	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
}

void SelectionSort(int *const pArr, const User *const pMembers, const int length) {
	for (int i = 0; i < length; i++) {
		int min = i;
		for (int j = i; j < length; j++) {
			if (pMembers[pArr[min]].mWeight > pMembers[pArr[j]].mWeight) {
				min = j;
			}
		}
		Swap(pArr, min, i);
	}
}

int MinIndex(int* const pArr, const User* const pMembers, const int begin, const int end) {
	if (begin == end) {
		return begin;
	}

	int min = MinIndex(pArr, pMembers, begin + 1, end);

	min = (pMembers[pArr[min]].mWeight < pMembers[pArr[begin]].mWeight) ? min : begin;

	return min;
}

void SelectionSortRecur(int *const pArr, const User *const pMembers, const int begin, const int end) {
	if (begin == end) {
		return;
	}

	int min = MinIndex(pArr, pMembers, begin, end);

	Swap(pArr, begin, min);
	SelectionSortRecur(pArr, pMembers, begin + 1, end);
}

int main() {
	for (int i = 0; i < LENGTH; i++) {
		ARR[i] = i;
	}
	PrintArray(ARR, MEMBERS, LENGTH);

	cout << "----" << endl;
	SelectionSort(ARR, MEMBERS, LENGTH);

	PrintArray(ARR, MEMBERS, LENGTH);

	cout << "Recursion" << endl;

	for (int i = 0; i < LENGTH; i++) {
		ARR[i] = i;
	}
	const int begin = 0;
	const int end = LENGTH - 1;
	PrintArray(ARR, MEMBERS, LENGTH);
	cout << "----" << endl;
	SelectionSortRecur(ARR, MEMBERS, begin, end);
	PrintArray(ARR, MEMBERS, LENGTH);

	return 0;
}