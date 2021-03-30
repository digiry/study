#include <iostream>

using namespace std;

const int DIGITS_LENGTH = 3;
const int LENGTH = 7;
int ARR[LENGTH] = { 329,457,657,839,436,720,355 };

void PrintArray(int *const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void CountingSortByDigit(int *const pArr, const int length, const int digit) {
	const int COUNTS_LENGTH = 10;
	int counts[COUNTS_LENGTH] = { 0, };
	int answers[LENGTH] = { 0 };
	int pows10[] = { 1,10,100,1000,10000 };
	int bigMask = pows10[digit];
	int smallMask = pows10[digit - 1];

	for (int i = 0; i < COUNTS_LENGTH; i++) {
		counts[i] = 0;
	}
	
	for (int i = 0; i < length; i++) {
		int index = pArr[i] % bigMask / smallMask;
		counts[index]++;
	}
	for (int i = 1; i < COUNTS_LENGTH; i++) {
		counts[i] += counts[i - 1];
	}

	for (int i = length - 1; i >= 0; i--) {
		int index = pArr[i] % bigMask / smallMask;
		--counts[index];
		answers[counts[index]] = pArr[i];
	}
	for (int i = 0; i < length; i++) {
		pArr[i] = answers[i];
	}
}

void RadixSort(int *const pArr, const int length, const int digits_length) {
	for (int digit = 1; digit <= digits_length; digit++) {
		CountingSortByDigit(pArr, length, digit);
	}
}

int main() {
	PrintArray(ARR, LENGTH);
	RadixSort(ARR, LENGTH, DIGITS_LENGTH);
	PrintArray(ARR, LENGTH);

	return 0;
}