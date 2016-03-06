#include <iostream>

using namespace std;

#define MIN(x,y) (((x)>(y))?(y):(x))

int T;
int N;
int C;

int coins[4];
int counts[21];
int min_cnt;

void calculate(int total);

int main() {
	int tc;
	int idx;
	cin >> T;

	for (tc = 0; tc < T; tc++) {
		cin >> N >> C;
		for (idx = 0; idx < N; idx++) {
			cin >> coins[idx];
		}
		calculate(C);

		cout << counts[20] << endl;
	}
	return 0;
}

void calculate(int total) {
	int idx;
	int remain;

	counts[0] = 0;
	for (remain = 1; remain <= total; remain++) {
		min_cnt = 20;
		for (idx = 0; idx < 4; idx++) {
			if ((remain - coins[idx]) >= 0) {
				min_cnt = MIN(min_cnt, counts[remain - coins[idx]] + 1);
			}
		}
		counts[remain] = min_cnt;
	}
}