#include <cstdio>

using namespace std;

int N;
bool visit[10000];

void power_set(int a, int check);

int main() {
	scanf("%d", &N);

	power_set(N, 0);
	return 0;
}

void power_set(int n, int depth) {
	if (n == depth) {
		for (int i = 0; i < n; i++) {
			if (visit[i]) {
				printf("%d ", i + 1);
			}
		}
		printf("\n");
		return;
	}
	visit[depth] = true;
	power_set(n, depth + 1);
	visit[depth] = false;
	power_set(n, depth + 1);
}
