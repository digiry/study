#include <iostream>

using namespace std;

int ARR[] = { 1,2,3 };

const int LENGTH = 3;
int ARR4MEMBERS = { 0, };

typedef struct _User {
	char mName[20];
	int mWeight;
} User;

User MEMBERS[LENGTH] = {
	{"abc", 82},
	{"def", 60},
	{"ghi", 103},
};

void Powerset(const int *const pArr, const int length) {
	for (int i = 0; i < (1 << length); i++) {
		for (int j = 0; j < length; j++) {
			if (1 & (i >> j)) {
				cout << pArr[j] << ' ';
			}
		}
		cout << endl;
	}
}

void Powerset(const User* const pMembers, const int length) {
	for (int i = 0; i < (1 << length); i++) {
		for (int j = 0; j < length; j++) {
			if (1 & (i >> j)) {
				cout << "[" << j << "]" << pMembers[j].mName << ":" << pMembers[j].mWeight << ' ';
			}
		}
		cout << endl;
	}
}

int main() {
	const int length = sizeof(ARR) / sizeof(ARR[0]);

	Powerset(ARR, length);
	cout << "----" << endl;

	Powerset(MEMBERS, length);

	return 0;
}
