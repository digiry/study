#include <iostream>

using namespace std;

int T;
char buffer[51];
char stack[51];
int top = -1;

int main() {
	char symbol;
	int idx = 0;
	bool is_good = true;

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		top = -1;
		idx = 0;
		is_good = true;
		cin >> buffer;
		symbol = buffer[0];
		while (symbol != '\0') {
			if (symbol == '(') {
				stack[++top] = '(';
			}
			else if (symbol == ')') {
				if (top == -1) {
					idx = 49;
					is_good = false;
				} else {
					stack[top--] = '\0';
				}
			}
			symbol = buffer[++idx];
		}
		if (top == -1 && is_good) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
