#include <iostream>

using namespace std;

#define ABS(x) ((x<0)?-(x):(x))

int T;
char input[7];
int convert_input[6];

bool is_babygin = false;

void swap(int src_idx, int dst_idx);
void perm(int size, int key_idx);
bool is_run(int idx_i, int idx_j, int idx_k);
bool is_triple(int idx_i, int idx_j, int idx_k);

int main() {
	int tc;

	cin >> T;
	for (tc = 0; tc < T; tc++) {
		cin >> input;
		for (int idx = 0; idx < 6; idx++) {
			convert_input[idx] = input[idx] - '0';
		}
		is_babygin = false;
		perm(6, 0);
		cout << input << " : " << ((is_babygin)?"baby-gin":"nothing") << endl;
	}
	return 0;
}

void perm(int size, int key_idx) {
	if (key_idx < size) {
		for (int idx = key_idx; idx < size; idx++) {
			swap(key_idx, idx);
			perm(size, key_idx + 1);
			swap(key_idx, idx);
		}
	}
	else {
		/*cout << convert_input[0] << convert_input[1] << convert_input[2] <<
			convert_input[3] << convert_input[4] << convert_input[5] << endl;*/
		if (is_run(0,1,2) == true) {
			if ((is_run(3, 4, 5) == true) ||
				(is_triple(3, 4, 5) == true)) {
				is_babygin = true;
			}
		}
		if (is_triple(0, 1, 2) == true) {
			if ((is_run(3, 4, 5) == true) ||
				(is_triple(3, 4, 5) == true)) {
				is_babygin = true;
			}
		}
	}
}

void swap(int src_idx, int dst_idx) {
	int temp;

	temp = convert_input[src_idx];
	convert_input[src_idx] = convert_input[dst_idx];
	convert_input[dst_idx] = temp;
}

bool is_run(int idx_i, int idx_j, int idx_k) {
	bool result = false;

	if ((ABS(convert_input[idx_i] - convert_input[idx_j]) == 1) &&
		(ABS(convert_input[idx_j] - convert_input[idx_k]) == 1) &&
		(ABS(convert_input[idx_i] - convert_input[idx_k]) == 2)) {
		result = true;
	}

	return result;
}

bool is_triple(int idx_i, int idx_j, int idx_k) {
	bool result = false;

	if ((convert_input[idx_i] == convert_input[idx_j]) &&
		(convert_input[idx_j] == convert_input[idx_k])) {
		result = true;
	}

	return result;
}