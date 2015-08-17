#include <iostream>
using namespace std;

#define MAX(x,y) ((x>y) ? x:y)
#define MIN(x,y) ((x>y) ? y:x)

char hexaMap[16][4] = {
	{ '0','0','0','0' },
	{ '0','0','0','1' },
	{ '0','0','1','0' },
	{ '0','0','1','1' },
	{ '0','1','0','0' },
	{ '0','1','0','1' },
	{ '0','1','1','0' },
	{ '0','1','1','1' },
	{ '1','0','0','0' },
	{ '1','0','0','1' },
	{ '1','0','1','0' },
	{ '1','0','1','1' },
	{ '1','1','0','0' },
	{ '1','1','0','1' },
	{ '1','1','1','0' },
	{ '1','1','1','1' }
};

int codemap[10][3] = {
	{ 2,1,1 },
	{ 2,2,1 },
	{ 1,2,2 },
	{ 4,1,1 },
	{ 1,3,2 },
	{ 2,3,1 },
	{ 1,1,4 },
	{ 3,1,2 },
	{ 2,1,3 },
	{ 1,1,2 }
};

char inputBitmap[2000][500] = { 0, };
int patternArray[31] = { 0, };
int decryptCode[8] = { 0, };

int intputBitsHight = 0;
int inputBitsLen = 0;

int maxSum = 0;

void htob(char letter);
int calBitPattern(int row, int begin);
int matchCode(int a, int b, int c);
void decrypt();
bool verify();

int main(void) {
	int testCase = 0;
	int C, N, M;
	char letter;
	int sum = 0;
	int row, col;
	int col_length = 0;
	int begin = 0;
	int height_backup = 0;

	cin >> C;

	for (testCase = 0; testCase < C; testCase++) {
		cin >> N >> M;
		for (row = 0; row < N; row++) {
			inputBitsLen = 0;
			for (col = 0; col < M; col++) {
				cin >> letter;
				intputBitsHight = row;
				htob(letter);
			}
		}

		row = 0;
		col_length = M * 4;
		while (row < N) {
			col = 0;
			sum = 0;

			while ((inputBitmap[row][col] != '1') && (col < col_length)) {
				col++;
			}

			if (col < col_length) {
				begin = col;
				int i = begin;
				while (i < col_length) {
					int up = ((row - 1) < 0) ? 0 : (row - 1);
					if ((row == 0) || (inputBitmap[row][i] != inputBitmap[up][i])) {
						i = calBitPattern(row, i);
						decrypt();
						if (verify()) {
							for (int j = 0; j < 8; j++) {
								sum += decryptCode[j];
							}
						}
						if (i < col_length) {
							while ((inputBitmap[row][i] != '1') && (i < col_length)) {
								i++;
							}
						}
					}
					else {
						i++;
					}
				}
			}
			row++;
			maxSum = MAX(maxSum, sum);
		}
		cout << '#' << testCase + 1 << ' ' << maxSum << endl;
	}

	return 0;
}

void htob(char letter) {
	int hexaInt = 0;

	if (letter <= '9') {
		hexaInt = letter - '0';
	}
	else {
		hexaInt = letter - 'A' + 10;
	}
	for (int i = 0; i < 4; i++) {
		inputBitmap[intputBitsHight][inputBitsLen++] = hexaMap[hexaInt][i];
	}
}

int calBitPattern(int row, int begin) {
	int cal = 0;
	int arrayLen = 0;
	int index = begin;
	char target = inputBitmap[row][index];

	while (true) {
		if (target == inputBitmap[row][index]) {
			cal++;
		}
		else {
			patternArray[arrayLen++] = cal;
			target = inputBitmap[row][index];
			cal = 1;
		}
		if (arrayLen == 31) {
			break;
		}
		else {
			index++;
		}
	}

	return index;
}

void decrypt() {
	int min = 100;

	for (int i = 0; i < 31; i++) {
		min = MIN(min, patternArray[i]);
	}

	if (min > 1) {
		for (int i = 0; i < 31; i++) {
			patternArray[i] /= min;
		}
	}

	for (int i = 0; i < 8; i++) {
		decryptCode[i] = matchCode(patternArray[4 * i], patternArray[1 + (4 * i)], patternArray[2 + (4 * i)]);
	}
}

int matchCode(int a, int b, int c) {
	int code = 0;
	for (int i = 0; i < 10; i++) {
		if ((codemap[i][0] == a) && codemap[i][1] == b && codemap[i][2] == c) {
			code = i;
			break;
		}
	}
	return code;
}

bool verify() {
	int parity = decryptCode[7];
	int result = 0;
	int isMatched = false;

	result = (decryptCode[0] + decryptCode[2] + decryptCode[4] + decryptCode[6]) * 3;
	result += decryptCode[1] + decryptCode[3] + decryptCode[5];
	result = 10 - (result % 10);

	if (result == parity) {
		isMatched = true;
	}

	return isMatched;
}