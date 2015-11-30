#include <iostream>

using namespace std;

int T;
int N;
int input[30];

void powerset();

int main() {
	int tc;

	cin >> T;
	for (tc = 0; tc < T; tc++) {
		cin >> N;
		for (int idx = 0; idx < N; idx++) {
			cin >> input[idx];
		}
		powerset();
	}

	return 0;
}

void powerset() {
	int last_number = 1 << N;
	int num;
	int bit_idx;
	int sum;

	for (num = 1; num < last_number; num++) {
		sum = 0;
		for (bit_idx = 0; bit_idx < N; bit_idx++) {
			if (num & (1 << bit_idx)) {
				sum += input[bit_idx];
			}
		}
		if (sum == 0) {
			for (bit_idx = 0; bit_idx < N; bit_idx++) {
				if (num & (1 << bit_idx)) {
					cout << input[bit_idx] << ' ';
				}
			}
			cout << " : sum 0" << endl;
		}
	}
}