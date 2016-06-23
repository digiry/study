#include <cstdio>

using namespace std;

int N; // 1~10,000
int arr[10000];

void swap(int a, int b) {
	int t;
	t = arr[a];
	arr[a] = arr[b];
	arr[b] = t;
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &(arr[i]));
	}

	int sm_i, rep_i;

	sm_i = N - 1;
	rep_i = N - 1;

	while ((sm_i > 0) && (arr[sm_i - 1] >= arr[sm_i])) sm_i--;
	if (sm_i < 1) {
		printf("-1\n");
	}
	else {
		while ((sm_i <= rep_i) && arr[sm_i - 1] >= arr[rep_i]) rep_i--;
		swap(sm_i - 1, rep_i);

		rep_i = N - 1;

		while (sm_i < rep_i) {
			swap(sm_i, rep_i);
			sm_i++;
			rep_i--;
		}

		for (int x = 0; x < N; x++) {
			printf("%d ", arr[x]);
		}
		printf("\n");
	}

	return 0;
}