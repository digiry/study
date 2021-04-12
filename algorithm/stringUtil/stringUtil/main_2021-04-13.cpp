#include <iostream>

using namespace std;

const int NO_VALUE = -1;

int AtoInt(char *const integerString) {
	char *pString = integerString;
	int result = 0;

	while (*pString != '\0') {
		result = result * 10;
		result += (*pString - '0');
		pString++;
	}

	return result;
}

char BITS[10] = { 0, };
int BITS_INDEX = 0;

char HEXA_MAP[16][4] = {
	{'0','0','0','0',},	// 0
	{'0','0','0','1',},	// 1
	{'0','0','1','0',},	// 2
	{'0','0','1','1',},	// 3
	{'0','1','0','0',},	// 4
	{'0','1','0','1',},	// 5
	{'0','1','1','0',},	// 6
	{'0','1','1','1',},	// 7
	{'1','0','0','0',},	// 8
	{'1','0','0','1',},	// 9
	{'1','0','1','0',},	// A
	{'1','0','1','1',},	// B
	{'1','1','0','0',},	// C
	{'1','1','0','1',},	// D
	{'1','1','1','0',},	// E
	{'1','1','1','1',},	// F
};

int AtoHex(char hex) {
	int result = 0;

	if (hex <= '9') {
		result = hex - '0';
	}
	else {
		result = hex - 'A' + 10;
	}

	return result;
}

void InttoA(int value, char* pString) {
	int count = 0;
	int degree = 1;
	int copyValue = value;
	
	while (copyValue / degree > 0) {
		count++;
		degree *= 10;
	}
	degree /= 10;

	for (int i = 0; i < count; i++) {
		pString[i] = '0' + (copyValue / degree);
		copyValue -= ((copyValue / degree) * degree);
		degree /= 10;
	}
	pString[count] = '\0';
}

void FillHexWithBits(int hex, char *const pBits) {
	for (int i = 0; i < 4; i++) {
		pBits[BITS_INDEX++] = HEXA_MAP[hex][i];
	}
}

void StrCpy(char* src, char* dest) {
	while (*src != '\0') {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

int StrCmp(char* src, char* dest) {
	int i = 0;

	while (src[i] != '\0') {
		if (src[i] != dest[i]) {
			break;
		}
		i++;
	}

	return src[i] - dest[i];
}

void Swap(char* pString, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}
	pString[a_index] = pString[a_index] ^ pString[b_index];
	pString[b_index] = pString[a_index] ^ pString[b_index];
	pString[a_index] = pString[a_index] ^ pString[b_index];
}

void StrSwitch(char* pString, const int length) {
	int half = length >> 1;
	for (int i = 0; i < half; i++) {
		Swap(pString, i, length - i - 2);
	}
}

int main() {
	int integer = 0;
	char integerInput[] = "4876";
	integer = AtoInt(integerInput);
	cout << integerInput << " > " << integer << endl;

	int value = 789;
	char convertedInteger[10] = { 0, };
	InttoA(value, convertedInteger);
	cout << value << " > " << convertedInteger << endl;

	int hexInt = 0;
	char letter = 'A';
	hexInt = AtoHex(letter);
	cout << letter << " > " << hexInt << endl;

	letter = '8';
	hexInt = AtoHex(letter);
	cout << letter << " > " << hexInt << endl;

	FillHexWithBits(10, BITS);
	cout << BITS << endl;
	FillHexWithBits(14, BITS);
	cout << BITS << endl;

	char src[10] = "abcdef";
	char dest[10] = { 0, };
	StrCpy(src, dest);
	cout << "src:" << src << " > dest:" << dest << endl;

	char stringA[10] = "abcdef";
	char stringB[10] = "abcefg";
	int diff = StrCmp(stringA, stringB);
	cout << "src:" << stringA << " - " << "dest:" << stringB << " = " << diff << endl;

	char stringC[] = "abcdef";
	const int length = sizeof(stringC) / sizeof(stringC[0]);
	cout << stringC;
	StrSwitch(stringC, length);
	cout << " >> " << stringC << endl;

	return 0;
}