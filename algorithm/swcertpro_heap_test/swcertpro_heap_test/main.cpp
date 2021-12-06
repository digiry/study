#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init();
extern void clear();
extern void push(int idx, char name[]);
extern int pop();
extern void mod(int idx, char name[]);

#define CLEAR		100
#define PUSH		200
#define POP			300
#define MOD			400

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main() {
	setbuf(stdout, NULL);

	int T;
	scanf("%d", &T);

	int N;

	int cmd, ret;

	int idx;
	char name[11];

	for (int TC = 1; TC <= T; TC++) {

		init();

		int score = 100;

		scanf("%d", &N);

		for (int i = 0; i < N; i++) {
			scanf("%d", &cmd);

			switch (cmd) {

			case CLEAR:
				//printf("> CLEAR\n");
				clear();
				break;

			case PUSH:
				scanf("%d %s", &idx, &name);
				//printf("> PUSH %d %s\n", idx, name);
				push(idx, name);

				break;

			case POP:
				scanf("%d", &idx);
				//printf("> POP %d\n", idx);
				ret = pop();

				if (ret != idx) {
					score = 0;
				}

				break;

			case MOD:
				scanf("%d %s", &idx, &name);
				//printf("> MOD %d %s", idx, name);
				mod(idx, name);

				break;
			}

		}

		printf("#%d %d\n", TC, score);
	}

	return 0;
}