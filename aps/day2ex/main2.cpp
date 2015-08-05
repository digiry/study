#include <iostream>

using namespace std;

#define BIT_INT(x) ((x=='0')? 0:1)

char input[] = "01D06079861D79F99F";
//char input[] = "0F97A3";
char inputBits[100] = { 0, };
int inputBitsLen = 0;

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

void htob(char letter);

int main(void) {
	int number = 0;
	int i = 0;
	// convert Hexa letter to bit letter
	for (i = 0; i < sizeof(input) - 1; i++) {
		htob(input[i]);
	}

	for (i = 0; i < inputBitsLen; i++) {
		// convert 7 bits letter to decimal
		if ((i % 7) < 7) {
			number = number * 2 + BIT_INT(inputBits[i]);
			// debug
			// cout << inputBits[i];
			if ((i % 7) == 6) {
				cout << number;
				number = 0;
				if (i != 0) {
					cout << ", ";
				}
			}
		}
	}

	if ((i % 7) != 6) {
		cout << number;
	}

	cout << endl;

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
		inputBits[inputBitsLen++] = hexaMap[hexaInt][i];
	}
}
