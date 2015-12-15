#include <iostream>

using namespace std;

#define ABS(x) ((x>0)?(x):-(x))
#define MIN(x,y) ((x>y)?(y):(x))

typedef struct __node {
	int x;
	int y;
} node;

int T;
int W;
int H;
int N;

node map[1001] = { 0, };

int sum;

int calc_dist(node a_node, node b_node);

int main() {
	int tc;
	int idx;

	cin >> T;
	for (tc = 0; tc < T; tc++) {
		sum = 0;
		cin >> W >> H >> N;
		cin >> map[0].x >> map[0].y;
		for (idx = 1; idx < N; idx++) {
			cin >> map[idx].x >> map[idx].y;
			sum += calc_dist(map[idx - 1], map[idx]);
		}
		cout << sum << endl;
	}
	return 0;
}

int calc_dist(node a_node, node b_node) {
	int delta_x;
	int delta_y;
	int temp_sum = 0;
	int min_delta = 0;

	delta_x = a_node.x - b_node.x;
	delta_y = a_node.y - b_node.y;
	// right diagonal
	if ((delta_x > 0) && (delta_y > 0) ||
		(delta_x < 0) && (delta_y < 0)) {
		min_delta = MIN(ABS(delta_x), ABS(delta_y));
		temp_sum = min_delta + ABS(ABS(delta_x) - ABS(delta_y));
	}
	// slope 0 degree or 90 degree
	// left diagonal
	else {
		temp_sum = ABS(delta_x) + ABS(delta_y);
	}
	return temp_sum;
}