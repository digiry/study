#include <iostream>

using namespace std;

int T;

bool prime(int num);

int main() {
	int number;
	int count = 0;
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> number;
		bool is_prime = prime(number);
		if (is_prime) {
			count++;
		}
	}
	cout << count << endl;
	return 0;
}

bool prime(int num) {
	if (num < 2) {
		return false;
	}
	for (int i = 2; i*i <= num; i++) {
		if ((num % i) == 0) {
			return false;
		}
	}
	return true;
}