#include <iostream>

using namespace std;

#define MAX(x,y) ((x>y)?(x):(y))

int T;
int N;
int input[100] = { 0, };
int max_linked = 0;

void init_input();

int main() {
	int tc;
	int idx_i;
	int idx_j;
	int num;
	int base;
	int target;
	int linked_cnt = 0;

	cin >> T;
	for (tc = 0; tc < T; tc++) {
		cin >> N;
		init_input();
		for (idx_i = 0; idx_i < N; idx_i++) {
			cin >> num;
			input[num] = idx_i;
		}
		input[idx_i] = -1;
		max_linked = 0;
		for (idx_i = 1; idx_i <= N; idx_i++) {
			linked_cnt = 1;
			base = input[idx_i];
			for (idx_j = idx_i + 1; idx_j <= N + 1; idx_j++) {
				target = input[idx_j];
				if (base < target) {
					linked_cnt++;
					base = target;
					max_linked = MAX(max_linked, linked_cnt);
				}
				else {
					break;
					max_linked = 0;
				}
			}
		}

		cout << '#' << tc + 1 << ' ' << N - max_linked << endl;
	}
	return 0;
}

void init_input() {
	for (int idx = 0; idx < N; idx++) {
		input[idx] = 0;
	}
}