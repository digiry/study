#include <iostream>

#define MAX(x,y) ((x>y)?(x):(y))

using namespace std;

int N;
int prices[1001];
int d[1001] = { 0, };

int main() {
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> prices[i];
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= i; j++) {
			// cout << i << ": d[" << i << " - " << j << "](" << d[i - j] << ") + prices[" << j << "](" << prices[j] << ")=" << d[j - 1] + prices[j] << ", d[" << i << "](" << d[i] << ") ";
			d[i] = MAX(d[i - j] + prices[j], d[i]);
			// cout << " MAX: " << d[i] << endl;
		}
	}

	cout << d[N] << endl;

	return 0;
}