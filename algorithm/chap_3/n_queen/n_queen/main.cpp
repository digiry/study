#include <iostream>

using namespace std;

#define ABS(x) ((x>0)?(x):-(x))

typedef struct __node {
	int row;
	int col;
} node;

node node_solution[10];

int T;
int N;

void check_node(node target);
bool is_solution(node target);

int main() {
	int tc;
	node input_node;

	cin >> T;
	for (tc = 0; tc < T; tc++) {
		cin >> N;
		cout << '#' << tc + 1 << ' ' << N << 'x' << N << endl;
		input_node.row = -1;
		input_node.col = -1;
		check_node(input_node);
	}
	return 0;
}

void check_node(node target) {
	int idx_row;
	int idx_col;
	node child;

	if (target.row < N) {
		//cout << '(' << target.row << ',' << target.col << ')' << endl;
		if (is_solution(target)) {
			if (target.row >= 0) {
				// optical queen coordinate
				node_solution[target.row].row = target.row;
				node_solution[target.row].col = target.col;
			}
			if (target.row == (N - 1)) {
				// print stack()
				for (int i = 0; i < N; i++) {
					cout << node_solution[i].row << ',' << node_solution[i].col << ' ';
				}
				cout << endl;
			}
			for (idx_col = 0; idx_col < N; idx_col++) {
				child.row = target.row + 1;
				child.col = idx_col;
				check_node(child);
			}
		}
	}
}

bool is_solution(node target) {
	int idx_i;
	bool result = true;

	if (target.row == -1) {
		return result;
	}
	// check vertical line
	for (idx_i = 0; idx_i < target.row; idx_i++) {
		if (target.col == node_solution[idx_i].col) {
			result = false;
			break;
		}
	}
	if (result) {
		// check diagonal lines(right, left)
		for (idx_i = 0; idx_i < target.row; idx_i++) {
			if (ABS(node_solution[idx_i].row - target.row) == ABS(node_solution[idx_i].col - target.col)) {
				result = false;
				break;
			}
		}
	}

	return result;
}
