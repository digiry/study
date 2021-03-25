#include <iostream>

using namespace std;

const int DIGIT_LENGTH = 3;
const int LENGTH = 7;
int ARR[LENGTH] = { 329,457,657,839,436,720,355 };
const int COUNTS_LENGTH = 10;
int COUNTS[COUNTS_LENGTH] = { 0, };
int ANSWERS[LENGTH] = { 0, };

void PrintArray(int* const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void CountingSortByDigit(const int digit, int* const pArr, int* const pAnswers, const int length) {
	int pows[] = { 1,10,100,1000,10000 };
	int bigMask = pows[digit];
	int smallMask = pows[digit - 1];

	for (int i = 0; i < COUNTS_LENGTH; i++) {
		COUNTS[i] = 0;
	}

	for (int i = 0; i < length; i++) {
		int index = pArr[i] % bigMask / smallMask;
		COUNTS[index]++;
	}

	for (int i = 1; i < COUNTS_LENGTH; i++) {
		COUNTS[i] += COUNTS[i - 1];
	}

	for (int i = length - 1; i >= 0; i--) {
		int index = pArr[i] % bigMask / smallMask;
		--COUNTS[index];
		ANSWERS[COUNTS[index]] = pArr[i];
	}
}

void RadixSort(int* const pArr, int* const pAnswers, const int length) {
	for (int digit = 1; digit <= DIGIT_LENGTH; digit++) {
		CountingSortByDigit(digit, pArr, pAnswers, length);

		for (int i = 0; i < length; i++) {
			pArr[i] = pAnswers[i];
		}
		PrintArray(pArr, length);
	}
}

int main() {
	PrintArray(ARR, LENGTH);
	cout << "---" << endl;
	RadixSort(ARR, ANSWERS, LENGTH);
	cout << "---" << endl;
	PrintArray(ARR, LENGTH);

	return 0;
}