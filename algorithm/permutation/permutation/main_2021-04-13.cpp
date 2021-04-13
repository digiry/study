#include <iostream>
#include <iomanip>

using namespace std;

const int _N = 4;
const int _R = 3;
int ARR[_N] = { 4,5,6,7 };
int TEMP[_R] = { 0, };

typedef struct _User {
	char mName[20];
	int mWeight;
} User;

User MEMBERS[_N] = {
	{"abc", 60},
	{"def", 83},
	{"ghi", 72},
	{"jkl", 103},
};

int ARR4MEMBERS[_N] = { 0,1,2,3 };


void PrintArray(const int *const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void PrintArray(const int* const pArr, const User *const pMembers, const int length) {
	for (int i = 0; i < length; i++) {
		cout << "[" << pArr[i] << "]" << pMembers[pArr[i]].mName << ":" << setw(3) << pMembers[pArr[i]].mWeight << ' ';
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

void Permutation(int *const pArr, const int n, const int r) {
	if (r == 0) {
		PrintArray(TEMP, _R);
		return;
	}

	for (int i = n - 1; i >= 0; i--) {
		Swap(pArr, n - 1, i);
		TEMP[r - 1] = pArr[n - 1];
		Permutation(pArr, n - 1, r - 1);
		Swap(pArr, n - 1, i);
	}
}

void Permutation(int* const pArr, const User* const pMembers, const int n, const int r) {
	if (r == 0) {
		PrintArray(TEMP, pMembers, _R);
		return;
	}

	for (int i = n - 1; i >= 0; i--) {
		Swap(pArr, n - 1, i);
		TEMP[r - 1] = pArr[n - 1];
		Permutation(pArr, pMembers, n - 1, r - 1);
		Swap(pArr, n - 1, i);
	}
}

void PermutationRepeatition(int *const pArr, const int n, const int r) {
	if (r == 0) {
		PrintArray(TEMP, _R);
		return;
	}

	for (int i = n - 1; i >= 0; i--) {
		Swap(pArr, n - 1, i);
		TEMP[r - 1] = pArr[n - 1];
		PermutationRepeatition(pArr, n, r - 1);
		Swap(pArr, n - 1, i);
	}
}

void PermutationRepeatition(int *const pArr, const User *const pMembers, const int n, const int r) {
	if (r == 0) {
		PrintArray(TEMP, MEMBERS, _R);
		return;
	}

	for (int i = n - 1; i >= 0; i--) {
		Swap(pArr, n - 1, i);
		TEMP[r - 1] = pArr[n - 1];
		PermutationRepeatition(pArr, pMembers, n, r - 1);
		Swap(pArr, n - 1, i);
	}
}

int main() {
	Permutation(ARR, _N, _R);
	cout << "----" << endl;
	Permutation(ARR4MEMBERS, MEMBERS, _N, _R);

	cout << "----" << endl;
	PermutationRepeatition(ARR, _N, _R);
	cout << "----" << endl;
	PermutationRepeatition(ARR4MEMBERS, MEMBERS, _N, _R);

	return 0;
}
