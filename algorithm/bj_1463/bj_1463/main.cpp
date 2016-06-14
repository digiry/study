#include <iostream>

using namespace std;

int N;
int D[1000001];

int godown_one(int num);

int main() {
	cin >> N;

	int count = 0;

	count = godown_one(N);

	cout << count << endl;

	return 0;
}

int godown_one(int num) {
	int temp;
	if (num <= 1)	return 0;
	if (D[num] > 0)	return D[num];
	
	D[num] = godown_one(num - 1) + 1;
	if ((num % 2) == 0) {
		temp = godown_one(num / 2) + 1;
		if (D[num] > temp)	D[num] = temp;
	}
	if ((num % 3) == 0) {
		temp = godown_one(num / 3) + 1;
		if (D[num] > temp)	D[num] = temp;
	}

	return D[num];
}