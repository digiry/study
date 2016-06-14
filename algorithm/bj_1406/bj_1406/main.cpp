#include <iostream>

using namespace std;

int T;

char l_stack[600000];
int l_top = -1;
char r_stack[600000];
int r_top = -1;

int main() {
	char cmd;
	char letter;
	cin >> l_stack;
	cin >> T;

	l_top = 0;
	while (l_stack[l_top] != '\0') {
		l_top++;
	}
	for (int tc = 0; tc < T; tc++) {
		cin >> cmd;
		switch (cmd) {
		case 'P':
			cin >> letter;
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
			l_top--;
			break;
		default:
			break;
		}
	}
	while (l_top != -1) {
		r_stack[++r_top] = l_stack[l_top--];
	}
	while (r_top != -1) {
		cout << r_stack[r_top--];
	}
	cout << endl;
	return 0;
}
