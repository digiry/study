#include <iostream>

using namespace std;

const int LENGTH = 7;
int ARR[LENGTH] = { 0, };

typedef struct _User {
	char mName[20];
	int mWeight;
} User;

User MEMBERS[LENGTH] = {
	{"abc", 3},
	{"def", 2},
	{"ghi", 5},
	{"jkl", 1},
	{"mno", 4},
	{"pqr", 73},
	{"stu", 82},
};

void PrintArray(const int *const pArr, const User *const pMembers, const int length) {
	for (int i = 0; i < length; i++) {
		cout << "[" << i << "] " << pMembers[pArr[i]].mName << ": " << pMembers[pArr[i]].mWeight << endl;
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

int Partition(int *const pArr, const User *const pMembers, const int left, const int right) {
	int i = left - 1;
	int j = left;
	int p = (left + right) >> 1;

	while (j <= right) {
		if (pMembers[pArr[j]].mWeight < pMembers[pArr[p]].mWeight) {
			i++;
			Swap(pArr, i, j);
		}
		j++;
	}

	Swap(pArr, i + 1, p);

	return i + 1;
}

void QuickSort(int *const pArr, const User *const pMembers, const int left, const int right) {
	if (left >= right) {
		return;
	}

	int pivot = Partition(pArr, pMembers, left, right);
	QuickSort(pArr, pMembers, left, pivot - 1);
	QuickSort(pArr, pMembers, pivot + 1, right);
}

int main() {
	const int left_index = 0;
	const int right_index = LENGTH - 1;

	for (int i = 0; i < LENGTH; i++) {
		ARR[i] = i;
	}
	PrintArray(ARR, MEMBERS, LENGTH);
	cout << "---" << endl;
	QuickSort(ARR, MEMBERS, left_index, right_index);
	PrintArray(ARR, MEMBERS, LENGTH);

	return 0;
}
