#include <cstdio>

using namespace std;

#define MIN(x,y) ((x>y)?(y):(x))
#define CHOOSE 2
#define NOT_CHOICE 1

int N;
int G_min;
int G_max;

int weights[10];
int checks[10];
int min_count = 0;

void comb(int n, int d, int sum);

int main() {
	scanf("%d %d %d", &N, &G_min, &G_max);

	for (int i = 0; i < N; i++) {
		scanf(" %d", &(weights[i]));
	}

	min_count = N;
	comb(N, 0, 0);

	printf("%d\n", min_count);

	return 0;
}

void comb(int n, int d, int sum) {
	int count = 0;
	if (n == d) {
		return;
	}
	if ((10 <= sum) && (sum <= 13)) {
		for (int i = 0; i < d; i++) {
			if (checks[i] == CHOOSE) {
				count++;
				//printf("[%d] %d -(%d) sum=%d\n", i, weights[i], count, sum);
			}
		}
		//printf("\n");
		min_count = MIN(min_count, count);
	}
	else {
		checks[d] = CHOOSE;
		comb(n, d + 1, sum + weights[d]);
		checks[d] = NOT_CHOICE;
		comb(n, d + 1, sum);
	}
}