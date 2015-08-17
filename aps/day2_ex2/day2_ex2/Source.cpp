#include <iostream>

using namespace std;

// 1111 1110 0000, >> 5
// 0001 1111 1100, >> 2
// 0011 1111 1000, >> 3
// 0111 1111 0000, >> 4
typedef struct __maskmap {
	int masks[3];
	int shiftN;
} maskMap;

maskMap map[4] = {
	{ { 0x0F, 0x0E, 0x00 }, 5 },
	{ { 0x01, 0x0F, 0x0C }, 2 },
	{ { 0x03, 0x0F, 0x08 }, 3 },
	{ { 0x07, 0x0F, 0x00 }, 4 }
};

// 7n/4
#define CALC_INDEX(n) (7*n/4)
#define MOD_4(x) (x&0x03)

int htoi(char data);

void main() {
	//char input[] = "01D06079861D79F99F";
	char input[] = "0F97A3";
	int input_len = sizeof(input) - 1;
	bool isLoop = true;
	int index = 0;
	int point = 0;
	int result = 0;

	while (isLoop) {
		result = 0;
		index = CALC_INDEX(point);
		for (int i = 0; i < 3; i++) {
			if ((index + i) < input_len) {
 				result = result << 4;
				result |= htoi(input[index + i]) & map[MOD_4(point)].masks[i];
			}
		}
		result = result >> map[MOD_4(point)].shiftN;
		cout << result;

		point++;

		if ((index <= input_len-1) && (input_len-1 <= index + 2)) {
			isLoop = false;
		}
		else {
			if (point != 0) {
				cout << ", ";
			}
		}
	}

	// remain bits

	cout << endl;
}

int htoi(char data) {
	int result = 0;

	if (data <= '9') {
		result = data - '0';
	}
	else {
		result = data - 'A' + 10;
	}
	return result;
}