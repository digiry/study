#include <iostream>

using namespace std;

const int LENGTH = 7;
//int ARR[LENGTH] = { 20,15,19,4,13,11,23 };
int ARR[LENGTH] = { 0, };
int TEMP[LENGTH] = { 0, };

typedef struct _User {
	char mName[20];
	int mWeight;
} User;

User MEMBERS[LENGTH] = {
	{"abc", 20},
	{"def", 15},
	{"ghi", 19},
	{"jkl", 4},
	{"mno", 13},
	{"pqr", 11},
	{"stu", 23},
};


void PrintArray(const int *const pArr, const User *const pMembers, const int length) {
	for (int i = 0; i < length; i++) {
		cout << "[" << pArr[i] << "] " << pMembers[pArr[i]].mName << ":" << pMembers[pArr[i]].mWeight << endl;
	}
}

void Merge(int *const pArr, const User *const pMembers, const int left, const int mid, const int right) {
	int i = left;
	int j = mid + 1;
	int t_index = 0;

	while (i <= mid && j <= right) {
		if (pMembers[pArr[i]].mWeight <= pMembers[pArr[j]].mWeight) {
			TEMP[t_index++] = pArr[i++];
		}
		else {
			TEMP[t_index++] = pArr[j++];
		}
	}

	while (i <= mid) {
		TEMP[t_index++] = pArr[i++];
	}
	while (j <= right) {
		TEMP[t_index++] = pArr[j++];
	}

	for (int k = 0; k < t_index; k++) {
		pArr[left + k] = TEMP[k];
	}
}

void MergeSort(int *const pArr, const User *const pMembers, const int left, const int right) {
	if (left == right) {
		return;
	}

	int mid = (left + right) >> 1;
	MergeSort(pArr, pMembers, left, mid);
	MergeSort(pArr, pMembers, mid + 1, right);
	Merge(pArr, pMembers, left, mid, right);
}

int main() {
	const int left_index = 0;
	const int right_index = LENGTH - 1;
	for (int i = 0; i < LENGTH; i++) {
		ARR[i] = i;
	}
	PrintArray(ARR, MEMBERS, LENGTH);
	cout << "----" << endl;

	MergeSort(ARR, MEMBERS, left_index, right_index);
	PrintArray(ARR, MEMBERS, LENGTH);

	return 0;
}
