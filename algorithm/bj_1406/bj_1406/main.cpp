#include <iostream>

using namespace std;

int T;
char buffer[100001];

char l_stack[600001];
int l_top = -1;
char r_stack[600001];
int r_top = -1;

void prepare_buffer();

int main() {
	char cmd;
	char letter;
	cin >> l_stack;
	cin >> T;

	prepare_buffer();
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

void prepare_buffer() {
	int idx = 0;
	char letter = l_stack[idx];

	while (letter != '\0') {
		++l_top;
		letter = l_stack[idx++];
	}
}
