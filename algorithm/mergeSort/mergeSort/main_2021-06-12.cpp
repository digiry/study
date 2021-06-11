#include <iostream>

using namespace std;

const int ARR_LENGTH = 7;
int ARR[ARR_LENGTH] = { 20,15,19,4,13,11,23 };
int TEMP[ARR_LENGTH] = { 0, };


void PrintArray(const int* pArr) {
	for (int i = 0; i < ARR_LENGTH; ++i) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void Merge(int* const pArr, const int l, const int m, const int r) {
	int i = l;
	int j = m + 1;
	int t_i = 0;

	while (i <= m && j <= r) {
		if (pArr[i] <= pArr[j]) {
			TEMP[t_i++] = pArr[i++];
		}
		else {
			TEMP[t_i++] = pArr[j++];
		}
	}

	while (i <= m) {
		TEMP[t_i++] = pArr[i++];
	}
	while (j <= r) {
		TEMP[t_i++] = pArr[j++];
	}

	for (register int k = 0; k < t_i; ++k) {
		pArr[l + k] = TEMP[k];
	}
}

void MergeSort(int* const pArr, const int l, const int r) {
	if (l == r) {
		return;
	}

	int m = (l + r) >> 1;
	MergeSort(pArr, l, m);
	MergeSort(pArr, m + 1, r);

	Merge(pArr, l, m, r);
}

int main() {
	const int l = 0;
	const int r = ARR_LENGTH - 1;
	PrintArray(ARR);
	MergeSort(ARR, l, r);
	PrintArray(ARR);

	return 0;
}