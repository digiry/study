#include <iostream>

using namespace std;

const int LENGTH = 14;
int ARR[LENGTH] = { 0,4,2,2,0,0,1,1,0,1,0,2,4,2 };
const int COUNTS_LENGTH = 10;
int COUNTS[COUNTS_LENGTH] = { 0, };
int ANSWERS[LENGTH] = { 0, };

void PrintArray(int* const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void CountingSort(int* const pArr, int* const pAnswers, const int length) {
	for (int i = 0; i < length; i++) {
		COUNTS[pArr[i]]++;
	}
	cout << "counts array" << endl;
	PrintArray(COUNTS, COUNTS_LENGTH);

	for (int i = 1; i < COUNTS_LENGTH; i++) {
		COUNTS[i] += COUNTS[i - 1];
	}

	cout << "accumulated counts array" << endl;
	PrintArray(COUNTS, COUNTS_LENGTH);

	cout << "become sorted answers" << endl;
	for (int i = length - 1; i >= 0; i--) {
		--COUNTS[pArr[i]];
		pAnswers[COUNTS[pArr[i]]] = pArr[i];
		PrintArray(pAnswers, length);
	}
}

int main() {
	PrintArray(ARR, LENGTH);
	CountingSort(ARR, ANSWERS, LENGTH);
	PrintArray(ANSWERS, LENGTH);

	return 0;
}