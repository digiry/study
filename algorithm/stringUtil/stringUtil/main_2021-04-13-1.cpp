#include <iostream>

using namespace std;


void StrCpy(const char * src, char * dest) {
	while (*src != '\0') {
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
}

int StrCmp(const char* src1, const char* src2) {
	while (*src1 != '\0' || *src2 != '\0') {
		if (*src1 != *src2) {
			break;
		}
		src1++;
		src2++;
	}

	return *src1 - *src2;
}

void Swap(char *const pArr, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
	pArr[b_index] = pArr[a_index] ^ pArr[b_index];
	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
}

void StrReverse(const char* src, char* dest, const int length) {
	const int lengthWithOutNull = length - 1;
	for (int i = 0; i < lengthWithOutNull; i++) {
		dest[i] = src[lengthWithOutNull - i - 1];
	}
	dest[lengthWithOutNull] = '\0';
}

void ItoA(const int number, char* destString) {
	int count = 0;
	int degree = 1;
	int num = number;

	while (num / degree > 0) {
		count++;
		degree *= 10;
	}
	degree /= 10;

	for (int i = 0; i < count; i++) {
		char letter = '0' + (num / degree);
		destString[i] = letter;
		num -= ((num / degree) * degree);
		degree /= 10;
	}
	destString[count] = '\0';
}

int AtoI(const char* src) {
	int num = 0;

	while (*src != '\0') {
		num *= 10;
		num += (*src - '0');
		src++;
	}

	return num;
}

int AtoH(const char src) {
	int hex = -1;
	if (src >= '0' && src <= '9') {
		hex = src - '0';
	}
	else if (src >= 'A' && src <= 'F') {
		hex = (src - 'A') + 10;
	}

	return hex;
}

const char HEXA_BITMAP[16][4] = {
	{'0','0','0','0'}, // 0
	{'0','0','0','1'}, // 1
	{'0','0','1','0'}, // 2
	{'0','0','1','1'}, // 3
	{'0','1','0','0'}, // 4
	{'0','1','0','1'}, // 5
	{'0','1','1','0'}, // 6
	{'0','1','1','1'}, // 7
	{'1','0','0','0'}, // 8
	{'1','0','0','1'}, // 9
	{'1','0','1','0'}, // A
	{'1','0','1','1'}, // B
	{'1','1','0','0'}, // C
	{'1','1','0','1'}, // D
	{'1','1','1','0'}, // E
	{'1','1','1','1'}, // F
};

int FillHexaWithBits(const int hex, char* src, const int cursor) {
	int current = cursor;

	for (int i = 0; i < 4; i++) {
		src[current++] = HEXA_BITMAP[hex][i];
	}

	return current;
}

int main() {
	const int LENGTH = 6;
	char src1[LENGTH] = "hello";
	char dest1[LENGTH] = { 0, };

	StrCpy(src1, dest1);
	cout << "SRC:" << src1 << " => DEST:" << dest1 << endl;

	char src2[] = "hello world";
	int diff = StrCmp(src1, src2);
	cout << "SRC1:" << src1 << " - SRC2:" << src2 << " = " << diff << endl;

	const int src3_length = 7;
	char src3[src3_length] = "sample";
	char dest3[src3_length] = { 0, };
	StrReverse(src3, dest3, src3_length);
	cout << "SRC3:" << src3 << " reverse: " << dest3 << endl;

	const int src4_length = 8;
	char src4[] = "samples";
	char dest4[src4_length] = { 0, };
	StrReverse(src4, dest4, src4_length);
	cout << "SRC4:" << src4 << " reverse: " << dest4 << endl;

	const int number1 = 486;
	char string1[LENGTH] = { 0, };
	ItoA(number1, string1);
	cout << "NUM1:" << number1 << " = STR1:" << string1 << endl;

	const char string2[] = "4876";
	int number2 = 0;
	number2 = AtoI(string2);
	cout << "STR2:" << string2 << " = NUM2:" << number2 << endl;

	const char hexChar = 'B';
	int hex = -1;
	hex = AtoH(hexChar);
	cout << "STR_HEX:" << hexChar << " = HEX:" << hex << endl;

	char bits[10] = { 0, };
	int cursor = 0;
	cursor = FillHexaWithBits(hex, bits, cursor);
	cout << "HEX:" << hexChar << "(" << hex << ")" << " => BITS:" << bits << endl;
	cursor = FillHexaWithBits(14, bits, cursor);
	cout << "HEX:" << 'E' << "(" << 14 << ")" << " => BITS:" << bits << endl;

	return 0;
}
