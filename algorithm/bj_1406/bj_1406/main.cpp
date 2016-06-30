#include <cstdio>

using namespace std;

int T;

char l_stack[600001];
int l_top = -1;
char r_stack[600001];
int r_top = -1;

int main() {
	char cmd;
	char letter;
	scanf("%s\n", l_stack);
	scanf("%d\n", &T);

	while (l_stack[++l_top] != '\0') {}
	l_top--;

	for (int tc = 0; tc < T; tc++) {
		scanf(" %c", &cmd);
		switch (cmd) {
		case 'P':
			scanf(" %c\n", &letter);
			l_stack[++l_top] = letter;
			break;
		case 'L':
			if (l_top != -1) {
				r_stack[++r_top] = l_stack[l_top--];
			}
			break;
		case 'D':
			if (r_top != -1) {
				l_stack[++l_top] = r_stack[r_top--];
			}
			break;
		case 'B':
			if (l_top != -1) {
				l_top--;
			}
			break;
		default:
			break;
		}
	}
	while (l_top != -1) {
		r_stack[++r_top] = l_stack[l_top--];
	}
	while (r_top != -1) {
		printf("%c", r_stack[r_top--]);
	}
	printf("\n");
	return 0;
}
