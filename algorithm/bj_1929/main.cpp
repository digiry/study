#include <cstdio>

using namespace std;

int start_num;
int end_num;

bool no_primes[1000001];

int main() {
	no_primes[0] = true;
	no_primes[1] = true;

	for (int i = 2; i*i <= 1000000; i++) {
		if (no_primes[i] == false) {
			for (int j = i+i; j <= 1000000; j += i) {
				no_primes[j] = true;
			}
		}
	}

	scanf("%d %d", &start_num ,&end_num);
	for (int j = start_num; j <= end_num; j++) {
		if (no_primes[j] == false) {
			printf("%d\n", j);
		}
	}

	return 0;
}
