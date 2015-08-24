#include <iostream>

using namespace std;

#define ABS(x) ((x<0)?-(x):(x))
#define SWAP(x,y,t) (t=x,x=y,y=t)

char numbers[6] = { 0, };
int permArray[720][6] = { 0, };

bool isRun(char a, char b, char c);
bool isTriplet(char a, char b, char c);
void initPermArrary();
bool isBabygin = false;
void checkBabygin(int n, int k);

int main(void) {
	int T;
	int testCase;

	cin >> T;
	
	for (testCase = 0; testCase < T; testCase++) {
		cin >> numbers[0] >> numbers[1] >> numbers[2]
			>> numbers[3] >> numbers[4] >> numbers[5];
		initPermArrary();
		isBabygin = false;
		checkBabygin(6, 0);
		cout << numbers[0] << numbers[1] << numbers[2]
			<< numbers[3] << numbers[4] << numbers[5];
		if (isBabygin) {
			cout << " : BABY-GIN" << endl;
		}
		else {
			cout << " : NO BABY-GIN" << endl;
		}
	}
	return 0;
}

void initPermArrary() {
	for (int row = 0; row < 720; row++) {
		for (int col = 0; col < 6; col++) {
			permArray[row][col] = 0;
		}
	}
}

bool isRun(char a, char b, char c) {
	bool ret = false;
	if (ABS(a - b) == 1) {
		if (ABS(a - c) == 2) {
			ret = true;
		}
	}
	return ret;
}

bool isTriplet(char a, char b, char c) {
	bool ret = false;
	if (a == b) {
		if (b == c) {
			ret = true;
		}
	}
	return ret;
}

void checkBabygin(int n, int k) {
	char temp;
	if (k == (n-1)) {
		if (isRun(numbers[0], numbers[1], numbers[2]) || isTriplet(numbers[0], numbers[1], numbers[2])) {
			if (isRun(numbers[3], numbers[4], numbers[5]) || isTriplet(numbers[3], numbers[4], numbers[5])) {
				isBabygin = true;
				// debug
				//cout << ":" << numbers[0] << numbers[1] << numbers[2] << numbers[3] << numbers[4] << numbers[5] << endl;
			}
		}
	}
	else {
		for (int i = k; i < n - 1; i++) {
			SWAP(numbers[k], numbers[i], temp);
			checkBabygin(n, k + 1);
			SWAP(numbers[k], numbers[i], temp);
		}
	}
}