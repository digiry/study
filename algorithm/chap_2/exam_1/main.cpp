#include <iostream>

using namespace std;

#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define MIN(x,y) ((x>y)? (y):(x))

int T;
int N;
int numbers[10] = { 0, };

void selection_sort(int begin, int size);

int main() {
	int tc;

	cin >> T;
	for (tc = 0; tc < T; tc++) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> numbers[i];
		}

		selection_sort(0, N);

		for (int i = 0; i < N; i++) {
			cout << numbers[i] << ' ';
		}
		cout << endl;
	}
	return 0;
}

void selection_sort(int begin, int size) {
	int temp;
	int min_idx;
	int min_value = 9999;

	if (begin == size - 1) {
		return;
	}
	
	min_idx = begin;
	min_value = numbers[min_idx];
	for (int idx = begin; idx < size; idx++) {
		if (min_value > numbers[idx]) {
			min_value = numbers[idx];
			min_idx = idx;
		}
	}

	if (begin != min_idx) {
		temp = numbers[min_idx];
		numbers[min_idx] = numbers[begin];
		numbers[begin] = temp;
	}

	selection_sort(begin + 1, size);
}