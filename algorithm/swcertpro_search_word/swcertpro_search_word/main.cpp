#include <iostream>

using namespace std;

const int CMD_INIT = 1;
const int CMD_ADD = 2;
const int CMD_REMOVE = 3;
const int CMD_SEARCH = 4;

int T, MARK;

extern void init();
extern int add(char str[]);
extern int remove(char str[]);
extern int search(char str[]);

typedef struct _input {
	char keyword[31];
	int answer;
} Input;

int run() {
	int query_count = 0;
	int cmd = 0;
	char keyword[31];
	int user_answer = 0;
	int answer = 0;
	int result = 1;

	cin >> query_count;

	for (int q = 0; q < query_count; ++q) {
		cin >> cmd;
		switch (cmd) {
		case CMD_INIT:
			init();
			break;
		case CMD_ADD:
			cin >> keyword >> answer;
			user_answer = add(keyword);
			if (user_answer != answer) {
				result = result * 0;
			}
			break;
		case CMD_REMOVE:
			cin >> keyword >> answer;
			user_answer = remove(keyword);
			if (user_answer != answer) {
				result = result * 0;
			}
			break;
		case CMD_SEARCH:
			cin >> keyword >> answer;
			user_answer = search(keyword);
			if (user_answer != answer) {
				result = result * 0;
			}
			break;
		default:
			break;
		}
	}

	return result;
}

int main() {
	int result = 0;

	cin >> T >> MARK;

	for (int tc = 1; tc <= T; tc++)
	{
		if (run() == 1) {
			cout << "#" << tc << ' ' << MARK << endl;
		}
		else {
			cout << "#" << tc << ' ' << '0' << endl;
		}
	}

	return 0;
}
