#include <cstdio>

using namespace std;

int N;

int main() {
	scanf("%d", &N);

	for (int i = 0; i < (1 << N); i++) {
		for (int j = 0; j < N; j++) {
			if (i & (1 << j)) {
				printf("%d ", j + 1);
			}
		}
		printf("\n");
	}
	return 0;
}