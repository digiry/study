#include <iostream>

using namespace std;

typedef struct __brackets {
	int r_open;
	int r_close;
	int c_open;
	int c_close;
	int s_open;
	int s_close;
	int dot_cnt;
} bracket;

bracket master_infomap[10];
bracket user_infomap[10];

int T;
int Master_N;
int User_N;

int R;
int C;
int S;

void init_infomap();
void cal_master_rcs();
void cal_user_indent();

int main() {
	int tc;
	int line_cnt;
	int dot_cnt;
	bool is_indent;
	char letter;
	int idx;
	int r_open_cnt;
	int r_close_cnt;
	int c_open_cnt;
	int c_close_cnt;
	int s_open_cnt;
	int s_close_cnt;

	cin >> T;
	for (tc = 0; tc < T; tc++) {
		cin >> Master_N >> User_N;
		init_infomap();
		letter = cin.get();
		R = -1;
		C = -1;
		S = -1;
		line_cnt = 0;
		dot_cnt = 0;
		r_open_cnt = 0;
		r_close_cnt = 0;
		c_open_cnt = 0;
		c_close_cnt = 0;
		s_open_cnt = 0;
		s_close_cnt = 0;
		is_indent = true;
		// analyse Master code
		while (line_cnt < Master_N) {
			letter = cin.get();

			if (is_indent && (letter == '.')) {
				dot_cnt++;
			}
			else {
				is_indent = false;
				switch (letter) {
				case '(': r_open_cnt++; break;
				case ')': r_close_cnt++; break;
				case '{': c_open_cnt++; break;
				case '}': c_close_cnt++; break;
				case '[': s_open_cnt++; break;
				case ']': s_close_cnt++; break;
				case '\n':
					if (line_cnt <= 1) {
						master_infomap[0].dot_cnt = dot_cnt;
					}
					else {
						master_infomap[line_cnt - 1].dot_cnt = dot_cnt;
					}
					line_cnt++;
					dot_cnt = 0;
					is_indent = true;
					break;
				default:
					break;
				}
				master_infomap[line_cnt].r_open = r_open_cnt;
				master_infomap[line_cnt].r_close = r_close_cnt;
				master_infomap[line_cnt].c_open = c_open_cnt;
				master_infomap[line_cnt].c_close = c_close_cnt;
				master_infomap[line_cnt].s_open = s_open_cnt;
				master_infomap[line_cnt].s_close = s_close_cnt;
			}
		}
		
		line_cnt = 0;
		r_open_cnt = 0;
		r_close_cnt = 0;
		c_open_cnt = 0;
		c_close_cnt = 0;
		s_open_cnt = 0;
		s_close_cnt = 0;
		// analyse User code
		while (line_cnt < User_N) {
			letter = cin.get();

			switch (letter) {
			case '(': r_open_cnt++; break;
			case ')': r_close_cnt++; break;
			case '{': c_open_cnt++; break;
			case '}': c_close_cnt++; break;
			case '[': s_open_cnt++; break;
			case ']': s_close_cnt++; break;
			case '\n':
				user_infomap[line_cnt].dot_cnt = -1;
				line_cnt++;
				break;
			default:
				break;
			}
			user_infomap[line_cnt].r_open = r_open_cnt;
			user_infomap[line_cnt].r_close = r_close_cnt;
			user_infomap[line_cnt].c_open = c_open_cnt;
			user_infomap[line_cnt].c_close = c_close_cnt;
			user_infomap[line_cnt].s_open = s_open_cnt;
			user_infomap[line_cnt].s_close = s_close_cnt;
		}
		cal_master_rcs();
		cal_user_indent();

		cout << 0;
		for (idx = 0; idx < User_N - 1; idx++) {
			cout << ' ' << user_infomap[idx].dot_cnt;
		}
		cout << endl;
	}


	return 0;
}

void init_infomap() {
	int idx;
	for (idx = 0; idx < Master_N; idx++) {
		master_infomap[idx].r_open = 0;
		master_infomap[idx].r_close = 0;
		master_infomap[idx].c_open = 0;
		master_infomap[idx].c_close = 0;
		master_infomap[idx].s_open = 0;
		master_infomap[idx].s_close = 0;
		master_infomap[idx].dot_cnt = 0;
	}
	for (idx = 0; idx < User_N; idx++) {
		user_infomap[idx].r_open = 0;
		user_infomap[idx].r_close = 0;
		user_infomap[idx].c_open = 0;
		user_infomap[idx].c_close = 0;
		user_infomap[idx].s_open = 0;
		user_infomap[idx].s_close = 0;
		user_infomap[idx].dot_cnt = -1;
	}
}

void cal_master_rcs() {
	int idx;
	int r_delta;
	int c_delta;
	int s_delta;

	// count delta 1
	for (idx = 0; idx < Master_N; idx++) {
		r_delta = master_infomap[idx].r_open - master_infomap[idx].r_close;
		c_delta = master_infomap[idx].c_open - master_infomap[idx].c_close;
		s_delta = master_infomap[idx].s_open - master_infomap[idx].s_close;
		if ((r_delta != 0) && (c_delta == 0) && (s_delta == 0)) {
			R = master_infomap[idx].dot_cnt / r_delta;
		}
		if ((r_delta == 0) && (c_delta != 0) && (s_delta == 0)) {
			C = master_infomap[idx].dot_cnt / c_delta;
		}
		if ((r_delta == 0) && (c_delta == 0) && (s_delta != 0)) {
			S = master_infomap[idx].dot_cnt / s_delta;
		}
	}
	// count delta 2
	for (idx = 0; idx < Master_N; idx++) {
		r_delta = master_infomap[idx].r_open - master_infomap[idx].r_close;
		c_delta = master_infomap[idx].c_open - master_infomap[idx].c_close;
		s_delta = master_infomap[idx].s_open - master_infomap[idx].s_close;
		if ((r_delta != 0) && (c_delta != 0) && (s_delta == 0)) {
			if (R != -1) {
				C = (master_infomap[idx].dot_cnt - (R*r_delta)) / c_delta;
			}
			if (C != -1) {
				R = (master_infomap[idx].dot_cnt - (C*c_delta)) / r_delta;
			}
		}
		if ((r_delta != 0) && (c_delta == 0) && (s_delta != 0)) {
			if (R != -1) {
				S = (master_infomap[idx].dot_cnt - (R*r_delta)) / s_delta;
			}
			if (S != -1) {
				R = (master_infomap[idx].dot_cnt - (S*s_delta)) / r_delta;
			}
		}
		if ((r_delta == 0) && (c_delta != 0) && (s_delta != 0)) {
			if (C != -1) {
				S = (master_infomap[idx].dot_cnt - (C*c_delta)) / s_delta;
			}
			if (S != -1) {
				C = (master_infomap[idx].dot_cnt - (S*s_delta)) / c_delta;
			}
		}
	}
	// count delta 3
	for (idx = 0; idx < Master_N; idx++) {
		r_delta = master_infomap[idx].r_open - master_infomap[idx].r_close;
		c_delta = master_infomap[idx].c_open - master_infomap[idx].c_close;
		s_delta = master_infomap[idx].s_open - master_infomap[idx].s_close;
		if ((r_delta != 0) && (c_delta != 0) && (s_delta != 0)) {
			if ((R != -1) && (C != -1)) {
				S = (master_infomap[idx].dot_cnt - (R*r_delta) - (C*c_delta)) / s_delta;
			}
			if ((R != -1) && (S != -1)) {
				C = (master_infomap[idx].dot_cnt - (R*r_delta) - (S*s_delta)) / c_delta;
			}
			if ((C != -1) && (S != -1)) {
				R = (master_infomap[idx].dot_cnt - (C*c_delta) - (S*s_delta)) / r_delta;
			}
		}
	}
}

void cal_user_indent() {
	int tmp_r;
	int tmp_c;
	int tmp_s;
	int idx;

	for (idx = 0; idx < User_N; idx++) {
		tmp_r = R * (user_infomap[idx].r_open - user_infomap[idx].r_close);
		tmp_c = C * (user_infomap[idx].c_open - user_infomap[idx].c_close);
		tmp_s = S * (user_infomap[idx].s_open - user_infomap[idx].s_close);
		if ((tmp_r < 0) || (tmp_c < 0) || (tmp_s < 0)) {
			user_infomap[idx].dot_cnt = -1;
		}
		else {
			user_infomap[idx].dot_cnt = tmp_r + tmp_c + tmp_s;
		}
	}
}