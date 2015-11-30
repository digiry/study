#include <iostream>

using namespace std;

int T;
int R;
char input[27];
char temp[27];
int N;

void init_input();
void comb(int size, int collect);

int main() {
	int tc;

	cin >> T;
	for (tc = 0; tc < T; tc++) {
		init_input();
		cin >> R;
		cin >> input;
		for (N = 0; input[N] != 0; ) N++;
		cout << '#' << tc + 1 << ' ' << input << endl;
		comb(N, R);
	}

	return 0;
}

void init_input() {
	for (int idx = 0; idx < 27; idx++) {
		input[idx] = 0;
		temp[idx] = 0;
	}
}

void comb(int size, int collect) {
	if (size < collect) {
		return;
	}
	else if (collect == 0) {
		for (int idx = 0; idx < R; idx++) {
			if (temp[idx] != 0) {
				cout << temp[idx] << ' ';
			}
		}
		cout << endl;
	}
	else {
		temp[collect - 1] = input[size - 1];
		comb(size - 1, collect - 1);
		comb(size - 1, collect);
	}
}