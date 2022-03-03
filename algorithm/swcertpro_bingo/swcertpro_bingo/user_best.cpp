#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#define MAX_N 10
#define MAX_LEN 11
#define MAX_M (1000 + 1)
#define EMPTY ""

#include <unordered_map>
#include <algorithm>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

int N, M;
int cur_round;
bool is_finished;
int winners;

#define pii pair<int, int>
#define pip pair<int, pii>
#define ppp pair<pii, pii>

unordered_map<string, vector<pip>> cells_by_word;
string bingos[MAX_M][MAX_N][MAX_N];

void init(int N, int M) {
	::N = N;
	::M = M;
	cur_round = 0;
	is_finished = false;
	cells_by_word.clear();
}

void join(int mID, char mBingo[MAX_N][MAX_N][MAX_LEN]) {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			string w = string(mBingo[y][x]);
			bingos[mID][y][x] = w;
			cells_by_word[w].push_back(pip(mID, pii(y, x)));
		}
	}
}

void update(string word) {
	vector<pip> cells = cells_by_word[word];

	int max_cnt = 0;
	int total = 0;

	for (pip info : cells) {
		int id = info.first;
		auto bingo = bingos[id];

		int y = info.second.first;
		int x = info.second.second;

		bingo[y][x] = EMPTY;

		int i, cnt = 0;
		for (i = 0; i < N; i++) {
			if (bingo[y][i] != EMPTY) {
				break;
			}
		}
		if (i == N) {
			cnt++;
		}

		for (i = 0; i < N; i++) {
			if (bingo[i][x] != EMPTY) {
				break;
			}
		}
		if (i == N) {
			cnt++;
		}

		for (i = 0; i < N; i++) {
			if (bingo[i][i] != EMPTY) {
				break;
			}
		}
		if (i == N) {
			cnt++;
		}

		for (i = 0; i < N; i++) {
			if (bingo[i][N - 1 - i] != EMPTY) {
				break;
			}
		}
		if (i == N) {
			cnt++;
		}

		if (max_cnt < cnt) {
			max_cnt = cnt;
			total = id;
		}
		else if (max_cnt == cnt) {
			total += id;
		}
	}

	if (max_cnt > 0) {
		::winners = total;
		is_finished = true;
	}
}

string select(int id) {
	auto bingo = bingos[id];

	int x_cnt[MAX_N] = {};
	int y_cnt[MAX_N] = {};
	int diag_cnt[2] = {};

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (bingo[y][x] == EMPTY) {
				x_cnt[x]++;
				y_cnt[y]++;
				if (x == y) {
					diag_cnt[0]++;
				}
				if (x + y == N - 1) {
					diag_cnt[1]++;
				}
			}
		}
	}

	ppp max_pos_info = ppp(pii(-1, 0), pii(0, 0));
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int cnt = 0, diag = 0;
			if (bingo[y][x] != EMPTY) {
				cnt = max(x_cnt[x], y_cnt[y]);
				if (x == y) {
					cnt = max(cnt, diag_cnt[0]);
					diag++;
				}
				if (x + y == N - 1) {
					cnt = max(cnt, diag_cnt[1]);
					diag++;
				}

				max_pos_info = max(ppp(pii(cnt, diag), pii(-y, -x)), max_pos_info);
			}
		}
	}

	int y = -max_pos_info.second.first;
	int x = -max_pos_info.second.second;

	return bingo[y][x];
}

string go() {
	int id = cur_round++ % M + 1;
	string w = select(id);
	update(w);

	return w;
}

void selectWord(int mRound, char mWord[]) {
	string w;
	for (; cur_round < mRound;) {
		w = go();
	}

	strncpy(mWord, w.c_str(), MAX_LEN);
}

int findWinners() {
	while (!is_finished) {
		go();
	}

	return winners;
}