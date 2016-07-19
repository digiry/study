#include <cstdio>

using namespace std;

int N;
int S;
int arr[20];
int visit[20];
int count = 0;

void powerset(int n, int depth, int sum);

int main() {
	scanf("%d %d", &N, &S);
	for (int i =0;i<N;i++) {
		scanf(" %d", &(arr[i]));
	}

	powerset(N, 0, 0);
	if (S == 0) count--;
	printf("%d\n", count);
	return 0;
}

void powerset(int n, int depth, int sum) {
	if (n == depth) {
		if (sum == S) {
			count++;
		}
		return;
	}
	powerset(n, depth + 1, sum + arr[depth]);
	powerset(n, depth + 1, sum);
}
