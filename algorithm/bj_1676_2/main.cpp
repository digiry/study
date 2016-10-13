#include <stdio.h>

int count = 0;

int main() {
	int N;
	int x = 1;

	scanf("%d", &N);

	while (N >= x * 5) {
		x *= 5;
		count += N / x;
	}

	printf("%d\n", count);

	return 0;
}