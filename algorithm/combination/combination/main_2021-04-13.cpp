#include <iostream>
#include <iomanip>

using namespace std;

const int _N = 4;
const int _R = 3;
int ARR[_N] = { 4,5,6,7 };
int TEMP[_R] = { 0, };

const int _HN = 3;
const int _HR = 3;
int ARRH[_HN] = { 1,2,3 };
int TEMPH[_HR] = { 0, };

typedef struct _User {
	char mName[20];
	int mWeight;
} User;

User MEMBERS[_N] = {
	{"abc", 60},
	{"def", 83},
	{"ghi", 74},
	{"jkl", 103},
};

int ARR4MEMBERS[_N] = { 0,1,2,3 };
int ARRH4MEMBERS[_HN] = { 0,1,2 };


void PrintArray(const int *const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void PrintArray(const int *const pArr, const User *const pMembers, const int length) {
	for (int i = 0; i < length; i++) {
		cout << "[" << pArr[i] << "]" << pMembers[pArr[i]].mName << ":" << setw(3) << pMembers[pArr[i]].mWeight << ' ';
	}
	cout << endl;
}

void Combination(int *const pArr, const int n, const int r) {
	if (r == 0) {
		PrintArray(TEMP, _R);
		return;
	}
	else if (n < r) {
		return;
	}

	TEMP[r - 1] = pArr[n - 1];
	Combination(pArr, n - 1, r - 1);
	Combination(pArr, n - 1, r);
}

void Combination(int *const pArr, const User *const pMembers, const int n, const int r) {
	if (r == 0) {
		PrintArray(TEMP, pMembers, _R);
		return;
	}
	else if (n < r) {
		return;
	}

	TEMP[r - 1] = pArr[n - 1];
	Combination(pArr, pMembers, n - 1, r - 1);
	Combination(pArr, pMembers, n - 1, r);
}

void CombinationRepeatition(int *const pArr, const int n, const int r) {
	if (r == 0) {
		PrintArray(TEMPH, _HR);
		return;
	}
	else if (n == 0) {
		return;
	}

	TEMPH[r - 1] = pArr[n - 1];
	CombinationRepeatition(pArr, n, r - 1);
	CombinationRepeatition(pArr, n - 1, r);
}

void CombinationRepeatition(int *const pArr, const User *const pMembers, const int n, const int r) {
	if (r == 0) {
		PrintArray(TEMPH, MEMBERS, _HR);
		return;
	}
	else if (n == 0) {
		return;
	}

	TEMPH[r - 1] = pArr[n - 1];
	CombinationRepeatition(pArr, pMembers, n, r - 1);
	CombinationRepeatition(pArr, pMembers, n - 1, r);
}

int main() {
	Combination(ARR, _N, _R);
	cout << "----" << endl;
	Combination(ARR4MEMBERS, MEMBERS, _N, _R);

	cout << "----" << endl;
	CombinationRepeatition(ARRH, _HN, _HR);
	cout << "----" << endl;
	CombinationRepeatition(ARRH4MEMBERS, MEMBERS, _HN, _HR);

	return 0;
}
