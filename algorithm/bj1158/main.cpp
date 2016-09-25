#include <cstdio>

using namespace std;

// 1 <= M <= N <= 5,000
int N;
int M;
int queue[5000];
int front = -1;
int back = -1;

void en_queue(int num);
int de_queue();
bool is_emyty_queue();

int main() {
	int loop_cnt = 0;
	int count = 0;
	int temp = 0;
	int num = 0;
	scanf(" %d %d", &N, &M);

	for (num = 1; num <= N; num++) {
		en_queue(num);
	}

	printf("<");
	while (is_emyty_queue() != true) {
		loop_cnt = M;
		while (loop_cnt > 0) {
			temp = de_queue();
			if (loop_cnt != 1) {
				en_queue(temp);
			}
			if (loop_cnt == 1) {
				printf("%d", temp);
				count++;
				if (count < N) {
					printf(", ");
				}
			}
			loop_cnt--;
		}
	}
	printf(">\n");

	return 0;
}

void en_queue(int num) {
	queue[++front] = num;
}

int de_queue() {
	return queue[++back];
}

bool is_emyty_queue() {
	if (front == back) {
		return true;
	}
	return false;
}


/*
#include <cstdio>
#include <queue>
using namespace std;
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		q.push(i);
	}
	printf("<");
	for (int i = 0; i<n - 1; i++) {
		for (int j = 0; j<m - 1; j++) {
			q.push(q.front());
			q.pop();
		}
		printf("%d, ", q.front());
		q.pop();
	}
	printf("%d>\n", q.front());
	return 0;
}
*/