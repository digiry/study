#include <cstdio>

using namespace std;

#define ABS(x) ((x>0)?(x):-(x))
#define MIN(x,y) ((x>y)?(y):(x))

int T;
int N;
int AP_R;
int MIN_AP = 0;

typedef struct _iot_list {
	int x;
	int y;
	int range;
} IOT_LIST;

typedef struct _ap_list {
	int x;
	int y;
} AP_LIST;

IOT_LIST iot_list[40];
int iot_len = 0;
AP_LIST ap_list[20];
int ap_len = 0;
bool all_dist[20][40];
int visit[5];
int visit_len = 0;
int currunt_ap_len = 0;
bool check_iot[40];

void init();

void comb(int n, int r);

int main() {
	int t;
	scanf("%d\n", &T);

	for (int tc = 1; tc <= T; tc++) {
		init();
		scanf(" %d %d", &N, &AP_R);
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				scanf(" %d", &t);
				if (t == 9) {
					ap_list[ap_len].x = r;	ap_list[ap_len].y = c;
					ap_len++;
				}
				else if ((1 <= t) && (t <= 3)) {
					iot_list[iot_len].x = r;	iot_list[iot_len].y = c;
					iot_list[iot_len].range = t;
					iot_len++;
				}
			}
		}

		if (ap_len > 5) {
			visit_len = 5;
		}
		else {
			visit_len = ap_len;
		}
		MIN_AP = ap_len + 1;
		for (int ap = 0; ap < ap_len; ap++) {
			for (int iot = 0; iot < iot_len; iot++) {
				t = ABS(ap_list[ap].x - iot_list[iot].x) + ABS(ap_list[ap].y - iot_list[iot].y) - iot_list[iot].range - AP_R;
				if (t <= 0)	all_dist[ap][iot] = true;
			}
		}

		for (int r = 1; r <= visit_len; r++) {
			if (MIN_AP >= ap_len + 1) {
				currunt_ap_len = r;
				comb(ap_len, r);
			}
		}
		if (MIN_AP == ap_len + 1) {
			MIN_AP = -1;
		}
		printf("#%d %d\n", tc, MIN_AP);
		iot_len = 0;
		ap_len = 0;
	}
	return 0;
}

void init() {
	for (int ap = 0; ap < ap_len; ap++) {
		for (int iot = 0; iot < iot_len; iot++) {
			all_dist[ap][iot] = false;
			check_iot[iot] = false;
		}
		visit[ap] = false;
	}
}

void comb(int n, int r) {
	int iot_count = 0;
	if (n < r) return;
	if (r == 0) {
		for (int iot = 0; iot < iot_len; iot++) check_iot[iot] = false;
		for (int ap_i = 0; ap_i < currunt_ap_len; ap_i++) {
			for (int iot = 0; iot < iot_len; iot++) {
				if (check_iot[iot] == false && all_dist[visit[ap_i]][iot]) {
					check_iot[iot] = true;
					iot_count++;
				}
			}
		}

		if (iot_count == iot_len) {
			MIN_AP = MIN(MIN_AP, currunt_ap_len);
		}
		return;
	}

	visit[r - 1] = n - 1;
	comb(n - 1, r - 1);
	comb(n - 1, r);
}