#include <iostream>

using namespace std;

const int DIGIT_LENGTH = 3;
const int LENGTH = 7;
//int ARR[LENGTH] = { 329,457,657,839,436,720,355 };
int ARR[LENGTH] = { 0, };

typedef struct _User {
	char mName[20];
	char mCode[4];
} User;

User MEMBERS[LENGTH] = {
	{"abc", "329"},
	{"def", "457"},
	{"ghi", "657"},
	{"jkl", "839"},
	{"mno", "436"},
	{"pqr", "720"},
	{"stu", "355"},
};

void PrintArray(const int *const pArr, const User *const pMembers, const int length) {
	for (int i = 0; i < length; i++) {
		cout << "[" << pArr[i] << "] " << pMembers[pArr[i]].mName << ": " << pMembers[pArr[i]].mCode << endl;
	}
	cout << "----" << endl;
}

void CountingSortByDigit(int *const pArr, const User *const pMembers, const int length, const int digit) {
	const int COUNTS_LENGTH = 10;
	int counts[COUNTS_LENGTH] = { 0, };
	int answers[LENGTH] = { 0, };
	int index = 0;

	for (int i = 0; i < COUNTS_LENGTH; i++) {
		counts[i] = 0;
	}

	for (int i = 0; i < length; i++) {
		index = int(pMembers[pArr[i]].mCode[digit] - '0');
		counts[index]++;
	}
	for (int i = 1; i < COUNTS_LENGTH; i++) {
		counts[i] += counts[i - 1];
	}

	for (int i = length - 1; i >= 0; i--) {
		index = int(pMembers[ARR[i]].mCode[digit] - '0');
		--counts[index];
		answers[counts[index]] = ARR[i];
	}

	for (int i = 0; i < LENGTH; i++) {
		ARR[i] = answers[i];
	}
}

void RadixSort(int *const pArr, const User *const pMembers, const int length, const int digit_length) {
	for (int d = digit_length - 1; d >= 0; d--) {
		CountingSortByDigit(pArr, pMembers, length, d);
	}
}

int main() {
	for (int i = 0; i < LENGTH; i++) {
		ARR[i] = i;
	}

	PrintArray(ARR, MEMBERS, LENGTH);
	RadixSort(ARR, MEMBERS, LENGTH, DIGIT_LENGTH);
	PrintArray(ARR, MEMBERS, LENGTH);
	
	return 0;
}
