#include <iostream>
#include <iomanip>

using namespace std;

const int LENGTH = 14;
//int ARR[LENGTH] = { 0,4,2,2,0,0,1,1,0,1,0,2,4,2 };
int ARR[LENGTH] = { 0, };

typedef struct _User {
	char mName[20];
	int mWeight;
} User;

User MEMBERS[LENGTH] = {
	{"a", 0},
	{"b", 4},
	{"c", 2},
	{"d", 2},
	{"e", 0},
	{"f", 0},
	{"g", 1},
	{"h", 1},
	{"i", 0},
	{"j", 1},
	{"k", 0},
	{"l", 2},
	{"m", 4},
	{"n", 2},
};

void PrintArray(const int *const pArr, const User *const pMembers, const int length) {
	for (int i = 0; i < length; i++) {
		cout << "[" << setw(2) << setfill(' ') << pArr[i] << "] " << pMembers[pArr[i]].mName << ": " << pMembers[pArr[i]].mWeight << endl;
	}
}

void CountingSort(int *const pArr, const User *const pMembers, const int length) {
	const int COUNTS_LENGTH = 10;
	int counts[COUNTS_LENGTH] = { 0, };
	int answers[LENGTH] = { 0, };

	for (int i = 0; i < length; i++) {
		counts[pMembers[pArr[i]].mWeight]++;
	}

	for (int i = 1; i < 10; i++) {
		counts[i] += counts[i - 1];
	}

	for (int i = length - 1; i >= 0; i--) {
		counts[pMembers[pArr[i]].mWeight]--;
		answers[counts[pMembers[pArr[i]].mWeight]] = pArr[i];
	}

	for (int i = 0; i < length; i++) {
		pArr[i] = answers[i];
	}
}

int main() {
	for (int i = 0; i < LENGTH; i++) {
		ARR[i] = i;
	}
	PrintArray(ARR, MEMBERS, LENGTH);
	cout << "---" << endl;

	CountingSort(ARR, MEMBERS, LENGTH);
	PrintArray(ARR, MEMBERS, LENGTH);

	return 0;
}
