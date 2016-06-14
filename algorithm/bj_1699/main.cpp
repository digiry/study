#include <iostream>

#define MIN(x,y) ((x>y)?(y):(x))

using namespace std;

int N;
int D[100001] = { 0, };

int main() {
	cin >> N;

	for (int i = 1; i <= N; i++) {
		D[i] = i; // maximum count
		for (int j = 1; j*j <= i; j++) {
			//cout << i << " : " << "D[" << i << "], D[" << i << "- (" << j << "*" << j << ")] + 1" << "(" << D[i - (j*j)] << "+1)";
			D[i] = MIN(D[i], D[i - (j*j)] + 1);
			//cout << " MIN : " << D[i] << endl;
		}
	}

	cout << D[N] << endl;

	return 0;
}