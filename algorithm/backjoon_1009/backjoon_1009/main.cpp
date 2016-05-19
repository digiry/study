#include <iostream>

using namespace std;

int T;
int a;
int b;

int main() {
	int result;
	cin >> T;

	for (int tc = 0; tc < T; tc++) {
		cin >> a >> b;
		result = 1;
		for (int idx = 0; idx < b; idx++) {
			a = a % 10;
			result = (result * a) % 10;
		}
		if (result == 0) {
			result = 10;
		}
		cout << result << endl;
	}
	return 0;
}