#include <iostream>

using namespace std;

int ARR[] = { 4,5,6 };


typedef struct _User {
	char mName[20];
	int mWeight;
} User;

const int LENGTH = 3;
User MEMBERS[LENGTH] = {
	{"abc", 60},
	{"def", 83},
	{"ghi", 74},
};

int ARR4MEMBERS[LENGTH] = { 0,1,2 };

void Combination(int *const pArr, const int n) {
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			if (1 & (i >> j)) {
				cout << pArr[j] << ' ';
			}
		}
		cout << endl;
	}
}

void Combination(int *const pArr, const User *const pMembers, const int n) {
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			if (1 & (i >> j)) {
				cout << "[" << pArr[j] << "]" << pMembers[pArr[j]].mName << ":" << pMembers[pArr[j]].mWeight << ' ';
			}
		}
		cout << endl;
	}
}

int main() {
	const int length = sizeof(ARR) / sizeof(ARR[0]);

	Combination(ARR, length);
	cout << "----" << endl;
	Combination(ARR4MEMBERS, MEMBERS, LENGTH);

	return 0;
}
