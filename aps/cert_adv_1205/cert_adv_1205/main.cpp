#include <iostream>

using namespace std;

#define MAX(x,y) ((x>y)?(x):(y))
#define toI(x) ((x)-'0')
int T;

int input;
int mem[100000] = { 0, };
int max_turn;

void game(int number, int rnumber, int turn);
int convert_number(int number, char *cnt_num);
int calc(char *cnt_num);

int main() {
	int tc;
	int idx;

	for (idx = 0; idx < 100000; idx++) {
		mem[idx] = -1;
	}

	cin >> T;
	for (tc = 0; tc < T; tc++) {
		cin >> input;

		max_turn = 0;
		game(input, input, 0);

		cout << '#' << tc + 1 << ' ' << max_turn << endl;
	}

	return 0;
}

void game(int number, int rnumber, int turn) {
	int idx;
	int result;
	int num;
	int n_len = 0;
	int full_len = 0;
	char cnt_num[10] = "";

	if (rnumber < 10) {
		if (max_turn < turn) {
			max_turn = turn;
			mem[number] = turn;
		}
	}
	else {
		if (mem[number] != -1) {
			max_turn = mem[number];
		}
		else {
			n_len = convert_number(rnumber, cnt_num);
			full_len = n_len + (n_len - 1) - 2;
			for (num = 1; num < (1 << (n_len - 1)); num++) {
				for (idx = 0; idx < (n_len - 1); idx++) {
					if (num & (1 << idx)) {
						cnt_num[full_len - (2 * idx)] = '*';
					}
					else {
						cnt_num[full_len - (2 * idx)] = '_';
					}
				}

				result = calc(cnt_num);
				game(number, result, turn + 1);
			}

		}
	}
}

int convert_number(int number, char *cnt_num) {
	char temp_num[5] = "";
	int idx;
	int jdx;
	int t_idx;
	int temp = number;
	int a_num;

	idx = 0;
	while (temp != 0) {
		a_num = temp % 10;
		temp = temp / 10;
		temp_num[5 - idx - 1] = '0' + a_num;
		idx++;
	}

	t_idx = 0;
	for (jdx = 0; jdx < 5; jdx++) {
		if (temp_num[jdx] != 0) {
			cnt_num[t_idx * 2] = temp_num[jdx];
			t_idx++;
		}
	}

	return idx;
}

int calc(char *cnt_num) {
	int result;
	int idx;
	int board[5] = { 0, 1, 1, 1, 1 };
	int idx_b = 0;
	int temp;

	for (idx = 0; idx < 9; idx++) {
		if (cnt_num[idx] != 0) {
			if (cnt_num[idx] != '*') {
				if (cnt_num[idx] != '_') {
					board[idx_b] = board[idx_b] * 10;
					board[idx_b] = board[idx_b] + toI(cnt_num[idx]);
				}
			}
			else {
				if (cnt_num[idx] == '*') {
					idx_b++;
					board[idx_b] = 0;
				}
			}
		}
		else {
			break;
		}
	}

	result = board[0];
	for (idx = 1; idx <= idx_b; idx++) {
		result = result * board[idx];
	}

	return result;
}