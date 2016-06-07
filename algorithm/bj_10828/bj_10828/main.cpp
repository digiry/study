#include <iostream>

using namespace std;

int T;
int stack[10000];
int top = -1;

int main() {
	char opt[6];
	int number;
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> opt;
		switch (opt[0]) {
		case 'p':
			if (opt[1] == 'u') {
				cin >> number;
				stack[++top] = number;
			} else if (opt[1] == 'o') {
				if (top == -1) {
					cout << -1 << endl;
				} else {
					cout << stack[top--] << endl;
				}
			}
			break;
		case 'e':
			if (top == -1) {
				cout << 1 << endl;
			} else {
				cout << 0 << endl;
			}
			break;
		case 't':
			if (top == -1) {
				cout << -1 << endl;
			}
			else {
				cout << stack[top] << endl;
			}
			break;
		case 's':
			cout << top + 1 << endl;
			break;
		default:
			cout << "Error" << opt << endl;
		}
	}
	return 0;
}