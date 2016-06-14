#include <iostream>

using namespace std;

int N;
int D[1001];
int tiling(int num);

int main() {
	cin >> N;

	int count = 0;

	count = tiling(N);

	cout << count << endl;

	return 0;
}

int tiling(int num) {
	if (num == 0)	return 0;
	if (num == 1)	return 1;
	if (num == 2)	return 2;

	if (D[num] > 0)	return D[num];

	D[num] = ((tiling(num - 1) % 10007) + (tiling(num - 2) % 10007)) % 10007;
	
	return D[num];
}