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

int main() {
	for (int i = 0; i < LENGTH; i++) {
		ARR[i] = i;
	}
	PrintArray(ARR, MEMBERS, LENGTH);

	cout << "----" << endl;
	SelectionSort(ARR, MEMBERS, LENGTH);

	PrintArray(ARR, MEMBERS, LENGTH);

	return 0;
}